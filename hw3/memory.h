// record structure
struct record {
  char name[3];
  char number[4];
  struct record * next;
};

void init_pool();
struct record * new_node(); /* ��带 ���� ���� �� ������ ���� struct record */
void free_node(struct record *r);/* r �� ����Ű�� ���, �޸� Ǯ�� ������ */
