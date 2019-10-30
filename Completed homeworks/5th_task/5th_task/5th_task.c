#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>

int main()
{
	int secure_input_counter;
	double secure_input[1], number;

	printf("Enter the natural number whose square root you want to explore\nfrom (this number should not be the square of any integer):\n");

	for(secure_input_counter = 0; secure_input_counter < 1; secure_input_counter++)
	{
		char end_of_line = 0;

		if(scanf("%lf%c", &secure_input[secure_input_counter], &end_of_line) != 2 || end_of_line != '\n' || secure_input[secure_input_counter] < 1 \
			|| sqrt(secure_input[secure_input_counter]) == (double) ((int) sqrt(secure_input[secure_input_counter])) \
			|| secure_input[secure_input_counter] != (double) ((int) secure_input[secure_input_counter]))
		{
			printf("Data you entered is incorrect.\nPlease check it for correctness and re-enter.\n");
			fseek(stdin, 0, SEEK_END);
			secure_input_counter--;
		}
	}
	
	number = sqrt((int) secure_input[0]);

	int chain_fraction_element, period = 0;
	double fraction;

	fraction = number - (int) number;
	printf("The elements of the continued fraction are:\n%d ( ", (int) number);

	while(1)
	{
		chain_fraction_element = (int) (1 / fraction);
		period++;
		printf("%d ", chain_fraction_element);

		if(chain_fraction_element == 2 * (int) number)
		{
			break;
		}

		fraction = (1 / fraction) - chain_fraction_element;
	}

	printf(")\nElements in (...) of this continued fraction are repeated with a period %d.\n", period);
	return(0);
}