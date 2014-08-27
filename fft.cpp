#include "fft.h"

#include <math.h>
#include <complex>
#include <iostream>

#define HI 50.0
#define LO -50.0
#define SAMPLE_LENGTH 1024
using namespace std;
void main()
{    
    complex <float>    *pSignal = new complex <float> [SAMPLE_LENGTH];
    for(int i = 0; i < SAMPLE_LENGTH; i++)
    {
         float r3 = LO + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(HI-LO)));
         pSignal[i] = r3;
         cout<<pSignal[i] <<",";
    }
    //Apply FFT
    CFFT::Forward(pSignal, SAMPLE_LENGTH);
    cout<<endl;
     for(int i = 0; i < SAMPLE_LENGTH; i++)
    {
         cout<<pSignal[i] <<",";
    }
    //Free memory
    delete[] pSignal;
}

bool CFFT::Forward(complex <float>  *const data, const unsigned int length)
{
    //Check input parameters
    if (!data || length < 1 || length & (length - 1))
        return false;
    //Rearrange
    Rearrange(data, length);
    //Call FFT implementation
    Perform(data, length);
    //Succeeded
    return true;
}

void CFFT::Rearrange(complex <float>  *const data, const unsigned int length)
{
    //Swap position
    unsigned int Target = 0;
    //Process all positions of input signal
    for (unsigned int Position = 0; Position < length; ++Position)
    {
        //Only for not yet swapped entries
        if (Target > Position)
        {
            //Swap entries
            const complex <float>  Temp(data[Target]);
            data[Target] = data[Position];
            data[Position] = Temp;
        }
        //Bit mask
        unsigned int Mask = length;
        //While bit is set
        while (Target & (Mask >>= 1))
            //Drop bit
            Target &= ~Mask;
        //The current bit is 0 - set it
        Target |= Mask;
    }
}
void CFFT::Perform(complex <float>  *const data, const unsigned int length,
    const bool Inverse /* = false */)
{
    const double pi = Inverse ? 3.14159265358979323846 : -3.14159265358979323846;
    //Iteration through dyads, quadruples, octads and so on...
    for (unsigned int Step = 1; Step < length; Step <<= 1)
    {
        //Jump to the next entry of the same transform factor
        const unsigned int Jump = Step << 1;
        //Angle increment
        const double delta = pi / double(Step);
        //Auxiliary sin(delta / 2)
        const double Sine = sin(delta * .5);
        //Multiplier for trigonometric recurrence
        const complex <float>  Multiplier(-2.0 * Sine * Sine, sin(delta));
        //Start value for transform factor, fi = 0
        complex <float>  Factor(1.);
        //Iteration through groups of different transform factor
        for (unsigned int Group = 0; Group < Step; ++Group)
        {
            //Iteration within group 
            for (unsigned int Pair = Group; Pair < length; Pair += Jump)
            {
                //Match position
                const unsigned int Match = Pair + Step;
                //Second term of two-point transform
                const complex <float>  Product(Factor * data[Match]);
                //Transform for fi + pi
                data[Match] = data[Pair] - Product;
                //Transform for fi
                data[Pair] += Product;
            }
            //Successive transform factor via trigonometric recurrence
            Factor = Multiplier * Factor + Factor;
        }
    }
}
