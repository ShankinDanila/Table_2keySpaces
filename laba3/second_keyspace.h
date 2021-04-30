#define MSIZE2 25 


struct keySpace2 {  /* перемешанная таблица, использующая перемешивание сцеплением */
	int ver;				/* версия элемента						*/
	int key2;				/* ключ элемента, не может быть 0		*/
	struct Item* item;				/* указатель на информацию				*/
	struct keySpace2* next;		/* указатель на следующий элемент 		*/

};


int HASH(int key2);
int FIND_KS2_VER(struct keySpace2** Second_Key, int key_to_find, int version);
int ADD_KS2(struct keySpace2** Second_Key, struct Item* item_to_add);
int DELETE_KS2(struct keySpace2** Second_Key, int key_to_delete, int version);
void CLEAN_ALL_SPACE2(struct keySpace2** Second_Key);
int FIND_KS2(struct keySpace2** Second_Key, int key2);