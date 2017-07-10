/*
      ex3-1
      naka.b.aa
      Naka, Bunta    */
#include <stdio.h>
#include <stdlib.h>

struct complex {
  double re;
  double im;
};

struct complex multipleComplex(struct complex, struct complex);

int main(void) {
  struct complex cmp_1, cmp_2, cmp_res;

  //get comps
  scanf("%lf %lf", &(cmp_1.re), &(cmp_1.im));
  scanf("%lf %lf", &(cmp_2.re), &(cmp_2.im));

  //calc result
  cmp_res = multipleComplex(cmp_1, cmp_2);

  //print result
  printf("%.4f %.4f", cmp_res.re, cmp_res.im);
  return 0;
}

struct complex multipleComplex(struct complex cmp_1, struct complex cmp_2){
  struct complex cmp_res;

  cmp_res.re = cmp_1.re * cmp_2.re - cmp_1.im * cmp_2.im;
  cmp_res.im = cmp_1.im * cmp_2.re + cmp_1.re * cmp_2.im;

  return cmp_res;

}
