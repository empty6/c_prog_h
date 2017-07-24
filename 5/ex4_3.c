/*
      ex4-3
      naka.b.aa
      Naka, Bunta    */
#include <stdio.h>
#include <stdlib.h>

typedef struct Val {
  int id;
  int need;
} Val;

typedef struct Node {
  Val *val;
  struct Node *next;
} Node;

void enqueue(Node**, Node**, int, int);
void dequeue(Node**, Node**, Val*);

int main(void){
  Node *first = NULL, *last = NULL, *print = NULL;
  Val head_val;
  int i, tmp, customer_num, shop_max;

  //init
  scanf("%d", &customer_num);
  scanf("%d", &shop_max);

  //get needs
  for(i=0;i<customer_num;i++){
    scanf("%d", &tmp);
    enqueue(&first, &last, i+1, tmp);
  }

  //exec sell
  while(first != NULL){
    //show queue
    print = first;
    while(print != NULL){
      //print id
      printf("C%d", (print->val)->id);

      //move next
      print = print->next;

      //print space/¥n
      if(print != NULL){
        printf(" ");
      }else{
        printf("\n");
      }
    }

    //sell for first
    dequeue(&first, &last, &head_val);
    if(head_val.need > shop_max){
      //remain need
      head_val.need -= shop_max;
      enqueue(&first, &last, head_val.id, head_val.need);
    }
  }

  return 0;
}

//enqueue
void enqueue(Node **first, Node **last, int id, int need){
  Node *new_node = malloc(sizeof(Node));
  if(new_node == NULL) exit(2);  //malloc error
  Val *new_val = malloc(sizeof(Val));
  if(new_val == NULL) exit(2);  //malloc error

  //set val
  new_val->id = id;
  new_val->need = need;
  new_node->val = new_val;
  new_node->next = NULL;

  //set queue
  if(*first == NULL){
    *first = new_node;
  }else{
    (*last)->next = new_node;
  }
  *last = new_node;
}

//dequeue
void dequeue(Node **first, Node **last, Val *val){
  Node *tmp = *first;
  if(tmp == NULL) exit(2);  //adress error

  //copy vals
  val->id = (tmp->val)->id;
  val->need = (tmp->val)->need;

  //move first
  *first = tmp->next;
  free(tmp);
}
