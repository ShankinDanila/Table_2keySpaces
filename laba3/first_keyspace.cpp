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


void REORGANIZATION_KS1(struct keySpace1* First_Key, int fullness) {
	int i = 0;
	int j = 0;
	struct keySpace1 tmp;

	while (i < fullness) {
		if (First_Key[i].busy == 1) {
			tmp = First_Key[i];
			j = i;
			while (j != 0) {
				First_Key[j] = First_Key[j - 1];
				j--;
			}
			First_Key[0] = tmp;
		}
		i++;
	}
	/* сборка мусора, организованная циклическим сдвигом */

	fullness = 0;
	int count = 0;

	while (First_Key[count].busy == 1) {
		fullness++;
		count++;
	}
	/* пересчет заполненности таблицы */
}

int FIND_KS1(struct keySpace1* First_Key, char* key_to_find) {
	int fullness;
	fullness = count_fullness(First_Key);

	int i = 0;
	if (i < fullness) {
		if ((First_Key[i].busy == 1) && (strcmp(First_Key[i].key1, key_to_find) == 0)) {
			return i;
		}
		i++;
	}

	return -1;			/* ошибка поиска, элемент не найден */
}

int ADD_KS1(struct keySpace1* First_Key, struct Item* elem_to_add) {
	int fullness;
	fullness = count_fullness(First_Key);

	if (FIND_KS1(First_Key, elem_to_add->key1) >= 0) {
		return -1;		/* поиск выполнен успешно, вставка невозможна */
	}
	if (fullness >= MSIZE1) {
		REORGANIZATION_KS1(First_Key, fullness);

		if (fullness == MSIZE1) {
			return -2;		/* ошибка вставки, таблица переполнена */
		}
	}

	First_Key[fullness].item = &elem_to_add;
	First_Key[fullness].busy = 1;
	fullness++;


	return 0;			/* вставка выполнена успешно */
}

int DELETE_KS1(struct keySpace1* First_Key, char* key_to_del) {
	int fullness;
	fullness = count_fullness(First_Key);
	if (FIND_KS1(First_Key, key_to_del) < 0) {
		return -1;		/* поиск неуспешен, удаление невозможно */
	}
	First_Key[FIND_KS1(First_Key, key_to_del)].busy = 0;

	return 0;			/* поиск успешен, элемент помечен, как удаленный */
}

void CLEAN_ALL_SPACE1(struct keySpace1* First_Key) {  /* очищение всей выделенной памяти */
	for (int i = 0; i < MSIZE1; i++) {
		First_Key[i].busy = 0;
		free(First_Key[i].item->info->string);
		free(First_Key[i].key1);
	}
	free(First_Key);
}

int count_fullness(struct keySpace1* First_Key) {
	int fullness = 0;

	for (int i = 0; i < MSIZE1; i++) {
		if (First_Key->busy == 1) {
			fullness++;
		}
	}
	return fullness;
}

//int main() {
//	keySpace1* First_Key;
//	int i = 0;
//	int j = 0;
//	int fullness = 0;
//	First_Key = (keySpace1*)malloc(MSIZE1 * sizeof(keySpace1));
//	
//	for (j = 0; j < MSIZE1; j++) {
//		First_Key[j].busy = 0;
//	}
//
//	while (i < MSIZE1) {
//		printf("Enter key from first keyspace: ");
//		First_Key[i].key1 = (char*)malloc(2 * sizeof(char));
//		scanf("%s", First_Key[i].key1);
//
//		printf("Enter string: ");
//		First_Key[i].info.string = (char*)malloc(2 * sizeof(char));
//		scanf("%s", First_Key[i].info.string);
//
//		printf("Enter float number: ");
//		scanf("%lf", First_Key[i].info.number);
//
//		fullness++;
//		ADD(First_Key, First_Key[i], fullness);
//
//		OUTPUT(First_Key, fullness);
//
//	}
//
//	CLEAN_ALL_SPACE1(First_Key);
//	
//	return 0;
//}