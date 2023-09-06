#include "Problem2Header.hpp"
#include "kijHeader.hpp"
#include "jkiHeader.hpp"
#include <chrono>
#include <iostream>

int main() {

   int n_start = 2;
   int n_end = 512;

   float rand_int_end_val = 10;

   int num_flops;
   std::vector<int> average_times_in_flops1;
   std::vector<int> average_times_in_flops2;
   
   int ntrial = 3;

   for (int n=n_start; n<=n_end; n++) {

      num_flops = 2 * n * n * n + 2 * n * n;
      std::vector<double> times_in_flops1;
      std::vector<double> times_in_flops2;

      double a = create_random_number<double>(rand_int_end_val);
      double b = create_random_number<double>(rand_int_end_val);
      const std::vector<double> A = create_random_matrix<double>(n*n);
      const std::vector<double> B = create_random_matrix<double>(n*n);

      for (int i=0; i<ntrial; i++) {
         std::vector<double> C1 = create_random_matrix<double>(n*n);

         auto start1 = std::chrono::high_resolution_clock::now();
         mm_kij<double>(a, A, B, b, C1, n, n, n);
         auto stop1 = std::chrono::high_resolution_clock::now();
         auto duration1 = std::chrono::duration_cast<std::chrono::nanoseconds>(stop1 - start1);
         times_in_flops1.push_back(((double)num_flops * 1000.0) / (double)duration1.count());

         std::vector<double> C2 = create_random_matrix<double>(n*n);

         auto start2 = std::chrono::high_resolution_clock::now();
         mm_jki<double>(a, A, B, b, C2, n, n, n);
         auto stop2 = std::chrono::high_resolution_clock::now();
         auto duration2 = std::chrono::duration_cast<std::chrono::nanoseconds>(stop2 - start2);
         times_in_flops2.push_back(((double)num_flops * 1000.0) / (double)duration2.count());
      }
      average_times_in_flops1.push_back(average_vector(times_in_flops1));
      average_times_in_flops2.push_back(average_vector(times_in_flops2));
      times_in_flops1.clear();
      times_in_flops2.clear();
      std::cout << "n = " << n << " complete." << std::endl;
   }
   export_vector_to_csv(average_times_in_flops1, average_times_in_flops2);

   return 0;
}