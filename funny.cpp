#include <stdlib.h>
#include <stdio.h>
#include <iostream>

using namespace std;  

void stringzip(const char* str, int str_size, char* zipped_str)
{
	char curr_char, saved_char = *str;
	int counter=0;
	for(int i=0; i<str_size+1;i++)
	{
		curr_char = str[i];
		if(curr_char == saved_char)
			counter++;
		else
		{
			_itoa(counter,zipped_str, 10);			
			zipped_str+= strlen(zipped_str);
			*zipped_str=saved_char;

			zipped_str++;
			counter = 1;
			saved_char = curr_char;
		}
	}
}
void main()  
{  
    const char *pInputStr="xxxyyyeeeellllllllddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddkkkkkkkkkkkkzzzzzzzzzzzzdddddddddgggggggzza";
#define D1 16
#define D2 12
#define D3 11
	char (*nudep) [16] = (char (*)[16]) pInputStr; //then node++ means 16 byte offset!
	for(int i=0; i<12;i++)
	{
		for(int j=0; j<16;j++) //16 is sizeof(*pointer)
		{
			printf("%c ",nudep[i][j]);
		}
		printf("\n ");
	}
/*
+		&(nudep[1][2])	0x013fcc82 "ddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddkkkkkkkkkkkkzzzzzzzzzzzzdd...	char *
+		&(nudep[1][1])	0x013fcc81 "lddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddkkkkkkkkkkkkzzzzzzzzzzzzd...	char *
means rightmost dimention increase one by one.
So... always set outter loop the leftmost dimention. and then inner loop as the rightmost dimention.
*/
	char (*pointer)[16] = (char (*)[16]) pInputStr;
	for(int i=0; i<12;i++)
	{
		char (*d1_pointer)= (char (*)) pointer[i] ;
		for(int j=0; j<16;j++) //16 is sizeof(*pointer)
		{
			printf("%c ",d1_pointer[j]);
		}
		printf("\n ");
	}

	char (*d3_pointer)[D2][D1] = (char (*)[D2][D1]) pInputStr;
	for(int i=0; i<D3;i++)//this 12 is actually have nothing related to d1 dimention. it is d3_dimention!
	{
		char (*d2_pointer)[D2] = (char (*)[D2]) d3_pointer[i] ; //i moves 12 times of 16(size of d2_pointer) each time
		for(int j=0; j<D2;j++)
		{
			char (*d1_pointer) = (char (*)) d2_pointer[j]; //d2_pointer)==16, then j added 16 each time. so size of arry it pointed is 12.
			for(int k=0; k<D1; k++)
			{
				printf("%c ",d1_pointer[k]);
			}
			printf("\n ");
		}
		printf("\n ---------------------------------------------\n");
	}

	long lInputLen=strlen(pInputStr);  

	char *pOutputStr=new char[1000]();
       
    stringzip(pInputStr,lInputLen,pOutputStr);  
    printf("%s",pOutputStr);
    delete []pOutputStr;  
}   
#if 0
	char (*d3_pointer)[12][16] = (char (*)[12][16]) pInputStr;
	for(int i=0; i<12;i++)
	{
		char (*d2_pointer)[16] = (char (*)[16]) d3_pointer[i] ;
		for(int j=0; j<16;j++)
		{
			char (*d1_pointer) = (char (*)) d2_pointer[j];
			for(int k=0; k<16; k++)
			{
				printf("%c ",d1_pointer[k]);
			}
			printf("\n ");
		}
		printf("\n ---------------------------------------------");
	}
#endif
