#include "hw3_p1_header.hpp"

template<typename T>
void mm_kij(T a, const std::vector<T>& A, const std::vector<T>& B, T b, std::vector<T>&C, int m, int p, int n) {

   int size = n*m;
   std::vector<T> ABresult(size, static_cast<T>(0));

   for (int k=0; k<n; k++) {
      for (int i=0; i<m; i++) {
         for (int j=0; j<p; j++) {
            ABresult[i+k*n] += A[i+j*m] * B[j+k*p];
         }
      }
   }

   for (int i=0; i<size; i++) {
      C[i] = a * ABresult[i] + b * C[i];
   }
}

template void mm_kij<int> (int a, const std::vector<int>& A, const std::vector<int>& B, int b, std::vector<int>&C, int m, int p, int n);
template void mm_kij<float> (float a, const std::vector<float>& A, const std::vector<float>& B, float b, std::vector<float>&C, int m, int p, int n);
template void mm_kij<double> (double a, const std::vector<double>& A, const std::vector<double>& B, double b, std::vector<double>&C, int m, int p, int n);