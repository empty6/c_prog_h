/*
      ex4-1
      naka.b.aa
      Naka, Bunta    */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
  int val;
  struct Node *next;
} Node;

void push(Node**, int);
int pop(Node**);


int main(void){
  Node *first = NULL;
  char command[10];
  int input;

  while(1){
    //get task
    scanf("%s", command);

    if(strcmp(command, "push") == 0){
      scanf("%d", &input);
      printf("push %d\n", input);
    }else if(strcmp(command, "pop") == 0){
      printf("%d\n", pop(&first));
    }else if(strcmp(command, "printstack") == 0){
      //pop all
      while(first != NULL){
        puts("!");
        printf("%d", pop(&first));
      }
      break;
    }
  }
  return 0;
}

//push stack
void push(Node **first, int val){
  Node *new = malloc(sizeof(Node));
  if(new == NULL) exit(2);  //malloc error
  new->val = val;
  new->next = *first;
  *first = new;
}

//pop stack
int pop(Node **first){
  int val;
  Node *tmp = *first;
  if(tmp == NULL) exit(2);  //adress error
  val = tmp->val;
  *first = tmp->next;
  free(tmp);
  return val;
}
