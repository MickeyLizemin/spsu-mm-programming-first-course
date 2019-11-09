#include <stdio.h>
#include <malloc.h>

int main()
{
	int* array;
	array = (int*)malloc(5000 * sizeof(int));
	int counter_a, counter_b, extra_zero_counter = 0;

	for (counter_a = 0; counter_a <= 4999; counter_a++)
	{
		array[counter_a] = 0;
	}

	array[0] = 1;

	for (counter_a = 0; counter_a <= 4999; counter_a++)
	{
		for (counter_b = 0; counter_b <= 4999; counter_b++)
		{
			array[counter_b] = array[counter_b] * 3;
		}

		for (counter_b = 0; counter_b <= 4998; counter_b++)
		{
			if (array[counter_b] >= 16)
			{
				array[counter_b + 1] = array[counter_b + 1] + array[counter_b] / 16;
				array[counter_b] = array[counter_b] % 16;
			}
		}
	}

	for (counter_a = 4999; counter_a >= 0; counter_a--)
	{
		if (array[counter_a] == 0)
		{
			extra_zero_counter++;
		}
		else
		{
			break;
		}
	}

	printf("The number 3^5000 in the hexadecimal number system is:\n");

	for (counter_a = 4999 - extra_zero_counter; counter_a >= 0; counter_a--)
	{
		printf("%X", array[counter_a]);
	}

	printf("\n");
	free(array);
	return(0);
}