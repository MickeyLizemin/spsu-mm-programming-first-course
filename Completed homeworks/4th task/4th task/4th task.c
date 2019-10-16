#include <stdio.h>
#include <math.h>

int main() 
{
	int num = 0, q = 0, numdivides, numpower;

	for(numpower = 2; numpower <= 31; numpower++) 
	{
		num = pow((double) 2, numpower) - 1;

		for(numdivides = 2; (double) numdivides * numdivides <= num; numdivides++) 
		{

			if(num % numdivides == 0) 
			{
				q++;
			}
		}

		if(q == 0) 
		{
			printf("%d\n", num);
		}
		else 
		{
			q = 0;
		}
	}

	return(0);
}