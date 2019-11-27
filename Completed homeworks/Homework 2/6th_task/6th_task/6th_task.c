#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "mman.c"
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>

int ccmp(const void* p1, const void* p2)
{
	const char* s1;
	const char* s2;

	s1 = *(char**)p1;
	s2 = *(char**)p2;
	return(strcmp(s1, s2));
}

int main()
{
	int flin, flout, flin_size;
	char* flin_mapped;
	struct stat flin_info;
	int i, k, len, j, maxline, m, u;

	flin = _open("input.txt", O_RDWR, 0);
	flout = _open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, S_IWRITE);

	if (flin == -1)
	{
		printf("Unable to open file.\n");
		exit(0);
	}

	fstat(flin, &flin_info);
	flin_size = flin_info.st_size;
	flin_mapped = mmap(0, flin_size, PROT_READ | PROT_WRITE, MAP_PRIVATE, flin, 0);
	len = strlen(flin_mapped);
	u = 0;
	m = 0;
	maxline = 0;

	for (i = 0; i < len; i++)
	{
		if (flin_mapped[i] != '\n')
		{
			m++;

			if (m > maxline)
			{
				maxline = m;
			}
		}
		else
		{
			m++;
			u++;

			if (m > maxline)
			{
				maxline = m;
			}

			m = 0;
		}
	}

	char** lineptr = (char**)malloc(u * sizeof(char*));
	char* str = (char*)malloc(maxline * sizeof(char));

	if (flin_mapped == MAP_FAILED)
	{
		printf("Unable to map file.\n");
		exit(0);
	}

	k = 0;

	for (i = 0; i < u; )
	{
		j = 0;

		while (k < len)
		{
			if (flin_mapped[k] == '\n')
			{
				str[j] = '\n';
				j++;
				k++;
				break;
			}

			str[j] = flin_mapped[k];
			j++;
			k++;
		}

		lineptr[i++] = _strdup(str);

		if (k == len)
		{
			break;
		}
	}

	qsort(lineptr, u, sizeof(char*), ccmp);

	/*for (i = 0; i < u; i++)
	{
		char* tmp = lineptr[i];

		while (*tmp != '\n')
		{
			//printf("%c", *lineptr[i]);
			tmp++;
		}

		if (*tmp == '\n')
		{
			//printf("%c", *lineptr[i]);
		}
	}*/

	char* flout_mapped = (char*)malloc(len * sizeof(char*));
	k = 0;

	for (i = 0; i < u; i++)
	{
		char* tmp = lineptr[i];

		while (*tmp != '\n')
		{
			flout_mapped[k] = *tmp;
			k++;
			tmp++;
		}

		if (*tmp == '\n')
		{
			flout_mapped[k] = '\n';
			k++;
		}

		free(lineptr[i]);
	}

	_write(flout, flout_mapped, len);
	munmap(flin_mapped, len);
	free(flout_mapped);
	free(lineptr);
	free(str);
	_close(flin);
	_close(flout);
	return(0);
}