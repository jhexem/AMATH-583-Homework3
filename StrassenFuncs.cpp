#include "StrassenHeader.hpp"

template <typename T>
std::vector<std::vector<T>> strassen_mm(const std::vector<std::vector<T>> &A, const std::vector<std::vector<T>> &B) {

   int size = A.size();
   int sizeAcols = A[0].size();
   int sizeB = B.size();
   int sizeBcols = B[0].size();

   if (sizeAcols!=sizeB) {
      throw std::invalid_argument("Matrix dimensions do not match.");
   }
   else {
      int n = 2;

      while (n<size) {
         n *= 2;
      }
      //std::cout << "size is: " << size << " n is: " << n << std::endl;

      if (size == n) return power_of_two_strassen(A, B);
      else {
         //std::cout << "Ran else" << std::endl;
         std::vector<std::vector<T>> padA(n, std::vector<T>(n, (T)0.0));
         std::vector<std::vector<T>> padB(n, std::vector<T>(n, (T)0.0));

         for (int row=0; row<size; row++) {
            for (int col=0; col<size; col++) {
               padA[row][col] += A[row][col];
               padB[row][col] += B[row][col];
            }
         }

         std::vector<std::vector<T>> C = power_of_two_strassen(padA, padB);
         strip_zeros(C, size);
         return C;
      }
   }
}

template <typename T>
std::vector<std::vector<T>> power_of_two_strassen(const std::vector<std::vector<T>> &A, const std::vector<std::vector<T>> &B) {

   int size = A.size();
   int half = (int)(size/2);
   //std::cout << "A: " << std::endl;
   //print_matrix(A);
   //std::cout << "B: " << std::endl;
   //print_matrix(B);

   if (size == 1) {
      return std::vector<std::vector<T>>(1, std::vector<T>(1, A[0][0] * B[0][0]));
   }
   else {
      std::vector<std::vector<std::vector<T>>> A_blocks = split_matrix_into_blocks(A);
      std::vector<std::vector<std::vector<T>>> B_blocks = split_matrix_into_blocks(B);

      std::vector<std::vector<T>> Aresult(half, std::vector<T>(half));
      std::vector<std::vector<T>> Bresult(half, std::vector<T>(half));
      std::vector<std::vector<T>> Cresult(half, std::vector<T>(half));
      std::vector<std::vector<T>> Dresult(half, std::vector<T>(half));

      add<T>(A_blocks[0], A_blocks[3], Aresult);
      add<T>(B_blocks[0], B_blocks[3], Bresult);
      std::vector<std::vector<T>> P1 = power_of_two_strassen(Aresult, Bresult);
      //std::cout << "P1 is: " << std::endl;
      //print_matrix(P1);

      add<T>(A_blocks[2], A_blocks[3], Aresult);
      std::vector<std::vector<T>> P2 = power_of_two_strassen(Aresult, B_blocks[0]);
      //std::cout << "P2 is: " << std::endl;
      //print_matrix(P2);

      sub<T>(B_blocks[1], B_blocks[3], Bresult);
      std::vector<std::vector<T>> P3 = power_of_two_strassen(A_blocks[0], Bresult);
      //std::cout << "P3 is: " << std::endl;
      //print_matrix(P3);

      sub<T>(B_blocks[2], B_blocks[0], Bresult);
      std::vector<std::vector<T>> P4 = power_of_two_strassen(A_blocks[3], Bresult);
      //std::cout << "P4 is: " << std::endl;
      //print_matrix(P4);

      add<T>(A_blocks[0], A_blocks[1], Aresult);
      std::vector<std::vector<T>> P5 = power_of_two_strassen(Aresult, B_blocks[3]);
      //std::cout << "P5 is: " << std::endl;
      //print_matrix(P5);

      sub<T>(A_blocks[2], A_blocks[0], Aresult);
      add<T>(B_blocks[0], B_blocks[1], Bresult);
      std::vector<std::vector<T>> P6 = power_of_two_strassen(Aresult, Bresult);
      //std::cout << "P6 is: " << std::endl;
      //print_matrix(P6);

      sub<T>(A_blocks[1], A_blocks[3], Aresult);
      add<T>(B_blocks[2], B_blocks[3], Bresult);
      std::vector<std::vector<T>> P7 = power_of_two_strassen(Aresult, Bresult);
      //std::cout << "P7 is: " << std::endl;
      //print_matrix(P7);
   

      //std::cout << "Upper left block:" << std::endl;
      sub<T>(P4, P5, Aresult);
      //std::cout << "P4 - P5 is: ";
      //print_matrix(Aresult);
      add<T>(P1, P7, Bresult);
      //std::cout << "P5 + P7 is: ";
      //print_matrix(Bresult);
      add<T>(Aresult, Bresult, Cresult);// Upper left block
      //std::cout << "Final Value is: ";
      //print_matrix(Cresult);

      //std::cout << "Lower right block:" << std::endl;
      sub<T>(P3, P2, Aresult);
      //std::cout << "P3 - P2 is: ";
      //print_matrix(Aresult);
      add<T>(P1, P6, Bresult);
      //std::cout << "P1 + P6 is: ";
      //print_matrix(Bresult);
      add<T>(Aresult, Bresult, Dresult);// Lower right block
      //std::cout << "Final Value is: ";
      //print_matrix(Dresult);

      //std::cout << "Upper right block:" << std::endl;
      add<T>(P3, P5, Aresult);//Upper right block
      //print_matrix(Aresult);

      //std::cout << "Lower left block:" << std::endl;
      add<T>(P2, P4, Bresult);  // Lower left block
      //print_matrix(Bresult);

      std::vector<std::vector<T>> combinedMatrix = build_matrix_from_blocks(Cresult, Aresult, Bresult, Dresult);
      //std::cout << "Combined Matrix is: " << std::endl;
      //print_matrix(combinedMatrix);

      return combinedMatrix;
   }
}

template <typename T>
std::vector<std::vector<std::vector<T>>> split_matrix_into_blocks(const std::vector<std::vector<T>> &matrix) {

   int size = matrix.size();
   int half = size / 2;
   std::vector<std::vector<std::vector<T>>> result_tensor;

   std::vector<std::vector<T>> upper_right(half, std::vector<T>(half));
   std::vector<std::vector<T>> upper_left(half, std::vector<T>(half));
   std::vector<std::vector<T>> lower_right(half, std::vector<T>(half));
   std::vector<std::vector<T>> lower_left(half, std::vector<T>(half));

   for (int row=0; row<size; row++) {
      if (row<half) {
         for (int col=0; col<size; col++) {
            if (col<half) {
               upper_right[row][col] = matrix[row][col];
            }
            else {
               upper_left[row][col-half] = matrix[row][col];
            }
         }
      }
      else {
         for (int col=0; col<size; col++) {
            if (col<half) {
               lower_right[row-half][col] = matrix[row][col];
            }
            else {
               lower_left[row-half][col-half] = matrix[row][col];
            }
         }
      }
   }

   result_tensor.push_back(upper_right);
   result_tensor.push_back(upper_left);
   result_tensor.push_back(lower_right);
   result_tensor.push_back(lower_left);

   return result_tensor;
}

template <typename T>
std::vector<std::vector<T>> build_matrix_from_blocks(std::vector<std::vector<T>> upper_left, std::vector<std::vector<T>> upper_right, std::vector<std::vector<T>> lower_left, std::vector<std::vector<T>> lower_right) {

   int half = upper_left.size();
   int size = 2 * half;
   std::vector<std::vector<T>> result_matrix(size, std::vector<T>(size));

   for (int row=0; row<size; row++) {
      if (row<half) {
         for (int col=0; col<size; col++) {
            if (col<half) {
               result_matrix[row][col] = upper_left[row][col];
            }
            else {
               result_matrix[row][col] = upper_right[row][col-half];
            }
         }
      }
      else {
         for (int col=0; col<size; col++) {
            if (col<half) {
               result_matrix[row][col] = lower_left[row-half][col];
            }
            else {
               result_matrix[row][col] = lower_right[row-half][col-half];
            }
         }
      }
   }
   return result_matrix;
}

template <typename T>
void strip_zeros(std::vector<std::vector<T>> &matrix, int original_size) {

   int size = matrix.size();
   int num_zeros = size - original_size;
   for (int row=0; row<original_size; row++) {
      for (int col=0; col<num_zeros; col++) {
         matrix[row].pop_back();
      }
   }
   for (int row=0; row<num_zeros; row++) {
      matrix.pop_back();
   }
}

template <typename T>
void add(std::vector<std::vector<T>> A, std::vector<std::vector<T>> B, std::vector<std::vector<T>> &result) {

   int size = A.size();

   for (int row=0; row<size; row++) {
      for (int col=0; col<size; col++) {
         result[row][col] = A[row][col] + B[row][col];
      }
   }
}

template <typename T>
void sub(std::vector<std::vector<T>> A, std::vector<std::vector<T>> B, std::vector<std::vector<T>> &result) {

   int size = A.size();

   for (int row=0; row<size; row++) {
      for (int col=0; col<size; col++) {
         result[row][col] = A[row][col] - B[row][col];
      }
   }
}

template <typename T>
std::vector<std::vector<T>> matrix_identity(int size) {

   std::vector<std::vector<T>> matrix;

   for (int i=0; i<size; i++) {
      std::vector<T> row;
      for (int j=0; j<size; j++) {
         if (i==j) row.push_back(1.0);
         else row.push_back(0.0);
      }
      matrix.push_back(row);
   }
   return matrix;
}

template <typename T>
std::vector<std::vector<T>> matrix_ones(int size) {

   std::vector<std::vector<T>> matrix;

   for (int i=0; i<size; i++) {
      std::vector<T> row;
      for (int j=0; j<size; j++) {
         row.push_back(1.0);
      }
      matrix.push_back(row);
   }
   return matrix;
}

template <typename T>
void print_matrix (std::vector<std::vector<T>> matrix) {
   for (int i=0; i<matrix.size(); i++) {
      for (int j=0; j<matrix[i].size(); j++) {
         std::cout << matrix[i][j] << " ";
      }
      std::cout << std::endl;
   }
   std::cout << std::endl;
}

template <typename T>
std::vector<std::vector<T>> create_random_matrix(int size) {

   std::vector<std::vector<T>> random_matrix;

   std::random_device dev;
   std::mt19937 rng(dev());
   std::uniform_real_distribution<T> dist(0,1);

   for (int i=0; i<size; i++) {
      std::vector<T> new_row;

      for (int j=0; j<size; j++) {
         T rNum = dist(rng);
         new_row.push_back(rNum);
      }
      random_matrix.push_back(new_row);
   }
   return random_matrix;
}

int average_vector(std::vector<double> vec) {
   int total = 0;
   for (int i=0; i<vec.size(); i++) {
      total += vec[i];
   }
   return (int)(total / vec.size());
}

void export_vector_to_csv(std::vector<int> vec) {
   std::ofstream file;
   file.open("results.csv");
   for (int i=0; i<vec.size(); i++) {
      file << vec[i] << "," << std::endl;
   }
   file.close();
}

template std::vector<std::vector<float>> strassen_mm(const std::vector<std::vector<float>> &A, const std::vector<std::vector<float>> &B);
template std::vector<std::vector<double>> strassen_mm(const std::vector<std::vector<double>> &A, const std::vector<std::vector<double>> &B);

template std::vector<std::vector<float>> power_of_two_strassen(const std::vector<std::vector<float>> &A, const std::vector<std::vector<float>> &B);
template std::vector<std::vector<double>> power_of_two_strassen(const std::vector<std::vector<double>> &A, const std::vector<std::vector<double>> &B);

template void strip_zeros(std::vector<std::vector<float>> &matrix, int original_size);
template void strip_zeros(std::vector<std::vector<double>> &matrix, int original_size);

template std::vector<std::vector<std::vector<float>>> split_matrix_into_blocks(const std::vector<std::vector<float>> &matrix);
template std::vector<std::vector<std::vector<double>>> split_matrix_into_blocks(const std::vector<std::vector<double>> &matrix);

template std::vector<std::vector<float>> build_matrix_from_blocks(std::vector<std::vector<float>> upper_left, std::vector<std::vector<float>> upper_right, std::vector<std::vector<float>> lower_left, std::vector<std::vector<float>> lower_right);
template std::vector<std::vector<double>> build_matrix_from_blocks(std::vector<std::vector<double>> upper_left, std::vector<std::vector<double>> upper_right, std::vector<std::vector<double>> lower_left, std::vector<std::vector<double>> lower_right);

template void add(std::vector<std::vector<float>> A, std::vector<std::vector<float>> B, std::vector<std::vector<float>> &result);
template void add(std::vector<std::vector<double>> A, std::vector<std::vector<double>> B, std::vector<std::vector<double>> &result);

template void sub(std::vector<std::vector<float>> A, std::vector<std::vector<float>> B, std::vector<std::vector<float>> &result);
template void sub(std::vector<std::vector<double>> A, std::vector<std::vector<double>> B, std::vector<std::vector<double>> &result);

template std::vector<std::vector<float>> matrix_identity(int size);
template std::vector<std::vector<double>> matrix_identity(int size);

template void print_matrix (std::vector<std::vector<float>> matrix);
template void print_matrix (std::vector<std::vector<double>> matrix);

template std::vector<std::vector<float>> matrix_ones(int size);
template std::vector<std::vector<double>> matrix_ones(int size);

template std::vector<std::vector<float>> create_random_matrix(int size);
template std::vector<std::vector<double>> create_random_matrix(int size);