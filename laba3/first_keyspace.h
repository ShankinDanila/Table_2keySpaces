#define N 6
#define MSIZE1 25 


struct keySpace1 {  /* ��������������� �������, �������������� �������� */
	int busy;				/* ������� ��������� ��������			*/
	char key1[N];			/* ���� ��������, �� ����� ���� 0		*/
	char par[N];			/* ���� ������������� ��������			*/
	struct Item* item;				/* ��������� �� ����������				*/

};


void REORGANIZATION_KS1(struct keySpace1* First_Key, int fullness);
int FIND_KS1(struct keySpace1* First_Key, char* key_to_find);
int ADD_KS1(struct keySpace1* First_Key, struct Item* elem_to_add);
int DELETE_KS1(struct keySpace1* First_Key, char* key_to_del);
void CLEAN_ALL_SPACE1(struct keySpace1* First_Key);
int count_fullness(struct keySpace1* First_Key);