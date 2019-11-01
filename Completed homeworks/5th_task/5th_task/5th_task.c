#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>

int main()
{
	int secure_input_counter, number;
	double secure_input[1];

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

	number = secure_input[0];

	int continued_fraction_element, period = 0, whole_part, numerator = 1, denominator = 0;
	
	whole_part = sqrt(number);
	printf("The elements of the continued fraction are:\n%d ( ", whole_part);

	while(1)
	{
		continued_fraction_element = whole_part - denominator;
		denominator = whole_part + continued_fraction_element;
		numerator = (number - continued_fraction_element * continued_fraction_element) / numerator;
		continued_fraction_element = denominator / numerator;
		period++;
		printf("%d ", continued_fraction_element);

		if(continued_fraction_element == 2 * whole_part)
		{
			break;
		}

		denominator = denominator % numerator;
	}

	printf(")\nElements in (...) of this continued fraction are repeated with a period %d.\n", period);
	return(0);
}