/*
      ex3-3
      naka.b.aa
      Naka, Bunta    */
#include <stdio.h>
#include <stdlib.h>

#define ROW_NUM 1000
#define ROW_LEN 202
#define WORD_LEN_MAX 16

int get_word_len(char[WORD_LEN_MAX]);
int check_char(char,char);

int main(int argc, char **argv) {
  FILE *fp;
  char *fname, **txt, row_temp[ROW_LEN], needle[WORD_LEN_MAX], needle_mirror[WORD_LEN_MAX];
  int input_count, needle_len, hit_count, find_count, i, j, len_temp;

  //get memory for column
  txt = malloc(sizeof(char*)*ROW_NUM);

  //get input file
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

  input_count = 0;
  while(fgets(row_temp, ROW_LEN, fp) != NULL){
    //get memory for row
    len_temp = get_word_len(row_temp) + 1;
    *(txt+input_count) = malloc(sizeof(char) * len_temp);
    //copy row
    for(i=0;i<len_temp;i++){
      *(*(txt+input_count)+i) = *(row_temp+i);
    }
    input_count++;
  }
  fclose(fp);

  //get needle word
  scanf("%s", needle);

  //count needle length
  needle_len = get_word_len(needle);

  //mirror needle
  for(i=0;i<needle_len;i++){
    needle_mirror[needle_len-i-1] = needle[i];
  }

  //search needle
  find_count=0; //hit flag
  for(i=0;i<input_count;i++){
    j=0;
    while(*(*(txt+i)+j) != '\0'){
      hit_count=0;
      //compare head char
      if(check_char(*(*(txt+i)+j), *needle_mirror) == 1){
        //hit head char -> check last chars
        hit_count = 1;
        while(hit_count < needle_len && *(*(txt+i)+hit_count) != '\0'){
          if(check_char(*(*(txt+i)+j+hit_count), *(needle_mirror+hit_count)) == 1){
            hit_count++;
          }else{
            break;
          }
        }
        //hit total needle
        if(hit_count == needle_len){
          find_count++;
          break;
        }
      }
      j++;
    }
  }

  //print result
  printf("%d", find_count);


  //free memory
  for(i=0;i<ROW_NUM;i++){
    free(*(txt+i));
  }
  free(txt);

  return 0;
}

// check same char
int get_word_len(char word[WORD_LEN_MAX]){
  int word_len=0;
  while(*(word+word_len) != '\0'){
    word_len++;
  }
  return word_len;
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
