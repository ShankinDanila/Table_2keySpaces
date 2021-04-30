#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#include "item.h"
#include "first_keyspace.h"
#include "second_keyspace.h"
#include "input.h"
#include "dialog.h"
#include "table.h"
#include "menu.h"


void D_new(struct Table** tab) {
	printf("You'll work with table, which contain 2 keyspaces\n");
	printf("Max size of 1st keyspace = 5\n");
	printf("Max size of 2st keyspace = 5\n");

	*tab = new_table();
	if (*tab == NULL) {
		printf("Error in D_new! Memory allocation error!\n");
		exit(1);
	}
}

void D_add(struct Table* table) {
	if (table == NULL) {
		printf("You should make a table!\n");
		return;
	}

	printf("To add an element in table, enter key1(srting, with length = 5), key2(int), info1_number, info2_string\n");

	printf("Key1: ");
	char* key1;
	key1 = get_line();
	
	printf("Key2: ");
	double key2;
	if (GetFloat(&key2) == 0) {
		printf("Error entering key2!\n");

		Terminate(table);
		exit(1);
	}

	printf("info1_number");
	int number;
	if (GetInt(&number) == 0) {
		printf("Error entering info1_number!\n");

		Terminate(table);
		exit(1);
	}

	printf("info2_string");
	char* string = NULL;
	if ((string = get_str()) == 0)
	{
		printf("Error entering string\n");

		Terminate(table);
		exit(1);
	}

	int rs = add_in_table(table, key1, key2, number, string);

	if (rs == -1) {
		printf("Error of adding in 1st keyspace\n");
		printf("There are no available positions\n");
	}
	if (rs == -2) {
		printf("Error add el\n");
		printf("Unknown error\n");
	}

	free(key1);
	free(string);
}

void D_print(struct Table* table) {
	if (table == NULL) {
		printf("You should make a table!\n");
		return;
	}

	int n;

	printf("How do you want to print the table?\n");
	printf("If you want to see minimum information, enter 1\n");
	printf("If you want to see only first keyspace, enter 2\n");
	printf("If you want to see only second keyspace, enter 3\n");

	GetInt(&n);

	if ((n > 3) || (n < 0)) {
		printf("Incorrect number of case");
		return;
	}

	switch (n) {
		case 1: {
			printf("\n");
			printf("----------------------------------------------------\n");
			printf("                  The Table:\n");

			printf("----------------------------------------------------\n");
			printf("|  KEY1 |    KEY2    |    NUMBER    |    STRING    |\n");
			printf("----------------------------------------------------\n");

			for (int i = 0; i < count_fullness(table->space1); i++)
			{
				printf("| %10s | %10lf | %10d | %s |\n", table->space1[i].item->key1, table->space1[i].item->key2, table->space1[i].item->info->number, table->space1[i].item->info->string);
			}
			printf("----------------------------------------------------\n");
			printf("\n");
		}
		break;


		case 2:
		{
			printf("\n");
			printf("----------------------------------------------------\n");
			printf("            The Table (first keyspace):\n");
			printf("----------------------------------------------------\n");
			printf("Current size: %d\n", count_fullness(table->space1));
			printf("----------------------------------------------------\n");
			printf("| # |  KEY1  |   BUSY  |    NUMBER   |    STRING    |\n");
			printf("----------------------------------------------------\n");

			for (int i = 0; i < MSIZE1; i++)
			{
				if (i < count_fullness(table->space1))
				{
					printf("| %d | %6s | %d | %10lf | %s |\n", i, table->space1[i].item->key1, table->space1[i].busy, table->space1[i].item->info->number, table->space1[i].item->info->string);
				}
				else
				{
					printf("| %d | 0x000 | 0x00000000 | 0x00000000 |\n", i);
				}
			}
			printf("-----------------------------------------------------\n");
			printf("\n");
		}
		break;


		case 3:
		{
			printf("\n");
			printf("--------------------------------------------------\n");
			printf("          The Table (second keyspace):\n");
			printf("--------------------------------------------------\n");
			printf("| # | Key2 | Release |   NUMBER   |    STRING    |\n");
			printf("--------------------------------------------------\n");

			for (int i = 0; i < MSIZE2; i++) {
				while (table->space2[i]->next != NULL) {
					printf("| %d | %10d | %4d  | %10lf | %s |\n", i, table->space2[i]->key2, table->space2[i]->ver, table->space2[i]->item->info->number, table->space2[i]->item->info->string);
				}
			}
			printf("--------------------------------------------------\n");
			printf("\n");
		}
		break;
	}
}

void D_find_key1_key2(struct Table* table) {
	if (table == NULL) {
		printf("You should make a table!\n");
		return;
	}

	printf("Enter key1: ");
	char* key1 = NULL;
	get_line(key1);

	printf("Enter key2: ");
	int key2;
	if (GetInt(&key2) == 0) {
		printf("Error entering key2!\n");

		Terminate(table);
		exit(1);
	}

	printf("Enter release for key2: ");
	int ver;
	if (GetInt(&ver) == 0) {
		printf("Error entering release!\n");

		Terminate(table);
		exit(1);
	}

	int i = find_key1_key2(table, key1, key2, ver);

	if (i > -1) {
		printf("Element:\n");
		printf("| %6s | %10d | %10d | %10lf | %s |\n", key1, key2, find_version_by_key1(table, key1), table->space1[i].item->info->number, table->space1[i].item->info->string);
	}
	else {
		printf("No such element in table");
	}

	free(key1);
}

void D_delete_key1_key2(struct Table* table) {
	if (table == NULL) {
		printf("You should make a table!\n");
		return;
	}

	printf("Enter key1: ");
	char* key1 = NULL;
	get_line(key1);

	printf("Enter key2: ");
	int key2;
	if (GetInt(&key2) == 0) {
		printf("Error entering key2!\n");

		Terminate(table);
		exit(1);
	}

	printf("Enter release for key2: ");
	int ver;
	if (GetInt(&ver) == 0) {
		printf("Error entering release!\n");

		Terminate(table);
		exit(1);
	}

	int i = delete_key1_key2;

	if (i == -1) {
		printf("Error! Failed in delete element");
		return;
	}
	else {
		printf("Success");
	}

	free(key1);
}

void D_find_key1(struct Table* table) {
	if (table == NULL) {
		printf("You should make a table!\n");
		return;
	}

	printf("Enter key1: ");
	char* key1 = NULL;
	get_line(key1);

	int i = FIND_KS1(table->space1, key1);

	if (i < 0) {
		printf("Error! There are no elements whith this key");

		free(key1);
		Terminate(table);
		exit(1);
	}
	else {
		printf("| %10s | %10d | %10d | %s |\n", key1, table->space1[i].busy, table->space1[i].item->info->number, table->space1[i].item->info->string);
	}

	free(key1);
}

void D_find_all_key2(struct Table* table) {
	if (table == NULL) {
		printf("You should make a table!\n");
		return;
	}

	printf("Enter key2: ");
	int key2;
	if (GetInt(&key2) == 0) {
		printf("Error entering key2!\n");

		Terminate(table);
		exit(1);
	}

	struct Table* new_tab = new_table();

	new_tab = find_all_by_ks2(table, key2);
	
	D_print(new_tab);

	if (new_table != NULL)
	{
		Terminate(new_table);
	}
	else
	{
		printf("There is no such elements!\n");
	}
}

void D_find_key2_release(struct Table* table) {
	if (table == NULL) {
		printf("You should make a table!\n");
		return;
	}

	printf("Enter key2: ");
	int key2;
	if (GetInt(&key2) == 0) {
		printf("Error entering key2!\n");

		Terminate(table);
		exit(1);
	}

	printf("Enter release for key2: ");
	int ver;
	if (GetInt(&ver) == 0) {
		printf("Error entering release!\n");

		Terminate(table);
		exit(1);
	}

	int i = FIND_KS2_VER(table->space2, key2, ver);

	if (i > -1) {
		printf("| %10lf | %10d | %10d | %s |\n", key2, table->space2[HASH(key2)]->ver, table->space2[HASH(key2)]->item->info->number, table->space2[HASH(key2)]->item->info->string);
	}
	else {
		printf("There is no such element!\n");
	}
}

void D_delete_elem_2(struct Table* table) {
	if (table == NULL) {
		printf("You should make a table!\n");
		return;
	}

	printf("Enter key2: ");
	int key2;
	if (GetInt(&key2) == 0) {
		printf("Error entering key2!\n");

		Terminate(table);
		exit(1);
	}

	int i = del_elem_key2(table, key2);

	if (i > -1) {
		printf("Success");
	}
	else {
		printf("There are no such elements!\n");	
		return;
	}
}

void D_delete_elem_1(struct Table* table) {
	if (table == NULL) {
		printf("You should make a table!\n");
		return;
	}

	printf("Enter key1: ");
	char* key1 = NULL;
	get_line(key1);

	int i = del_elem_key1(table, key1);

	if (i > -1) {
		printf("Success");
	}
	else {
		printf("There is no such element!\n");
		free(key1);
	}
	free(key1);
}

