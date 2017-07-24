/*
      ex_fin_2
      naka.b.aa
      Naka, Bunta    */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct tnode{
  char *term;
  int dfreq;
  struct tnode *left;
  struct tnode *right;
  lnode *pos;
} tnode;

void insertTerm(tnode**, char*);
void createTNode(tnode**, vhar*);
void printTree(tnode**);
void freeTree(tnode**);

int main(void){
  tnode *root;



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

//insert id list
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

void add_tree(tnode **prev, char *term){

}
