#include "hw3_p1_header.hpp"
#include <iostream>

int main() {

   int m = 2;
   int p = 3;
   int n = 2;

   int a = 2;
   int b = 3;

   const std::vector<int> A = {1, 0, 0, 1, 2, 2};
   const std::vector<int> B = {3, 0, 1, 1, 2, 1};
   std::vector<int> C = {1, 1, 1, 0};

   mm_ikj<int>(a, A, B, b, C, m, p, n);
   
   int size = m*n;
   for (int i=0; i<size; i++) {
      std::cout << C[i] << std::endl;
   }
}