#ifndef HASH_H_
#define HASH_H_

#include <stdio.h>

void create_hash(const char* path, char* hash_summ);
void create_h_arr(unsigned* h, int n);
void create_k_arr(unsigned* k, int n);
void create_bin_arr(unsigned* h, unsigned* k, const char* path, char* hash_summ);
unsigned rotr(unsigned num, unsigned char shift);
void get_size_of_binary_file(FILE* file, size_t* size);
unsigned int create_32bit_num(double num);
void create_arr_simple_num(unsigned* h, int n);

#endif  // HASH_H_