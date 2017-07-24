/*
      ex_fin_2
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

typedef struct tnode{
  char *term;
  int dfreq;
  struct tnode *left;
  struct tnode *right;
  lnode *pos;
} tnode;

void add_list(lnode**, int);
void insert_list(lnode**, int);

void add_tree(tnode**, char*);

//int comp_word(char*, char*);

int main(void){
  int tmp_id;
  tnode *high, *low;
  char word_list_high[6][7] = {
    {"apple"},
    {"banana"},
    {"grape"},
    {"kiwi"},
    {"mango"},
    {"orange"}
  }, word_list_low[6][7] = {
    {"apple"},
    {"grape"},
    {"banana"},
    {"orange"},
    {"mango"},
    {"kiwi"}
  };

  //set high


/*
  while(scanf("%d", &tmp_id) != EOF){
    //insert docid
    if(tmp_id==0)break;
    insert_list(&first, tmp_id);
  }
*/
/*
  //print list
  pivot = first;
  while(pivot != NULL){
    printf("%d ", pivot->docid);
    pivot = pivot->next;
  }
*/


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
