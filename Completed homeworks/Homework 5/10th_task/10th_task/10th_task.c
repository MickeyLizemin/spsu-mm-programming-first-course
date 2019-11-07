#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>

int main()
{
	int secure_input[1], secure_input_counter, amount_of_coins;

	printf("Enter your amount of coins in pence to find out how many ways there are to collect this amount from English coins:\n");

	for (secure_input_counter = 0; secure_input_counter < 1; secure_input_counter++)
	{
		char end_of_line = 0;

		if (scanf("%d%c", &secure_input[secure_input_counter], &end_of_line) != 2 || end_of_line != '\n' \
			|| secure_input[secure_input_counter] < 1)
		{
			printf("Data you entered is incorrect.\nPlease check it for correctness and re-enter.\n");
			fseek(stdin, 0, SEEK_END);
			secure_input_counter--;
		}
	}

	amount_of_coins = secure_input[0];

	int types_of_coins_counter, array_counter;
	int types_of_coins[8] = {1, 2, 5, 10, 20, 50, 100, 200};
	int *array = (int*) malloc((1 + amount_of_coins) * sizeof(int));

	for (array_counter = 0; array_counter <= amount_of_coins; array_counter++)
	{
		array[array_counter] = 0;
	}

	array[0] = 1;

	for (types_of_coins_counter = 0; types_of_coins_counter <= 7; types_of_coins_counter++)
	{
		for (array_counter = types_of_coins[types_of_coins_counter]; array_counter <= amount_of_coins; array_counter++)
		{
			array[array_counter] = array[array_counter] + array[array_counter - types_of_coins[types_of_coins_counter]];
		}
	}

	printf("Number of all possible combinations: %d.", array[amount_of_coins]);
	free(array);
	return(0);
}