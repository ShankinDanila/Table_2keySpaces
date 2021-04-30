#define N 6


struct Table {
	struct keySpace1* space1;
	struct keySpace2** space2;

	int fullness;

};

struct Table* new_table();
void clean_item(struct Item* item);
int add_in_table(struct Table* table, char* key1, int key2, double data_num, const char* data_string);
int find_key1_key2(struct Table* table, char key1[N], int key2, int version);
int delete_key1_key2(struct Table* table, char key1[N], int key2, int version);
struct Table* find_all_by_ks2(struct Table* table, int key2);
int del_elem_key2(struct Table* table, int key2);
int find_version_by_key1(struct Table* table, char key1[N]);
int del_elem_key1(struct Table* table, char key1[N]);
void Terminate(struct Table* tab);