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
void swap_next_2(lnode*);

int main(void){
  lnode *first = NULL, *pivot = NULL;
  int tmp_id, sort_f=1;

  while(scanf("%d", &tmp_id) != EOF){
    if(tmp_id==0)break;
    printf("->%d\n", tmp_id);
    add_list(&first, tmp_id);

  }

  //bubble sort
  //edict 0/1/2 list
  while(sort_f){
    pivot = first;
    sort_f = 0;
    while(pivot->next != NULL){
      if(pivot->docid > (pivot->next)->docid){
        swap_next_2(pivot);
        sort_f = 1;
      }
      pivot = pivot->next;
    }
  }
  pivot = first;
  while(pivot != NULL){
    printf("%d ", pivot->docid);
    pivot = pivot->next;
  }

  return 0;
}

//add
void add_list(lnode **first, int id){
  lnode *new = malloc(sizeof(lnode));
  if(new == NULL) exit(2);  //malloc error
  new->docid = id;
  new->next = *first;
  *first = new;
}

//swap A-B: node->A->B->C => node->B->A->C
void swap_next_2(lnode *node){
  lnode *tmp_1 = node->next, *tmp_2 = (node->next)->next;
  tmp_1->next = tmp_2->next;
  tmp_2->next = tmp_1;
  node->next = tmp_2;
}
