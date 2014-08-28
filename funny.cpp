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

	long lInputLen=strlen(pInputStr);  
	char *pOutputStr=new char[1000]();
       
    stringzip(pInputStr,lInputLen,pOutputStr);  
    printf("%s",pOutputStr);
    delete []pOutputStr;  
}   

