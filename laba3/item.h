#define N 6


struct InfoType {
	double number;			/* ������ ���� ����������				*/
	char* string;			/* ������ ���� ����������, ���� �� Enter	*/

};

typedef struct Item {
	struct InfoType* info;		/* ��������� �� �������������� ����		*/
	char key1[N];		/* ���� ������� ������������				*/
	int key2;			/* ���� ������� ������������ ������		*/

};