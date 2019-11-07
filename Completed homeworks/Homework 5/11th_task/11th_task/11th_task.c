#include <stdio.h>
#include <malloc.h>

int digitalRoot(int number)
{
	int sum;

	while (number > 9)
	{
		sum = 0;

		while (number > 0)
		{
			sum = sum + number % 10;
			number = number / 10;
		}

		number = sum;
	}

	return(number);
}

int simplicityTest(int number)
{
	int divider;

	for (divider = 2; divider * divider <= number; divider++)
	{
		if (number % divider == 0)
		{
			return(0);
		}
	}

	return(1);
}

int main()
{
	int* digital_roots;
	digital_roots = (int*)malloc(1000000 * sizeof(int));
	int mdrs = 0;

	for (int number = 2; number <= 999999; number++) //array index matches the number
	{
		if ((number < 10) || (simplicityTest(number) == 1))
		{
			digital_roots[number] = digitalRoot(number);
			mdrs = mdrs + digital_roots[number];
		}
		else
		{
			int maximum = digitalRoot(number);

			for (int divider = 2; divider * divider <= number; divider++)
			{
				if (number % divider == 0)
				{
					digital_roots[number] = digital_roots[divider] + digital_roots[number / divider];
				}

				if (digital_roots[number] > maximum)
				{
					maximum = digital_roots[number];
				}
			}

			digital_roots[number] = maximum;
			mdrs = mdrs + digital_roots[number];
		}
	}

	printf("The sum of the maximum values of digital roots in factorizations (not only prime)\nof numbers from 2 to 999999 is %d.\n", mdrs);
	return(0);
}