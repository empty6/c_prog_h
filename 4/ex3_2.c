/*
      ex3-2
      naka.b.aa
      Naka, Bunta    */
#include <stdio.h>
#include <stdlib.h>

#define COMPLEX_NUM 3

struct complex {
  double re;
  double im;
};

struct complex multipleComplex(struct complex, struct complex);

int main(void) {
  struct complex *cmp;

  //get memory
  cmp = malloc(sizeof(struct complex) * COMPLEX_NUM);
  if(cmp == NULL){
    printf("Can not allocate memory.\n");
    return 1;
  }

  //get comps
  scanf("%lf %lf", &(cmp[0].re), &(cmp[0].im));
  scanf("%lf %lf", &(cmp[1].re), &(cmp[1].im));

  //calc result
  cmp[2] = multipleComplex(cmp[0], cmp[1]);

  //print result
  printf("%.4f %.4f", cmp[2].re, cmp[2].im);

  //free memory
  free(cmp);

  return 0;
}


struct complex multipleComplex(struct complex cmp_1, struct complex cmp_2){
  struct complex cmp_res;

  cmp_res.re = cmp_1.re * cmp_2.re - cmp_1.im * cmp_2.im;
  cmp_res.im = cmp_1.im * cmp_2.re + cmp_1.re * cmp_2.im;

  return cmp_res;

}
