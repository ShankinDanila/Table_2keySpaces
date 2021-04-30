#include <stdio.h>
#include <stdlib.h>


#include "item.h"
#include "first_keyspace.h"
#include "second_keyspace.h"
#include "input.h"
#include "dialog.h"
#include "table.h"
#include "menu.h"
#include "dialog.h"

int HASH(int key2) {
	return (key2 % MSIZE2);
}

int FIND_KS2_VER(struct keySpace2** Second_Key, int key_to_find, int version) {
	int i = 0;
	if (Second_Key[HASH(key_to_find)]->key2 == 0) {
		return -1;						/* элемента с данным ключом нет в таблице */
	}

	while (Second_Key[HASH(key_to_find)]->next != NULL)
	{
		if ((Second_Key[HASH(key_to_find)]->key2 == key_to_find) & (Second_Key[HASH(key_to_find)]->ver == version))
		{
			return 0;					/* элемент найден */
		}
		Second_Key[HASH(key_to_find)] = Second_Key[HASH(key_to_find)]->next;
	}

	return -1;							/* элемента в данным ключом нет в списке */
}

int ADD_KS2(struct keySpace2** Second_Key, struct Item* item) {
	struct keySpace2* head;
	
	int count = 0;
	struct keySpace2* ptr;
	ptr = Second_Key[HASH(item->key2)];
	while (ptr->next != NULL) {
		if (ptr->key2 == item->key2 && ptr->ver > count) {
			count = ptr->ver;
		}
		ptr = ptr->next;
	}
	int version = count + 1;		/* считаем версию ключа */
	
	
	head = Second_Key[HASH(item->key2)];
	struct keySpace2* tmp = (struct keySpace2*)calloc(1, sizeof(struct keySpace2));
	tmp->item = item;
	tmp->key2 = item->key2;
	tmp->ver = version;
	tmp->next = head;
	head = tmp;

	return 0;							/* элемент вставлен в начало списка */
}

int DELETE_KS2(struct keySpace2** Second_Key, int key_to_delete, int version) {
	if (FIND_KS2_VER(Second_Key, key_to_delete, version) == -1)
	{
		return -1;						/* искомого элемента в таблице нет */
	}

	struct keySpace2* ptr;
	/*ptr = (struct keySpace2*)malloc(1 * sizeof(struct keySpace2));
	ptr = NULL;*/
	ptr = Second_Key[HASH(key_to_delete)];
	while (ptr->next != NULL) {
		if (ptr->next->key2 == key_to_delete && ptr->next->ver == version) {
			break;
		}
		ptr = ptr->next;
	}

	struct keySpace2* tmp;
	tmp = ptr->next->next;
	free(ptr->next);
	ptr->next = tmp;

	free(ptr);

	return 0;							/* удаление успешно */
}

void CLEAN_ALL_SPACE2(struct keySpace2** Second_Key) {
	for (int i = 0; i < MSIZE2; i++) {
		struct keySpace2* tmp;
		while (Second_Key[i] != NULL) {
			tmp = Second_Key[i];
			Second_Key[i] = Second_Key[i]->next;
			free(tmp);
		}
		free(Second_Key[i]);
	}
	free(Second_Key);
}

int FIND_KS2(struct keySpace2** Second_Key, int key2) {
	while (Second_Key[HASH(key2)]->next != NULL) {
		if (Second_Key[HASH(key2)]->key2 = key2) {
			return 0;	/* Найден элемент с данным ключом во втором пространстве */
		}

		Second_Key[HASH(key2)] = Second_Key[HASH(key2)]->next;
	}
	return -1;			/* Элемент с данным ключом не найден во втором пространстве */
}