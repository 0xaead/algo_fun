//http://en.wikipedia.org/wiki/Radix_sort#Least_significant_digit_radix_sorts
//http://www.cs.princeton.edu/~rs/AlgsDS07/18RadixSort.pdf gives more practical cases.
#include <stdlib.h>
#include <stdio.h>

#define SRC_ARRY_SIZE 100

#define SRC_HI_BOUND 999
#define SRC_LOW_BOUND 0
#define SRC_RANGE SRC_HI_BOUND-SRC_LOW_BOUND+1
#define CTR_ARRY_SIZE SRC_RANGE

int* generate_src_arry()
{
	int* arry = new int[SRC_ARRY_SIZE];
	for (int i = 0; i < SRC_ARRY_SIZE; i++)
		arry[i]= rand()%SRC_RANGE;
	return arry;
}
int* generate_counter_arry()
{
	int* arry = new int[CTR_ARRY_SIZE];
	for (int i = 0; i < CTR_ARRY_SIZE; i++)
		arry[i]= 0;
	return arry;
}
void ctr_sort(int* src_arry, int* counter_arry)
{
	for (int i = 0; i < SRC_ARRY_SIZE; i++)
		counter_arry[src_arry[i]]++; 
	
	for (int i = SRC_LOW_BOUND; i < SRC_HI_BOUND; i++)//forward fabnacci??
		counter_arry[i+1] += counter_arry[i]; 
	//if src range is much smaller than arry size, then this iteration can be mergered with next one. it generates more complicated logic.

	int* temp = new int[SRC_ARRY_SIZE];
	int map, value;
	for (int i = 0; i < SRC_ARRY_SIZE; i++) 
	{	
		value = src_arry[i];
		map = --counter_arry[value];//then counter down!
		temp[map] = value;
	}

	for (int i = 0; i < SRC_ARRY_SIZE; i++)
	{	
		src_arry[i] = temp[i];//todo, memcpy()!!
	}
}
void main()
{
	int* src = new int[SRC_ARRY_SIZE];
	for (int i = 0; i < SRC_ARRY_SIZE; i++)
		src[i]= rand()%SRC_RANGE;

	int* ctr = new int[CTR_ARRY_SIZE];
	for (int i = 0; i < CTR_ARRY_SIZE; i++)
		ctr[i]= 0;

	//ctr_sort(src=generate_src_arry(),ctr= generate_counter_arry()); troublesome!
	ctr_sort(src,ctr);

	for (int i = 0; i < SRC_ARRY_SIZE; i++)
	{	
		printf("%d,", src[i]);
		
	}
	printf("dd%d%d,");
}
