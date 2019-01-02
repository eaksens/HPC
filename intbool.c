#include <stdio.h>
#include<stdbool.h> 
#include <string.h>
#include <unistd.h>

void main()
{
	int i = 1;
	
	if(i)
	{
		printf("1 is true");
	}
	else
	{
		printf("1 is false");
	}
	
	i=100;
	
	if(i)
	{
		printf("100 is true");
	}
	else
	{
		printf("100 is false");
	}
	
	i=0;
	if(i)
	{
		printf("0 is true");
	}
	else
	{
		printf("0 is false");
	}
	
	i = -10;
	if(i)
	{
		printf("-10 is true");
	}
	else
	{
		printf("-10	 is false");
	}
}