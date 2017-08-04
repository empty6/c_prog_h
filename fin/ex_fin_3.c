/*
      ex_final_3
      naka.b.aa
      Naka, Bunta    */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ROW_LEN 2002
#define TERM_LEN 21


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

typedef struct qnode{
  lnode *pos;
  struct qnode *next;
} qnode;


tnode* createTNode(tnode**, char*, int, lnode*);
tnode* insertTerm(tnode**, char*, lnode*);
void printTree(tnode*);
void freeTree(tnode*);

lnode* createLNode(lnode**, lnode*, int);
lnode* insertList(lnode**, int);
void printList(lnode*);
void freeList(lnode*);

tnode* search(tnode*, char*);

lnode* mergeList(lnode*, lnode*);
lnode* intersectList(lnode*, lnode*);

qnode* pushQuery(qnode**, lnode*);
lnode* popQuery(qnode**);
void freeQuery(qnode*);

void execQuery(qnode**, tnode*, char*);

int main(int argc, char **argv){
  FILE *fp;
  int idTmp;
  char *fname, *tokenTmp, rowTmp[ROW_LEN], query[TERM_LEN];
  tnode *root=NULL, *hitTNode;
  qnode *queryStack=NULL;

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
      hitTNode = search(root, tokenTmp);
      if(hitTNode == NULL){
        //create Node
        hitTNode = insertTerm(&root, tokenTmp, NULL);
      }
      //add id to posting list
      insertList(&(hitTNode->pos), idTmp);
    }
  }
  fclose(fp);

  //get query
  //scanf("%s", query);
  while(scanf("%s", query) != EOF){
    execQuery(&queryStack, root, query);
  }
  if(queryStack == NULL || queryStack->pos == NULL){
    printf("Not found");
  }else if(queryStack->next != NULL){
    printf("Query error");
  }else{
    printList(queryStack->pos);
  }

  freeQuery(queryStack);
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
lnode* insertList(lnode **first, int id){
  if(*first == NULL){
    return createLNode(first, NULL, id);
  }else{
    lnode *pivot = *first;
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

//search term from tree
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


lnode* mergeList(lnode *l1, lnode *l2){
  lnode *first=NULL;

  while(l1 != NULL && l2 != NULL){
    if(l1->docId <= l2->docId){
      insertList(&first, l1->docId);
      if(l1->docId == l2->docId)l2 = l2->next;
      l1 = l1->next;
    }else if(l1->docId < l2->docId){
      insertList(&first, l2->docId);
      l2 = l2->next;
    }
  }
  if(l1 == NULL){
    while(l2 != NULL){
      insertList(&first, l2->docId);
      l2 = l2->next;
    }
  }else{
    while(l1 != NULL){
      insertList(&first, l1->docId);
      l1 = l1->next;
    }
  }
  return first;
}

lnode* intersectList(lnode *l1, lnode *l2){
  lnode *first=NULL;

  while(l1 != NULL && l2 != NULL){
    if(l1->docId != l2->docId){
      if(l1->docId < l2->docId){
        l1 = l1->next;
      }else{
        l2 = l2->next;
      }
    }else{
      insertList(&first, l1->docId);
      l2 = l2->next;
      l1 = l1->next;
    }
  }
  return first;
}

//push query stack
qnode* pushQuery(qnode **first, lnode *pos){
  qnode *new = malloc(sizeof(lnode));
  if(new == NULL) exit(2);  //malloc error

  new->pos = pos;
  new->next = *first;
  *first = new;
  return new;
}

//pop query stack
lnode* popQuery(qnode **first){
  qnode *tmp = *first;
  lnode *pos;

  pos = tmp->pos;
  *first = tmp->next;
  free(tmp);

  return pos;
}

void freeQuery(qnode *head){
  qnode *pivot = head;
  qnode *tmp;

  while(pivot != NULL){
    tmp = pivot;
    pivot = pivot->next;
    free(tmp);
  }
}

void execQuery(qnode **queryStack, tnode *root, char *query){
  lnode *pos_1, *pos_2, *result;
  tnode *hitTNode;

  if(strcmp(query, "OR") == 0){
    //push merge
    pos_1 = popQuery(queryStack);
    pos_2 = popQuery(queryStack);
    result = mergeList(pos_1, pos_2);
    pushQuery(queryStack, result);
  }else if(strcmp(query, "AND") == 0){
    //push intersect
    pos_1 = popQuery(queryStack);
    pos_2 = popQuery(queryStack);
    result = intersectList(pos_1, pos_2);
    pushQuery(queryStack, result);
  }else{
    //push 1 posting
    hitTNode = search(root, query);
    if(hitTNode != NULL){
      pushQuery(queryStack, hitTNode->pos);
    }else{
      pushQuery(queryStack, NULL);
    }
  }
}
