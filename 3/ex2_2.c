/*
      ex2-2
      naka.b.aa
      Naka, Bunta    */
#include <stdio.h>

#define WORD_LEN_MAX 16

int check_char(char,char);

int main(void) {
  char word_1[WORD_LEN_MAX], word_2[WORD_LEN_MAX];
  int word_len_1, word_len_2, hit_count, i;

  //get  words
  scanf("%s %s", word_1, word_2);

  //count word length
  i=word_len_1=0;
  while(*(word_1+i) != '\0'){
    word_len_1++;
    i++;
  }
  i=word_len_2=0;
  while(*(word_2+i) != '\0'){
    word_len_2++;
    i++;
  }

  //diff length
  if(word_len_1 != word_len_2){
    printf("False");
    return 0;
  }

  //count same chars
  hit_count=0;
  for(i=0;i<word_len_1;i++){
    if(check_char(*(word_1+i), *(word_2+i)) == 1)hit_count++;
  }

  //print result
  if (hit_count == word_len_1){
    printf("True");
  }else{
    printf("False");
  }
  return 0;
}

// check same char
int check_char(char c_1, char c_2){
  if(c_1 == c_2){
    //same char
    return 1;
  }else if((c_1 > 64 && c_1 < 91 && c_1+('a'-'A') == c_2) || (c_2 > 64 && c_2 < 91 && c_1 == c_2+('a'-'A'))){
    //same char (w/o caps)
    return 1;
  }
  return 0;
}
