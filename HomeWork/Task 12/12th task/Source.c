﻿#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include <stdlib.h>

void myPow(int *mas, int n, int pow)
{
	int i, j;
	for (i = 0; i < pow ; i++)
	{
		for (j = 0; j < i; j++) mas[j] *= n;
		for (j = 0; j < i; j++)
			if (mas[j] >= 16)
			{
				mas[j + 1] += mas[j] / 16;
				mas[j] %= 16;
			}
	}

	for (j = 0; j < pow; j++) mas[j] *= n;
	for (j = 0; j < pow-1; j++)
		if (mas[j] >= 16)
		{
			mas[j + 1] += mas[j] / 16;
			mas[j] %= 16;
		}
}

int main()
{
	int n = 3000, i;
	int mas[3000];
	mas[0] = 1;
	for (i = 1; i < n; i++) mas[i] = 0;

	myPow(mas, 3, n);

	int zero = 0;
	for (i = n/2; i >= 0; i--)
		if (mas[i] != 0)
		{
			zero = i + 1;
			break;
		}

	for (i = zero - 1; i >= 0; i--) printf("%x", mas[i]);
	printf("\n");

	system("pause");
	return 0;
}