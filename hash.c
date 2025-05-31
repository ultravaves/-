#include "../include/hash.h"
#define __USE_MINGW_ANSI_STDIO 1
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
void create_hash(char *path, char *hash_summ) {
  unsigned h[8], k[64];
  create_h_arr(h, 8);
  create_k_arr(k, 64);
  create_bin_arr(h, k, path, hash_summ);
}
void create_bin_arr(unsigned *h, unsigned *k, char *path, char *hash_summ) {
  FILE *file = fopen(path, "r");
  if (file != NULL) {
    unsigned w[64];
    size_t size, size_64, num_block, i;
    unsigned char ch, j, m, byte_size = 8, last_pos_mess;
    get_size_of_binary_file(file, &size);
    last_pos_mess = size % 64;
    size_64 = size / 64 + 1;
    if (last_pos_mess < 56) {
      num_block = size_64;
    } else {
      num_block = size_64 + 1;
    }
    size *= 8;  // length of file in bit
    for (i = 0; i < num_block; i++) {
      for (m = 0, j = 0; m < 64; m++) {
        if (m % 4 == 0) {
          if (m != 0) {
            j++;
          }
          w[j] = 0;
        }
        if ((i < size_64 - 1) || (i == size_64 - 1 && m < last_pos_mess)) {
          fscanf(file, "%c", &ch);
          w[j] <<= 8;
          w[j] += (unsigned)ch;
        } else if (i == size_64 - 1 && m == last_pos_mess) {  // put one 1
          w[j] <<= 8;
          w[j] += 1 << 7;
        } else if (i != num_block - 1 || m < 56) {  // put zero
          w[j] <<= 8;
        } else if (byte_size > 0) {  // put length of source file
          w[j] = size >> (8 * (byte_size - 1));
          byte_size--;
        }
      }
      // generate adding 48 words to j [from 16 to 63]
      unsigned s0, s1;
      for (j = 16; j < 64; j++) {
        s0 = rotr(w[j - 15], 7) ^ rotr(w[j - 15], 18) ^ (w[j - 15] >> 3);
        s1 = rotr(w[j - 2], 17) ^ rotr(w[j - 2], 19) ^ (w[j - 2] >> 10);
        w[j] = w[j - 16] + s0 + w[j - 7] + s1;
      }
      unsigned A = h[0], B = h[1], C = h[2], D = h[3], E = h[4], F = h[5],
               G = h[6], H = h[7];
      unsigned Ma, t1, t2, Ch;
      for (j = 0; j < 64; j++) {
        s0 = rotr(A, 2) ^ rotr(A, 13) ^ rotr(A, 22);
        Ma = (A & B) ^ (A & C) ^ (B & C);
        t2 = s0 + Ma;
        s1 = rotr(E, 6) ^ rotr(E, 11) ^ rotr(E, 25);
        Ch = (E & F) ^ ((~E) & G);
        t1 = H + s1 + Ch + k[j] + w[j];
        H = G;
        G = F;
        F = E;
        E = D + t1;
        D = C;
        C = B;
        B = A;
        A = t1 + t2;
      }
      h[0] += A;
      h[1] += B;
      h[2] += C;
      h[3] += D;
      h[4] += E;
      h[5] += F;
      h[6] += G;
      h[7] += H;
    }
    fclose(file);
  } else {
    printf("n/a");
  }
  snprintf(hash_summ, 65, "%08x%08x%08x%08x%08x%08x%08x%08x", h[0], h[1], h[2],
           h[3], h[4], h[5], h[6], h[7]);
}
// rotate_right (0 <= num <= 32)
unsigned rotr(unsigned num, unsigned char shift) {
  return (num >> shift) | (num << (32 - shift));
}
// size of file <= 4 Gb
void get_size_of_binary_file(FILE *file, size_t *size) {
  fseeko64(file, 0, SEEK_END);
  *size = ftello64(file);
  fseeko64(file, 0, SEEK_SET);
}
// first 32 bit of fractional part square root of first 8 simple numbers
// [from 2 to 19]
void create_h_arr(unsigned *h, int n) {
  create_arr_simple_num(h, n);
  for (int i = 0; i < n; i++) {
    double num = sqrt(h[i]);
    num -= floor(num);
    h[i] = create_32bit_num(num);
  }
}
// first 32 bit of fractional part cube root of first 64 simple numbers
// [from 2 to 311]
void create_k_arr(unsigned *k, int n) {
  create_arr_simple_num(k, n);
  for (int i = 0; i < n; i++) {
    double num = cbrt(k[i]);
    num -= floor(num);
    k[i] = create_32bit_num(num);
  }
}
unsigned int create_32bit_num(double num) {
  int i, n = 32;
  unsigned int res = 0;
  for (i = -1; i >= n * -1; i--) {
    res <<= 1;
    if (num / pow(2, i) > 1) {
      res += 1;
      num -= pow(2, i);
    }
  }
  return res;
}
// n must be > 0
void create_arr_simple_num(unsigned *h, int n) {
  h[0] = 2;
  int num, flag_simple;
  for (int i = 1; i < n; i++) {
    num = h[i - 1] + 1;
    do {
      flag_simple = 1;
      for (int k = 0; k < i; k++) {
        if (num % h[k] == 0) {
          num += 1;
          flag_simple = 0;
          break;
        }
      }
    } while (flag_simple == 0);
    h[i] = num;
  }
}
