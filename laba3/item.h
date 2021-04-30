#define N 6


struct InfoType {
	double number;			/* первое поле информации				*/
	char* string;			/* второе поле информации, пока не Enter	*/

};

typedef struct Item {
	struct InfoType* info;		/* указатель на информационное поле		*/
	char key1[N];		/* ключ первого пространства				*/
	int key2;			/* ключ второго пространства ключей		*/

};