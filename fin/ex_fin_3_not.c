lnode* notList(lnode *l1, lnode *l2){
  lnode *first=NULL;

  while(l1 != NULL && l2 != NULL){
    if(l1->docId < l2->docId){
      insertList(&first, l1->docId);
      l1 = l1->next;
    }else if(l1->docId > l2->docId){
    l2 = l2->next;
    }else{
      l2 = l2->next;
      l1 = l1->next;
    }
  }
  return first;
}
