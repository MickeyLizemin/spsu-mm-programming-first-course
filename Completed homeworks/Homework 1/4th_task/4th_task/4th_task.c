#include <stdio.h>
#include <math.h>

int main()
{
	for(int num_power = 2; num_power <= 31; num_power++)
	{
		int num = pow((double)2, num_power) - 1;
		int q = 0;

		for(int num_divides = 2; (double) num_divides * num_divides <= num; num_divides++)
		{
			if(num % num_divides == 0)
			{
				q++;
			}
		}

		if(q == 0)
		{
			printf("%d\n", num);
		}
	}

	return(0);
}