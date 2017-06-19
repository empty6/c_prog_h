/*
      ex1-2
      naka.b.aa
      Naka, Bunta    */
#include <stdio.h>

void calcFib(int,int*);
void printFib(int,int*);

int* p_head;

int main(void) {
  int n;

  //get n
  scanf("%d", &n);

  int fib_arr[n];
  p_head = fib_arr;

  //calc fibonacci
  calcFib(n, fib_arr);

  //print data
  printFib(n, fib_arr);

  return 0;
}

//calc fibonacci
void calcFib(int n, int *fib){
  if(fib - p_head == 0){
    *fib = 0;
    calcFib(n, ++fib);
  }else if(fib - p_head == 1){
    *fib = 1;
    calcFib(n, ++fib);
  }else if(fib - p_head > n){
    //end
    return;
  }else{
    *fib = *(fib-1) + *(fib-2);
    calcFib(n, ++fib);
  }
}

//print fibonacci
void printFib(int n, int *fib){
  int i;
  for(i=0;i<=n;i++){
    if(i == 0){
      printf("%d", fib[0]);
    }else{
      printf(" %d", fib[i]);
    }
  }
}
