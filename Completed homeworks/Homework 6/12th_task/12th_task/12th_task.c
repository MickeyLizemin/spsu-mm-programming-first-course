#include <stdio.h>
#include <math.h>
#include <malloc.h>

int main()
{
	int* array;
	int counter_a, counter_b, digit_counter;

	digit_counter = (int)(5000 * log(3) / log(16)); //We do not add 1 to the result, since the elements of the array are numbered from 0
	array = (int*)malloc((digit_counter + 1) * sizeof(int)); //Add 1 here in connection with what is written above

	for (counter_a = 0; counter_a <= digit_counter; counter_a++)
	{
		array[counter_a] = 0;
	}

	array[0] = 1;

	for (counter_a = 0; counter_a <= 4999; counter_a++)
	{
		for (counter_b = 0; counter_b <= digit_counter; counter_b++)
		{
			array[counter_b] = array[counter_b] * 3;
		}

		for (counter_b = 0; counter_b <= digit_counter - 1; counter_b++) //Subtract 1, otherwise it is possible to get out of the array
		{
			if (array[counter_b] >= 16)
			{
				array[counter_b + 1] = array[counter_b + 1] + array[counter_b] / 16;
				array[counter_b] = array[counter_b] % 16;
			}
		}
	}

	printf("The number 3^5000 in the hexadecimal number system is:\n");

	for (counter_a = digit_counter; counter_a >= 0; counter_a--)
	{
		printf("%X", array[counter_a]);
	}

	printf("\n");
	free(array);
	return(0);
}