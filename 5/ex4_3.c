/*
      ex4-2
      naka.b.aa
      Naka, Bunta    */
#include <stdio.h>
#include <stdlib.h>

typedef struct Val {
  int id;
  int need;
} Val;

typedef struct Node {
  Val val;
  int id;
  struct Node *next;
} Node;

void enqueue(Node**, Node**, Val);
Val dequeue(Node**, Node**);

int main(void){
  Node *first = NULL, *last = NULL, *print = NULL;
  Val tmp_val;
  int i, tmp, customer_num, shop_max;

  //init
  scanf("%d", &customer_num);
  scanf("%d", &shop_max);

  //get needs
  for(i=0;i<customer_num;i++){
    scanf("%d", &tmp);
    tmp_val.id = i+1;
    tmp_val.need = tmp;
    enqueue(&first, &last,tmp_val);
  }

  //exec sell
  while(first != NULL){
    //show queue
    print = first;
    while(print != NULL){
      //print id
      printf("C%d", (print->val).id);

      //move next
      print = print->next;

      //print space/¥n
      if(print != NULL){
        printf(" ");
      }else{
        printf("\n");
      }
    }

    //get head customer
    tmp_val = dequeue(&first, &last);
    if(tmp_val.need > shop_max){
      //remain needs
      tmp_val.need -= shop_max;
      enqueue(&first, &last, tmp_val);
    }
  }

  return 0;
}

//enqueue val
void enqueue(Node **first, Node **last, Val val){
  Node *new = malloc(sizeof(Node));
  if(new == NULL) exit(2);  //malloc error
  new->val = val;
  if(*first==NULL)
    *first = new;
  else
    (*last)->next = new;
  *last = new;
}

//dequeue
Val dequeue(Node **first, Node **last){
  Val val;
  Node *tmp = *first;
  if(tmp == NULL) exit(2);  //adress error
  val = tmp->val;
  *first = tmp->next;
  free(tmp);
  return val;
}
