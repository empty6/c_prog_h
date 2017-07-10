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
  Node *first = NULL, *print = NULL;
  char command[11];
  int input;

  //get task
  while(scanf("%s", command) != EOF){
    if(strcmp(command, "push") == 0){
      scanf("%d", &input);
      push(&first, input);
    }else if(strcmp(command, "pop") == 0){
      printf("%d\n", pop(&first));
    }else if(strcmp(command, "printstack") == 0){
      //print all
      print = first;
      while(print != NULL){
        printf("%d", print->val);
        print = print->next;
        if(print != NULL){
          printf(" ");
        }else{
          printf("\n");
        }
      }
    }
  }

  //pop all
  while(first != NULL){
    pop(&first);
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
