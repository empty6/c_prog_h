/*
      ex_final_1
      naka.b.aa
      Naka, Bunta    */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TERM_LEN 21

typedef struct tnode{
  char *term;
  struct tnode *left;
  struct tnode *right;
} tnode;

void createTNode(tnode**, char*, int);
void insertTerm(tnode**, char*);
void printTree(tnode*);
void freeTree(tnode*);

int main(int argc, char **argv){
  FILE *fp;
  char *fname, termTmp[TERM_LEN];
  tnode *root = NULL;

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

  //get terms
  while(fgets(termTmp, TERM_LEN, fp) != NULL){
    strtok(termTmp, "\n\0");  //delete "\n"
    insertTerm(&root, termTmp);
  }
  fclose(fp);

  printTree(root);
  freeTree(root);

  return 0;
}

//add node isLeft=true:left
void createTNode(tnode **parent, char *term, int isLeft){
  tnode *new = malloc(sizeof(tnode));
  if(new == NULL) exit(2);  //malloc error

  char *newTerm = malloc(sizeof(char) * (strlen(term) + 1));
  if(newTerm == NULL) exit(2);  //malloc error
  strcpy(newTerm, term);

  new->term = newTerm;
  new->left = NULL;
  new->right = NULL;

  //set Tree
  if((*parent) != NULL){
    if(isLeft){
      (*parent)->left = new;
    }else{
      (*parent)->right = new;
    }
  }else{
    *parent = new;
  }
}

//insert term
void insertTerm(tnode **parent, char *term){
  if((*parent) == NULL){
    //empty Tree
    createTNode(parent, term, 1);
  }else if(strcmp((*parent)->term, term) < 0){
    //go right
    if((*parent)->right == NULL){
      createTNode(parent, term, 0);
    }else{
      insertTerm(&((*parent)->right), term);
    }
  }else{
    //go left
    if((*parent)->left == NULL){
      createTNode(parent, term, 1);
    }else{
      insertTerm(&((*parent)->left), term);
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

//free Tree Node
void freeTree(tnode *parent){
  if(parent != NULL){
    freeTree(parent->left);
    freeTree(parent->right);
    free(parent);
  }
}
