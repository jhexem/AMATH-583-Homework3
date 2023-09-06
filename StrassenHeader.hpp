#ifndef STRASSENHEADER_HPP
#define STRASSENHEADER_HPP

#include <iostream>
#include <vector>
#include <random>
#include <fstream>
#include <exception>

template <typename T>
std::vector<std::vector<T>> strassen_mm(const std::vector<std::vector<T>> &A, const std::vector<std::vector<T>> &B);
template <typename T>
void strip_zeros(std::vector<std::vector<T>> &matrix, int original_size);
template <typename T>
std::vector<std::vector<T>> power_of_two_strassen(const std::vector<std::vector<T>> &A, const std::vector<std::vector<T>> &B);
template <typename T>
std::vector<std::vector<std::vector<T>>> split_matrix_into_blocks(const std::vector<std::vector<T>> &matrix);
template <typename T>
std::vector<std::vector<T>> build_matrix_from_blocks(std::vector<std::vector<T>> upper_left, std::vector<std::vector<T>> upper_right, std::vector<std::vector<T>> lower_left, std::vector<std::vector<T>> lower_right);
template <typename T>
void add(std::vector<std::vector<T>> A, std::vector<std::vector<T>> B, std::vector<std::vector<T>> &result);
template <typename T>
void sub(std::vector<std::vector<T>> A, std::vector<std::vector<T>> B, std::vector<std::vector<T>> &result);
template <typename T>
std::vector<std::vector<T>> matrix_identity(int size);
template <typename T>
void print_matrix (std::vector<std::vector<T>> matrix);
template <typename T>
std::vector<std::vector<T>> matrix_ones(int size);
template <typename T>
std::vector<std::vector<T>> create_random_matrix(int size);
int average_vector(std::vector<double> vec);
void export_vector_to_csv(std::vector<int> vec);

#endif