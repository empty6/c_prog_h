/*
      ex2-3
      naka.b.aa
      Naka, Bunta    */
#include <stdio.h>

#define ROW_NUM 1000
#define ROW_LEN 202
#define NEEDLE_LEN_MAX 16

int check_char(char,char);

int main(int argc, char **argv) {
  FILE *fp;
  char txt[ROW_NUM][ROW_LEN], needle[NEEDLE_LEN_MAX], *fname;
  int input_count, needle_len, hit_count, find_f, i, j;

  //get input file
  if(argc!=2){
    fprintf(stderr, "Usage: %s prob_file\n", argv[0]);
  }
  fname = argv[1];

  fp = fopen(fname, "r");
  if(fp==NULL){
    fprintf(stderr,"input file error");
    return 1;
  }
  input_count = 0;
  while(fgets(*(txt+input_count), ROW_LEN, fp) != NULL){input_count++;}
  fclose(fp);

  //get needle word
  scanf("%s", needle);
  //count needle length
  i=needle_len=0;
  while(*(needle+i) != '\0'){
    needle_len++;
    i++;
  }

  //search needle
  find_f=0; //hit flag
  for(i=0;i<input_count;i++){
    j=0;
    while(*(*(txt+i)+j) != '\0'){
      hit_count=0;
      //compare head char
      if(check_char(*(*(txt+i)+j), *needle) == 1){
        //hit head char -> check last chars
        hit_count = 1;
        while(hit_count < needle_len && *(*(txt+i)+hit_count) != '\0'){
          if(check_char(*(*(txt+i)+j+hit_count), *(needle+hit_count)) == 1){
            hit_count++;
          }else{
            break;
          }
        }

        //hit total needle
        if(hit_count == needle_len){
          if(find_f == 0){
            find_f = 1;
          }else{
            printf(" ");
          }
          //print row
          printf("%d", i+1);
          break;
        }
      }
      j++;
    }
  }

  //not found
  if (find_f == 0){
    printf("Not found");
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
