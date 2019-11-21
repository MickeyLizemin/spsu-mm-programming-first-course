#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <time.h>
#include <math.h>

//default values
static const unsigned int arr_min_size = 100;
static const double min_load = 0.72;
static const unsigned int min_mult = 2;

unsigned int funcHash(unsigned int x)
{
	x = ((x >> 16) ^ x) * 0x45d9f3b;
	x = ((x >> 16) ^ x) * 0x45d9f3b;
	x = (x >> 16) ^ x;
	return x;
}

typedef struct pair
{
	unsigned int* key;
	unsigned int* value;
} pair;

typedef struct list
{
	pair* data;
	struct list* next;
} list;

typedef struct hash_table
{
	unsigned int table_size;
	list** arr;
	unsigned int arr_size;
	double load;
	unsigned int limit;
	unsigned int mult;
} hash_table;

hash_table* createHashTable(unsigned int arr_size, double load, unsigned int mult)
{
	hash_table* table = (hash_table*)malloc(sizeof(hash_table));

	table->table_size = 0;
	table->arr_size = arr_size;
	table->load = load;
	table->limit = (unsigned int)(table->arr_size * table->load);
	table->mult = mult;
	table->arr = (list**)calloc(table->arr_size, sizeof(list*));
	return(table);
}

hash_table* rebalanceAndPutHashTable();

void putHashTable(hash_table** table, pair* kv)
{
	unsigned int i;

	i = funcHash(kv->key) % ((*table)->arr_size);

	if((*table)->table_size < (*table)->limit)
	{
		if ((*table)->arr[i] == NULL)
		{
			list* new_list = (list*)malloc(sizeof(list));

			new_list->next = NULL;
			new_list->data = kv;
			(*table)->arr[i] = new_list;
		}
		else
		{
			list* tmp_list = (*table)->arr[i];
			list* new_list = NULL;

			while (tmp_list->next)
			{
				if (tmp_list->data->key == kv->key)
				{
					printf("Key %u repeated. The old value %u is\nreplaced by new value %u.\n", kv->key, tmp_list->data->value, kv->value);
					tmp_list->data = kv;
					(*table)->table_size--;
					return;
				}

				tmp_list = tmp_list->next;
			}

			new_list = (list*)malloc(sizeof(list));
			new_list->next = NULL;
			new_list->data = kv;
			tmp_list->next = new_list;
		}
	}
	else
	{
		*table = rebalanceAndPutHashTable(table, kv);
	}

	(*table)->table_size++;
}

void putHashTableForUser(hash_table** table, unsigned int key, unsigned int value)
{
	pair* kv = (pair*)malloc(sizeof(pair));

	kv->key = key;
	kv->value = value;
	putHashTable(table, kv);
}

hash_table* rebalanceAndPutHashTable(hash_table** table, pair* kv)
{
	hash_table* new_hash_table = createHashTable((*table)->arr_size * (*table)->mult, (*table)->load, (*table)->mult);
	list* tmp_list = NULL;
	unsigned int i, arr_size;

	arr_size = (*table)->arr_size;

	for (i = 0; i < arr_size; i++)
	{
		tmp_list = (*table)->arr[i];

		while (tmp_list)
		{
			putHashTable(&new_hash_table, tmp_list->data);
			tmp_list = tmp_list->next;
		}

		free(tmp_list);
	}

	free((*table)->arr);
	free(*table);

	*table = new_hash_table;
	putHashTable(&new_hash_table, kv);
	return(new_hash_table);
}

void getValueHashTable(hash_table* table, unsigned int* key)
{
	unsigned int i, f = 0;

	i = funcHash(key) % (table->arr_size);

	if (table->arr[i])
	{
		if (table->arr[i]->data->key == key)
		{
			f = 1;
			printf("Of the key %u, %u is found.\n", key, table->arr[i]->data->value);
		}
		else
		{
			list* tmp_list = table->arr[i]->next;

			while (tmp_list)
			{
				if (tmp_list->data->key == key)
				{
					f = 1;
					printf("Of the key %u, %u is found.\n", key, tmp_list->data->value);
				}

				tmp_list = tmp_list->next;
			}
		}
	}
	else
	{
		f = 1;
		printf("No value found for key %u.\n", key);
	}

	if (f == 0)
	{
		printf("No value found for key %u.\n", key);
	}
}

void removeValueHashTable(hash_table* table, unsigned int* key)
{
	unsigned int i, f = 0;

	i = funcHash(key) % (table->arr_size);

	if (table->arr[i])
	{
		if (table->arr[i]->data->key == key)
		{
			list* next_list = NULL;

			f = 1;
			printf("Of the key %u, %u is removed.\n", key, table->arr[i]->data->value);
			next_list = table->arr[i]->next;
			free(table->arr[i]->data);
			free(table->arr[i]);
			table->arr[i] = next_list;
		}
		else
		{
			list* next_list = table->arr[i];
			list* tmp_list = table->arr[i]->next;

			while (tmp_list)
			{
				if (tmp_list->data->key == key)
				{
					f = 1;
					printf("Of the key %u, %u is removed.\n", key, tmp_list->data->value);
					next_list->next = tmp_list->next;
					free(tmp_list->data);
					free(tmp_list);
					table->table_size--;
					break;
				}

				next_list = tmp_list;
				tmp_list = tmp_list->next;
			}
		}
	}
	else
	{
		f = 1;
		printf("No value to remove for key %u.\n", key);
	}

	if (f == 0)
	{
		printf("No value to remove for key %u.\n", key);
	}

	table->table_size--;
}

void removeHashTable(hash_table** table)
{
	list* tmp_list;
	unsigned int i, arr_size;

	arr_size = (*table)->arr_size;

	for (i = 0; i < arr_size; i++)
	{
		tmp_list = (*table)->arr[i];

		while (tmp_list)
		{
			free(tmp_list->data);
			tmp_list = tmp_list->next;
		}

		free(tmp_list);
	}

	free((*table)->arr);
	free(*table);
	*table = NULL;
}

void outputHashTable(hash_table* table)
{
	unsigned int i, arr_size, k = 0;

	arr_size = table->arr_size;
	
	for (i = 0; i < arr_size; i++) 
	{
		list* tmp_list = table->arr[i];

		printf("Array element #%u --------------------------------------------\n\n", i);

		while (tmp_list)
		{
			printf("Node #%u -------------------------------\n", k);
			printf("(Key: %u, Value: %u)\n\n", tmp_list->data->key, tmp_list->data->value);
			k++;
			tmp_list = tmp_list->next;
		}

		k = 0;
	}
}

int main()
{
	srand(time(NULL));

	hash_table* hash_table;
	unsigned int k = 1, c, arr_size, mult;
	double load;

	printf("You need to enter 3 main parameters of the hash table: \n");
	printf("(enter 1 in all parameters to accept default values)\n\n");

	if (k == 1)
	{
		printf("%u. The number of array elements: ", k);
		scanf("%u", &arr_size);

		if (arr_size < arr_min_size)
		{
			arr_size = arr_min_size;
			printf("\nThe number of array elements you entered is too small.\n");
			printf("This parameter has been changed to the default value (%u).\n\n", arr_min_size);
		}

		k++;
	}

	if (k == 2)
	{
		printf("%u. Percentage of load of the array, exceeding which will cause rebalancing: ", k);
		scanf("%lf", &load);
		load = load * 0.01;

		if (load < min_load || load > 1)
		{
			load = min_load;
			printf("\nThe percentage of load of the array you entered is not optimal, because it is too large or too small.\n");
			printf("This parameter will be changed to the default value (%u%%).\n\n", (unsigned int) (min_load * 100));
		}

		k++;
	}

	if (k == 3)
	{
		printf("%u. The value of how many times the length of the array will increase during rebalancing: ", k);
		scanf("%u", &mult);

		if (mult < min_mult)
		{
			mult = min_mult;
			printf("\nThe value you entered, how many times the length of the array will increase during rebalancing,\n");
			printf("is not optimal, because it is too small. This parameter will be changed to the default value (%u).\n", min_mult);
		}
	}

	printf("\n");
	hash_table = createHashTable(arr_size, load, mult);
	printf("Enter the number of (key, value) pairs that you want to put in the hash table: ");
	scanf("%u", &c);
	printf("\nInput pairs table:\n");

	for (k = 0; k < c; k++)
	{
		unsigned int value = rand();
		unsigned int key = rand();

		printf("Pair #%u. (Key: %u, Value: %u)\n", k, key, value);
		putHashTableForUser(&hash_table, key, value);
	}

	printf("\nThe contents of the hash table:\n");
	outputHashTable(hash_table);

	printf("Enter the key whose value you want to find. To complete the search, enter -1.\n");

	while (1)
	{
		scanf("%d", &k);

		if (k == -1)
		{
			break;
		}

		getValueHashTable(hash_table, k);
	}

	printf("\nEnter the key whose value you want to remove. To complete the search, enter -1.\n");

	while (1)
	{
		scanf("%d", &c);

		if (c == -1)
		{
			break;
		}

		removeValueHashTable(hash_table, c);
	}

	removeHashTable(&hash_table);
	return(0);
}

