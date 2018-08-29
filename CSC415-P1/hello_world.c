/**
 * CSC 415 Assignment 1
*/
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define NAME "Ahmad"

int main(int argc,  char** argv)
{
	int len, bytes_written;
	char* out = malloc(64); //allocates 128 bytes 
	len = sprintf(out, "CSC 415, This program written by %s!!!\n",NAME);
	//printf("%d\n", len);
	if(!len)
	{
		perror("error sprintf...");
	}
	bytes_written = write(1,out,len);

	if(bytes_written < 0)
	{
		perror("error write...");
	}
	return 0;
}
