#ifndef _FFT_H_
#define _FFT_H_

#include <complex>
using namespace std;
class CFFT
{
public:

    //FORWARD FOURIER TRANSFORM, INPLACE VERSION
    //  Data - both input data and output
    //  N     - length of both input data and result
    static bool Forward(complex <float>  *const Data, const unsigned int N);

    //INVERSE FOURIER TRANSFORM, INPLACE VERSION
    //  Data  - both input data and output
    //  N      - length of both input data and result
    //  Scale - if to scale result
    static bool Inverse(complex <float>  *const Data, const unsigned int N,
        const bool scale = true);

protected:
    //Rearrange function and its inplace version
    static void Rearrange(complex <float>  *const Data, const unsigned int N);

    //FFT implementation
    static void Perform(complex <float>  *const Data, const unsigned int N,
        const bool Inverse = false);

	static void Scale(complex<float> *const Data, const unsigned int N);
};

#endif
