#include "Problem2Header.hpp"

void export_vector_to_csv (std::vector<int> vec1, std::vector<int> vec2) {
   std::ofstream file;
   file.open("results.csv");
   for (int i=0; i<vec1.size(); i++) {
      file << vec1[i] << "," << std::endl;
   }
   for (int i=0; i<vec2.size(); i++) {
      file << vec2[i] << "," << std::endl;
   }
   file.close();
}

template <typename T>
std::vector<T> create_random_matrix(int size) {

   std::vector<T> random_matrix(size);

   std::random_device dev;
   std::mt19937 rng(dev());
   std::uniform_real_distribution<T> dist(0,1);

   for (int i=0; i<size; i++) {
      T rNum = dist(rng);
      random_matrix[i] = rNum;
   }
   return random_matrix;
}

template <typename T>
T create_random_number(T end_val) {

   std::random_device dev;
   std::mt19937 rng(dev());
   std::uniform_real_distribution<T> dist(0,1);

   T rNum = dist(rng) * end_val;
   return rNum;
}

int average_vector(std::vector<double> vec) {
   double total = 0;
   for (int i=0; i<vec.size(); i++) {
      total += vec[i];
   }
   return (int)(total / (double)vec.size());
}

template std::vector<float> create_random_matrix(int size);
template std::vector<double> create_random_matrix(int size);

template float create_random_number(float end_val);
template double create_random_number(double end_val);