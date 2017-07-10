/*
      ex2-1
      naka.b.aa
      Naka, Bunta    */
#include <stdio.h>

#define WORD_LEN_MAX 16

int get_char_len(char[WORD_LEN_MAX]);

int main(void) {
  char word_1[WORD_LEN_MAX], word_2[WORD_LEN_MAX];
  int word_len_1, word_len_2;

  //get  words
  scanf("%s %s", word_1, word_2);

  //count word length
  word_len_1 = get_char_len(word_1);
  word_len_2 = get_char_len(word_2);

  //diff length
  if(word_len_1 > word_len_2){
    printf("1");
  }else if(word_len_1 < word_len_2){
    printf("2");
  }else{
    printf("0");
  }

  return 0;
}

// check same char
int get_char_len(char word[WORD_LEN_MAX]){
  int i=0, word_len=0;
  while(*(word+i) != '\0'){
    word_len++;
    i++;
  }
  return word_len;
}
