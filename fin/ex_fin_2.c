/*
      ex_final_2
      naka.b.aa
      Naka, Bunta    */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ROW_LEN 2002
#define TERM_LEN 21


int count = 0;

typedef struct lnode {
  int docId;          //id
  struct lnode *next; //next node
} lnode;

typedef struct tnode{
  char *term;
  struct tnode *left;
  struct tnode *right;
  lnode *pos;
} tnode;

tnode* createTNode(tnode**, char*, int, lnode*);
tnode* insertTerm(tnode**, char*, lnode*);
void printTree(tnode*);
void freeTree(tnode*);

lnode* createLNode(lnode**, lnode*, int);
lnode* insertList(lnode**, int);
void printList(lnode*);
void freeList(lnode*);

tnode* search(tnode*, char*);


int main(int argc, char **argv){
  FILE *fp;
  int idTmp;
  char *fname, *tokenTmp, rowTmp[ROW_LEN], query[TERM_LEN];
  tnode *root=NULL, *hit;

  //open input file
  if(argc!=2){
    fprintf(stderr, "Usage: %s prob_file\n", argv[0]);
    return 1;
  }
  fname = argv[1];
  fp = fopen(fname, "r");
  if(fp==NULL){
    fprintf(stderr,"input file error");
    return 1;
  }

  //get row
  while(fgets(rowTmp, ROW_LEN, fp) != NULL){
    strtok(rowTmp, "\n\0");  //delete "\n"

    //cut id
    tokenTmp = strtok(rowTmp, "\t");
    idTmp = atoi(tokenTmp);

    //cut term
    while((tokenTmp = strtok(NULL, " ")) != NULL){
      //search Tree
      hit = search(root, tokenTmp);
      if(hit == NULL){
        //create Node
        hit = insertTerm(&root, tokenTmp, NULL);
      }
      //add id to posting list
      insertList(&(hit->pos), idTmp);
    }
  }
  fclose(fp);

  //get query
  scanf("%s", query);
  //search
  hit = search(root, query);
  if(hit == NULL || hit->pos == NULL){
    printf("Not found");
  }else{
    printList(hit->pos);
  }

  freeTree(root);

  return 0;
}

//add node isLeft=true:left
tnode* createTNode(tnode **parent, char *term, int isLeft, lnode *pos){
  tnode *new = malloc(sizeof(tnode));
  if(new == NULL) exit(2);  //malloc error
  char *newTerm = malloc(sizeof(char) * (strlen(term) + 1));
  if(newTerm == NULL) exit(2);  //malloc error
  strcpy(newTerm, term);
  new->term = newTerm;
  new->left = NULL;
  new->right = NULL;
  new->pos = pos;

  if((*parent) != NULL){
    if(isLeft){
      (*parent)->left = new;
    }else{
      (*parent)->right = new;
    }
  }else{
    *parent = new;
  }

  return new;
}

//insert term
tnode* insertTerm(tnode **parent, char *term, lnode *pos){
  if((*parent) == NULL){
    //empty Tree
    return createTNode(parent, term, 1, pos);
  }else if(strcmp((*parent)->term, term) > 0){
    //go left
    if((*parent)->left == NULL){
      return createTNode(parent, term, 1, pos);
    }else{
      return insertTerm(&((*parent)->left), term, pos);
    }
  }else{
    //go right
    if((*parent)->right == NULL){
      return createTNode(parent, term, 0, pos);
    }else{
      return insertTerm(&((*parent)->right), term, pos);
    }
  }
}

//print Tree Node
void printTree(tnode *parent){
  if(parent != NULL){
    printTree(parent->left);
    printf("%s\n", parent->term);
    printTree(parent->right);
  }
}

//Free Tree Node & List
void freeTree(tnode *parent){
  if(parent != NULL){
    freeTree(parent->left);
    freeTree(parent->right);
    freeList(parent->pos);
    free(parent);
  }
}

//insert to list
lnode* createLNode(lnode **parent, lnode *child, int id){
  lnode *new = malloc(sizeof(lnode));
  if(new == NULL) exit(2);  //malloc error
  new->docId = id;
  new->next = child;
  if(*parent != NULL){
    (*parent)->next = new;
  }else{
    *parent = new;
  }
  return new;
}

//add id to list
lnode* insertList(lnode **parent, int id){
  if(*parent == NULL){
    return createLNode(parent, NULL, id);
  }else{
    lnode *pivot = *parent;
    while(pivot->next != NULL){
      pivot = pivot->next;
    }
    if(pivot->docId == id)
      return pivot;
    return createLNode(&pivot, NULL, id);
  }
}

//print List Node
void printList(lnode *head){
  lnode *pivot = head;
  while(pivot != NULL){
    printf("%d\n", pivot->docId);
    pivot = pivot->next;
  }
}

//free List Node
void freeList(lnode *head){
  lnode *pivot = head;
  lnode *tmp;

  while(pivot != NULL){
    tmp = pivot;
    pivot = pivot->next;
    free(tmp);
  }
}

tnode* search(tnode *parent, char* term){
  int cmpRet;
  if(parent == NULL)
    return NULL;

  cmpRet = strcmp(parent->term, term);
  if(cmpRet > 0){
    //left
    if(parent->left == NULL){
      return NULL;
    }else{
      return search(parent->left, term);
    }
  }else if(cmpRet == 0){
    //hit
    return parent;
  }else{
    //right
    if(parent->right == NULL){
      return NULL;
    }else{
      return search(parent->right, term);
    }
  }
  return NULL;
}
