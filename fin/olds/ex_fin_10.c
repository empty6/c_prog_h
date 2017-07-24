/*
      ex_fin
      naka.b.aa
      Naka, Bunta    */
#include <stdio.h>
#include <stdlib.h>

typedef struct lnode {
  int docid;          //id
  int frec;           //TF
  int score;          //score
  struct lnode *next; //next node
} lnode;

void add_list(lnode**, int);
void insert_list(lnode**, int);

int main(void){
  lnode *first = NULL, *pivot = NULL;
  int tmp_id;

  while(scanf("%d", &tmp_id) != EOF){
    if(tmp_id==0)break;
    insert_list(&first, tmp_id);
  }

  //print list
  pivot = first;
  while(pivot != NULL){
    printf("%d ", pivot->docid);
    pivot = pivot->next;
  }

  return 0;
}

//add
void add_list(lnode **first, int id){
printf("add -> %d\n", id);
  lnode *new = malloc(sizeof(lnode));
  if(new == NULL) exit(2);  //malloc error
  new->docid = id;
  new->next = *first;
  *first = new;
}

void insert_list(lnode **first, int id){
  lnode *pivot = *first;
  if(pivot == NULL || pivot->docid > id){
    add_list(first, id);
  }else{
    //search
    while(pivot != NULL){
      if(pivot->next == NULL || (pivot->next)->docid > id){
        add_list(&(pivot->next), id);
        break;
      }
      pivot = pivot->next;
    }
  }
}
