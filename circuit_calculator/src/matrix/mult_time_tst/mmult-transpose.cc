#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <array>

#include "../matrix.hpp"

using cxx_containers::Matrix;

enum { BIG_AX = 2000, BIG_AY = 1600, BIG_BY = 1200 };

// to exclude silly errors
void smoketest() {
  std::array<int, 6> a = {1, 2, 3, 4, 5, 6};
  std::array<int, 2> b = {1, 2};

  Matrix<int> ma(a.begin(), a.end(), {3, 2});
  Matrix<int> mb(b.begin(), b.end(), {2, 1});
  Matrix<int> mc({3, 1});

  mc = ma * mb;

  assert(mc[0][0] == 5);
  assert(mc[1][0] == 11);
  assert(mc[2][0] == 17);
}

void matrix_rand_init(std::vector<int>& arr, int sz) {
  srand(time(NULL));
  for (int i = 0; i < sz; ++i)
    arr[i] = (rand() % 20) - 10;
}

int main () {
  clock_t start, fin;
  double diff;
  
  smoketest();

  std::vector<int> a(BIG_AX*BIG_AY);
  std::vector<int> b(BIG_AY*BIG_BY);
  std::vector<int> c(BIG_AX * BIG_BY);

  matrix_rand_init(a, BIG_AX * BIG_AY);
  matrix_rand_init(b, BIG_AY * BIG_BY);
  matrix_rand_init(c, BIG_AX * BIG_BY);

  Matrix<int> ma(a.begin(), a.end(), {BIG_AX, BIG_AY});
  Matrix<int> mb(b.begin(), b.end(), {BIG_AY, BIG_BY});
  Matrix<int> mc(c.begin(), c.end(), {BIG_AX, BIG_BY});
  
  start = clock();
  mc = ma * mb;
  fin = clock();
  
  diff = (double)(fin - start) / CLOCKS_PER_SEC;
  printf("Elapsed: %lg seconds\n", diff);
}
