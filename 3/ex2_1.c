/*
      ex1-1
      naka.b.aa
      Naka, Bunta    */
#include <stdio.h>

void squareMatrix(int*);

int main(void) {
  int data[9];

  //get data
  scanf("%d %d %d %d %d %d %d %d %d",
    data, data+1, data+2, data+3, data+4, data+5, data+6, data+7, data+8);

  //exec data * data
  squareMatrix(data);

  //print data
  printf("%d %d %d %d %d %d %d %d %d",
    data[0], data[1], data[2], data[3], data[4], data[5], data[6], data[7], data[8]);
  return 0;
}

//calc mat*mat
void squareMatrix(int *mat){
  int i, j, k, ret_mat[9];

  //calc mat * mat
  for(i=0;i<3;i++){
    for(j=0;j<3;j++){
      ret_mat[i*3+j] = 0;
      //[i][0]*[0][j] + [i][1]*[1][j] + [i][2]*[2][j]
      for(k=0;k<3;k++){
        ret_mat[i*3+j] += *(mat+i*3+k) * *(mat+k*3+j);
      }
    }
  }

  //copy ret -> mat
  for(i=0;i<3;i++){
    for(j=0;j<3;j++){
      *(mat+i*3+j) = *(ret_mat+i*3+j);
    }
  }
}
