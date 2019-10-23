#include <stdio.h>
#include <math.h>
#include <string.h>

void arrayBinaryNumberTranslator(long long number, int *array, int counter)
{
	while(number != 0)
	{
		array[counter] = number % 2;
		counter++;
		number = number / 2;
	}

	return(0);
}

int main()
{
	const char *name = "Ilya";
	const char *surname = "Kuznetsov";
	const char *patronymic = "Alexandrovich";
	int counter_a = 0, multiplication = 1;
	int digits_a[32];
	long long additional_code;
	
	multiplication = strlen(name) * strlen(surname) * strlen(patronymic);
	printf("Multiplication of name, surname and patronymic is %d.\n", multiplication);

	additional_code = pow(2, 32) - multiplication;

	arrayBinaryNumberTranslator(additional_code, digits_a, counter_a);
	
	printf("Representation of a multiplication as a negative 32-bit integer: ");
	
	for(counter_a = 0; counter_a <= 31; counter_a++) 
	{
		printf("%d", digits_a[31 - counter_a]);
	}

	printf(".\n");

	float float_multiplication = multiplication;
	int transformed_multiplication_b = *((int*) & float_multiplication);
	int counter_b = 0;
	int digits_b[31];

	arrayBinaryNumberTranslator(transformed_multiplication_b, digits_b, counter_b);

	printf("Representation of a multiplication as an IEEE 754 single-precision positive floating-point number: 0");

	for(counter_b = 0; counter_b <= 30; counter_b++)
	{
		printf("%d", digits_b[30 - counter_b]);
	}

	printf(".\n");

	double double_multiplication = multiplication;
	long long transformed_multiplication_c = *((long long*) & double_multiplication);
	int counter_c = 0;
	int digits_c[63];

	arrayBinaryNumberTranslator(transformed_multiplication_c, digits_c, counter_c);

	printf("Representation of a multiplication as an IEEE 754 double-precision negative floating-point number: 1");

	for(counter_c = 0; counter_c <= 62; counter_c++) 
	{
		printf("%d", digits_c[62 - counter_c]);
	}

	printf(".\n");

	return(0);
}
