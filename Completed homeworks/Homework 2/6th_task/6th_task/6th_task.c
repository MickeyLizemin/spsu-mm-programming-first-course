#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "mman.c"
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>

#define S_IWRITE 0x0080 //Instead of connecting a separate <io.h> library
#define MAXLINE 4096

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

	char* lineptr[MAXLINE];
	char str[MAXLINE];
	int i, k, nl, d, j, t;

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
	d = strlen(flin_mapped);

	if (flin_mapped == MAP_FAILED)
	{
		printf("Unable to map file.\n");
		exit(0);
	}

	k = 0;

	for (i = 0; i < MAXLINE; )
	{
		j = 0;

		while (k < d)
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

		if (k == d)
		{
			break;
		}

		lineptr[i++] = _strdup(str);
	}

	nl = i;
	qsort(lineptr, nl, sizeof(char*), ccmp);
	t = 0;

	for (i = 0; i < nl; i++)
	{
		char* tmp = lineptr[i];

		while (*tmp != '\n')
		{
			t++;
			//printf("%c", *lineptr[i]);
			tmp++;
		}

		if (*tmp == '\n')
		{
			t++;
			//printf("%c", *lineptr[i]);
		}
	}

	char* flout_mapped = (char**)malloc(t * sizeof(char*));
	k = 0;

	for (i = 0; i < nl; i++)
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

	_write(flout, flout_mapped, t);
	munmap(flin_mapped, d);
	free(flout_mapped);
	_close(flin);
	_close(flout);
	return(0);
}