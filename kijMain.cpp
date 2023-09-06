#include "hw3_p1_header.hpp"
#include <iostream>

int main() {

   int m = 2;
   int p = 3;
   int n = 2;

   int a = 2;
   int b = 3;

   const std::vector<float> A = {1.0f, 0.0f, 0.0f, 1.0f, 2.0f, 2.0f};
   const std::vector<float> B = {3.0f, 0.0f, 1.0f, 1.0f, 2.0f, 1.0f};
   std::vector<float> C = {1.0f, 1.0f, 1.0f, 0.0f};

   mm_kij<float>(a, A, B, b, C, m, p, n);
   
   int size = m*n;
   for (int i=0; i<size; i++) {
      std::cout << C[i] << std::endl;
   }
}