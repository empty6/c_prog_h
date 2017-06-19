/*
      ex1-3
      naka.b.aa
      Naka, Bunta    */
#include <stdio.h>
#define LIMIT_YEAR 1970

void backYesterday(int*, int*, int*);

int main(void) {
  int i, n, year, month, day;

  //get n
  scanf("%d", &n);
  scanf("%d/%d/%d", &year, &month, &day);


  //calc n days before
  for(i=0;i<n;i++){
    backYesterday(&year ,&month, &day);

    //check error
    if(year<LIMIT_YEAR){
      fprintf(stderr,"NAN");
      return 1;
    }
  }

  printf("%d/%d/%d", year, month, day);

  return 0;
}

//calc yestarday
void backYesterday(int *year ,int *month, int *day){
  if(*day==1){
    //get before month
    switch (*month) {
      case 1:
        *year -= 1;
        *month =12;
        *day = 31;
        break;
      case 3:
        *month = 2;
        //check leap
        *day = 28 + (*year%400==0 || (*year%100 !=0 && *year%4 == 0) ? 1 : 0);
        break;
      case 2:
      case 4:
      case 6:
      case 8:
      case 9:
      case 11:
        //(1,3,5,7,8,10) / 31
        *month -= 1;
        *day = 31;
        break;
      case 5:
      case 7:
      case 10:
      case 12:
        //(4,6,9,11) / 31
        *month -= 1;
        *day = 30;
        break;
    }
  }else{
    *day -= 1;
  }

}
