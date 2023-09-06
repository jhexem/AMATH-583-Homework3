#include "StrassenHeader.hpp"
#include <chrono>

int main() {

   int n_start = 2;
   int n_end = 512;

   double num_flops;
   std::vector<int> average_times_in_flops;
   
   int ntrial = 3;

   for (int n=n_start; n<=n_end; n+=2) {

      num_flops = (7.0/4.0)*n*n*n + (9.0/2.0)*n*n;
      std::vector<double> times_in_flops;

      const std::vector<std::vector<double>> A = create_random_matrix<double>(n);
      const std::vector<std::vector<double>> B = create_random_matrix<double>(n);

      for (int i=0; i<ntrial; i++) {
         auto start = std::chrono::high_resolution_clock::now();
         std::vector<std::vector<double>> C = strassen_mm(A, B);
         auto stop = std::chrono::high_resolution_clock::now();
         auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
         times_in_flops.push_back((num_flops * 1000.0) / (double)duration.count());
      }
      average_times_in_flops.push_back(average_vector(times_in_flops));
      times_in_flops.clear();
      std::cout << "n = " << n << " complete." << std::endl;
   }
   export_vector_to_csv(average_times_in_flops);

   return 0;
}