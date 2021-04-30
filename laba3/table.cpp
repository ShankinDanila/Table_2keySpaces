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


struct Table* new_table() {
	struct Table* newtab = NULL;
	newtab = (struct Table*)calloc(1, sizeof(struct Table));

	newtab->space1 = (struct keySpace1*)calloc(MSIZE1, sizeof(struct keySpace1));
	for (int i = 0; i <= MSIZE1; i++) {
		newtab->space1[i].busy = 0;
	}
	newtab->space2 = (struct keySpace2**)calloc(MSIZE2, sizeof(struct keySpace2*));
	for (int i = 0; i <= MSIZE2; i++) {
		newtab->space2[i] = NULL;
	}

	return newtab;
}

void clean_item(struct Item* item) {
	item->info->number = 0;
	if (item->info->string != NULL) {
		free(item->info->string);
	}
	if (item->info != NULL) {
		free(item->info);
	}
	if (item != NULL) {
		free(item);
	}
}

int add_in_table(struct Table* table, char* key1, int key2, double data_num, const char* data_string) {
	struct InfoType* info = NULL;
	info = (struct InfoType*)calloc(1, sizeof(struct InfoType));

	info->number = data_num;

	info->string = (char*)malloc(strlen(data_string) * sizeof(char));

	struct Item* item = NULL;
	item = (struct Item*)calloc(1, sizeof(struct Item));

	item->info = info;

	if (ADD_KS1(table->space1, item) < 0) {
		clean_item(item);

		return -1; //ошибка во вставке в первое пространство ключей (табл. переполнена)
	}

	if (ADD_KS2(table->space2, item) == 0) {
		return 0;
	}
	else return -2; //неизвестная ошибка
}

int find_key1_key2(struct Table* table, char key1[N], int key2, int version) {
	if (FIND_KS1(table->space1, key1) < 0) {
		return -1; //ключ по первому пространству не найден
	}
	if (FIND_KS2_VER(table->space2, key2, version) < 0) {
		return -2; //ключ по второму пространству не найден
	}

	return FIND_KS1(table->space1, key1); // возвращаем индекс найденного элемента в первом пр-ве
}

int delete_key1_key2(struct Table* table, char key1[N], int key2, int version) {
	int i = find_key1_key2(table, key1, key2, version);

	if (i > -1) {
		int j = FIND_KS1(table->space1, key1);
		clean_item(table->space1[j].item);
		DELETE_KS1(table->space1, key1);
		DELETE_KS2(table->space2, key2, version);

		return 0; //удаление прошло успешно
	}
	
	return -1; //произошла ошибка при удалении
}

struct Table* find_all_by_ks2(struct Table* table, int key2) {
	struct Table* newtab = new_table();

	while (table->space2[HASH(key2)]->next != NULL) {
		
		if (table->space2[HASH(key2)]->key2 = key2) {
			add_in_table(newtab, table->space2[HASH(key2)]->item->key1, key2, table->space2[HASH(key2)]->item->info->number, table->space2[HASH(key2)]->item->info->string);
		}


		table->space2[HASH(key2)] = table->space2[HASH(key2)]->next;
	}

	return newtab;
}

int del_elem_key2 (struct Table* table, int key2) {
	if (FIND_KS2(table->space2, key2) != -1) {
		while (table->space2[HASH(key2)]->next != NULL) {
			if (table->space2[HASH(key2)]->key2 = key2) {
				DELETE_KS2(table->space2, key2, table->space2[HASH(key2)]->ver);
				clean_item(table->space2[HASH(key2)]->item);
				DELETE_KS1(table->space1, table->space2[HASH(key2)]->item->key1);
			}

			table->space2[HASH(key2)] = table->space2[HASH(key2)]->next;
		}
		return 0;	/* успех */
	}
	else return -1; /* не найдено элементов в данным ключом */
}

int find_version_by_key1(struct Table* table, char key1[N]) {
	while (table->space2[HASH(table->space1[FIND_KS1(table->space1, key1)].item->key2)]->next != NULL) {
		
		if (&(table->space2[HASH(table->space1[FIND_KS1(table->space1, key1)].item->key2)]->item->info) == &(table->space1[FIND_KS1(table->space1, key1)].item->info)) {
			
			return table->space2[HASH(table->space1[FIND_KS1(table->space1, key1)].item->key2)]->ver; //возврат версии элемента
		}	
	}
	return -1; //элемента не найдено
}

int del_elem_key1(struct Table* table, char key1[N]) {

	if (FIND_KS1(table->space1, key1) != -1) {
		DELETE_KS1(table->space1, key1);
		clean_item(table->space1->item);
		DELETE_KS2(table->space2, table->space1[FIND_KS1(table->space1, key1)].item->key2, find_version_by_key1(table, key1));
		return 0;
	}
	
	return -1; /* элемента с данным ключом не найдено в первом пространстве */
}

void Terminate(struct Table* tab) {
	if (tab == NULL) {
		return;
	}

	CLEAN_ALL_SPACE1(tab->space1);
	CLEAN_ALL_SPACE2(tab->space2);
}