#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <ctime>

#include "../matrix.hpp"

using cxx_containers::Matrix;

enum { BIG_AX = 2000, BIG_AY = 1600, BIG_BY = 1200 };

// to exclude silly errors
void smoketest() {
  int a[3][2] = {{1, 2}, {3, 4}, {5, 6}};
  int b[2][1] = {{1}, {2}};
  int c[3][1];

  Matrix<int> ma(&a[0][0], 3, 2);
  Matrix<int> mb(&b[0][0], 2, 1);
  Matrix<int> mc(&c[0][0], 3, 1);

  mc = ma * mb;

  assert(mc[0][0] == 5);
  assert(mc[1][0] == 11);
  assert(mc[2][0] == 17);
}

void matrix_rand_init(int *arr, int sz) {
  srand(time(NULL));
  for (int i = 0; i < sz; ++i)
    arr[i] = (rand() % 20) - 10;
}

int
main () {
  clock_t start, fin;
  double diff;
  
  smoketest();

  int (*a)[BIG_AY] = (int (*)[BIG_AY]) malloc(BIG_AX * BIG_AY * sizeof(int));
  int (*b)[BIG_BY] = (int (*)[BIG_BY]) malloc(BIG_AY * BIG_BY * sizeof(int)); 
  int (*c)[BIG_BY] = (int (*)[BIG_BY]) malloc(BIG_AX * BIG_BY * sizeof(int));

  matrix_rand_init(&a[0][0], BIG_AX * BIG_AY);
  matrix_rand_init(&b[0][0], BIG_AY * BIG_BY);
  matrix_rand_init(&c[0][0], BIG_AX * BIG_BY);

  Matrix<int> ma(&a[0][0], BIG_AX, BIG_AY);
  Matrix<int> mb(&b[0][0], BIG_AY, BIG_BY);
  Matrix<int> mc(&c[0][0], BIG_AX, BIG_BY);
  
  start = clock();
  mc = ma * mb;
  fin = clock();
  
  diff = (double)(fin - start) / CLOCKS_PER_SEC;
  printf("Elapsed: %lg seconds\n", diff);
  
  free(c);
  free(b);
  free(a);
}
