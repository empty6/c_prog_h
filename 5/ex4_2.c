/*
      ex4-2
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
  char head;
  int result = 0;


  //get head char
  while(scanf("%c", &head)){
    //judge brackets
    if(head == '('){
      push(&first, 1);
    }else if(head == '{'){
      push(&first, 2);
    }else if(head == '['){
      push(&first, 3);
    }else if(head == ')'){
      if(pop(&first) != 1){
        //bad bracket match
        result = 1; break;
      }
    }else if(head == '}'){
      if(pop(&first) != 2){
        //bad bracket match
        result = 1; break;
      }
    }else if(head == ']'){
      if(pop(&first) != 3){
        //bad bracket match
        result = 1; break;
      }
    }else if(head == '\n'){
      //end
      break;
    }
  }

  //check remain "([{"
  if(first != NULL)result = 1;

  //free all
  while(first != NULL)pop(&first);

  //print result
  printf("%d", result);

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
