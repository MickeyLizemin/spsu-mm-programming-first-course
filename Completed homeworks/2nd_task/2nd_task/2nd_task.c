#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int greatestCommonDivisor(int number1, int number2)
{
	while(number1 != 0 && number2 != 0)
	{
		if (number1 > number2)
		{
			number1 = number1 % number2;
		}
		else
		{
			number2 = number2 % number1;
		}
	}

	return(number1 + number2);
}

int main()
{
	int array[3];
	int counter;
	int temporary;
	int x, y, z;

	printf("Enter three natural numbers that you want to check for the formation of the Pythagorean triple:\n");

	for(counter = 0; counter < 3; counter++)
	{
		scanf("%d", &array[counter]);
		
		if(array[counter] <= 0)
		{
			printf("The last number you entered is incorrect.\nTry entering all the numbers again, making sure they are correct.\n");
			scanf("%*[^\n]");
			counter = 0;
		}
	}

	for(counter = 0; counter < 2; counter++)
	{
		if(array[counter] > array[counter + 1])
		{
			temporary = array[counter];
			array[counter] = array[counter + 1];
			array[counter + 1] = temporary;
		}
	}

	x = array[0];
	y = array[1];
	z = array[2];

	if (x * x + y * y == z * z)
	{
		if(greatestCommonDivisor(x, y) == 1 && greatestCommonDivisor(y, z) == 1 && greatestCommonDivisor(x, z) == 1)
		{
			printf("The numbers you enter form a simple Pythagorean triple.\n");
		}
		else
		{
			printf("The numbers you enter form a Pythagorean triple.\n");
		}
	}
	else
	{
		printf("The numbers you enter do not form the Pythagorean triple.\n");
	}

	return(0);
}