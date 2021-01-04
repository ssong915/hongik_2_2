// record structure
struct record {
  char name[3];
  char number[4];
  struct record * next;
};

void init_pool();
struct record * new_node(); /* 노드를 새로 만들어서 그 포인터 리턴 struct record */
void free_node(struct record *r);/* r 이 가르키는 노드, 메모리 풀로 돌려줌 */
