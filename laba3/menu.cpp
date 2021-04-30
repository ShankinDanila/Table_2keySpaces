#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "item.h"
#include "first_keyspace.h"
#include "second_keyspace.h"
#include "input.h"
#include "dialog.h"
#include "table.h"
#include "menu.h"
#include "dialog.h"


void menu(struct Table** table) {
	int n = 1;
	int flag = 0;

	while (n != 0) {
		printf("\n");

		if (flag == 0)
		{
			printf("If You want to make new Table, enter 1\n");
		}

		printf("If You want to add element, enter 2\n");
		printf("If You want to print table, enter 3\n");
		printf("If You want to search by key2 and release, enter 4\n");
		printf("If You want to search by key1 and key2, enter 5\n");
		printf("If You want to delete element, enter 6\n");
		printf("If You want to find all element by second key, enter 7\n");
		printf("If You want search by key1, enter 8\n");
		printf("If You want delete by key2, enter 9\n");
		printf("If You want delete by key1, enter 10\n");


		printf("If You want to exit, enter 0\n");
		printf("\n");


		printf("Your choise: ");
		scanf_s("%d", &n, sizeof(int));
		scanf_s("%*c");

		switch (n) {
			case 1: {
				if (flag == 0)
				{
					D_new(table);
				}
				flag = 1;
			} break;

			case 2: {
				D_add(table);
			} break;

			case 3: {
				D_print(table);
			} break;

			case 4: {
				D_find_key2_release(table);
			} break;

			case 5: {
				D_find_key1_key2(table);
			} break;

			case 6: {
				D_delete_key1_key2(table);
			} break;
			
			case 7: {
				D_find_all_key2(table);
			} break;

			case 8: {
				D_find_key1(table);
			} break;

			case 9: {
				D_delete_elem_2(table);
			} break;

			case 10: {
				D_delete_elem_1(table);
			} break;

			case 0:
			{

			} break;
		}
	}
}