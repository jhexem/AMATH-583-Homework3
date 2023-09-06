#ifndef PROBLEM2HEADER_HPP
#define PROBLEM2HEADER_HPP

#include <vector>
#include <fstream>
#include <random>

void export_vector_to_csv(std::vector<int> vec1, std::vector<int> vec2);
template <typename T>
std::vector<T> create_random_matrix(int size);
template <typename T>
T create_random_number(T end_val);
int average_vector(std::vector<double> vec);

#endif