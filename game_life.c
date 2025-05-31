
#include "../include/game_life.h"

#include <dir.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include "../include/hash.h"
int main(int argc, char* argv[]) {
  char** matrix = (char**)malloc(HEIGHT * sizeof(char*));
  for (int i = 0; i < HEIGHT; i++) {
    matrix[i] = (char*)malloc(WIDTH * sizeof(char));
  }
  int num_datasets;
  printf("Input number of datasets (1-5): ");
  scanf("%d", &num_datasets);
  char buf[PATH_MAX], path[PATH_MAX], path_datasets[PATH_MAX];
  snprintf(path_datasets, PATH_MAX, "datasets\\%d.txt", num_datasets);
  if (argc > 0) {
    char** lppPart = NULL;
    GetFullPathName(argv[0], PATH_MAX, buf, lppPart);
    int ptr = strlen(buf);
    for (int i = 0; i < 2; i++) {
      ptr--;
      while (buf[ptr] != '\\') {
        ptr--;
      }
    }
    buf[ptr + 1] = '\0';
    snprintf(path, PATH_MAX, "%s%s", buf, path_datasets);
  }
  system("cls");
  if (!setup(matrix, path)) {
    print(matrix);
    snprintf(path, PATH_MAX, "%smatrix.txt", buf);
    int size_hash_sum = 1, period = 0;
    char** hash_sum = (char**)malloc(size_hash_sum * sizeof(char*));
    for (int i = 0; i < size_hash_sum; i++) {
      hash_sum[i] = (char*)malloc(65 * sizeof(char));
    }
    write_hash(path, matrix, hash_sum, size_hash_sum - 1);
    do {
      system("cls");
      update(matrix);
      print(matrix);
      size_hash_sum++;
      hash_sum = (char**)realloc(hash_sum, size_hash_sum * sizeof(char*));
      hash_sum[size_hash_sum - 1] = (char*)malloc(65 * sizeof(char));
      write_hash(path, matrix, hash_sum, size_hash_sum - 1);
    } while (!check_exit(hash_sum, size_hash_sum, &period));
    printf("\nperiod of oscillator = %d\nsize of steps = %d", period,
           size_hash_sum);
    for (int i = 0; i < size_hash_sum; i++) {
      free(hash_sum[i]);
    }
    free(hash_sum);
  } else {
    printf("n/a");
  }
  for (int i = 0; i < HEIGHT; i++) {
    free(matrix[i]);
  }
  free(matrix);
  return 0;
}
int check_exit(char** hash_sum, int size_hash_sum, int* period) {
  int flag_exit = 0;
  for (int i = size_hash_sum - 2; i >= 0; i--) {
    if (!strcmp(hash_sum[i], hash_sum[size_hash_sum - 1])) {
      *period = size_hash_sum - 1 - i;
      flag_exit = 1;
      break;
    }
  }
  return flag_exit;
}
void write_hash(char* path, char** matrix, char** hash_sum, int i) {
  write_matrix_to_file(matrix, path);
  create_hash(path, hash_sum[i]);
  if (remove(path)) {
    printf("\nCan't remove file");
  }
}
void write_matrix_to_file(char** matrix, char* path) {
  FILE* file = fopen(path, "w");
  for (int i = 0; i < HEIGHT; i++) {
    fwrite(matrix[i], 1, WIDTH, file);
  }
  fclose(file);
}
int setup(char** matrix, char* path) {
  int flag_err = 0;
  FILE* file = fopen(path, "r");
  if (file) {
    char ch;
    for (int i = 0; i < HEIGHT; i++) {
      for (int j = 0; j < WIDTH; j++) {
        if (i == 0 || i == HEIGHT - 1) {
          matrix[i][j] = '=';
        } else if (j == 0 || j == WIDTH - 1) {
          matrix[i][j] = '|';
        } else {
          do {
            fscanf(file, "%c", &ch);
          } while (ch == '\n');
          if (ch == '-') {
            matrix[i][j] = ' ';
          } else if (ch == '1') {
            matrix[i][j] = '*';
          }
        }
      }
    }
    fclose(file);
  } else {
    flag_err = 1;
  }
  return flag_err;
}
void print(char** matrix) {
  char mess[2241];
  int k = 0;
  for (int i = 0; i < HEIGHT; i++) {
    for (int j = 0; j < WIDTH; j++) {
      mess[k] = matrix[i][j];
      k++;
    }
    if (i < HEIGHT - 1) {
      mess[k] = '\n';
      k++;
    } else if (i == HEIGHT - 1) {
      mess[k] = '\0';
    }
  }
  printf("%s", mess);
}
void update(char** matrix) {
  char new_matrix[HEIGHT][WIDTH];
  int i, j, y, x, yy, xx, neighbour;
  for (i = 1; i < HEIGHT - 1; i++) {
    for (j = 1; j < WIDTH - 1; j++) {
      neighbour = 0;
      for (y = i - 1; y <= i + 1; y++) {
        if (y == 0) {
          yy = HEIGHT - 2;
        } else if (y == HEIGHT - 1) {
          yy = 1;
        } else {
          yy = y;
        }
        for (x = j - 1; x <= j + 1; x++) {
          if (x == 0) {
            xx = WIDTH - 2;
          } else if (x == WIDTH - 1) {
            xx = 1;
          } else {
            xx = x;
          }
          if (!(y == i && x == j) && matrix[yy][xx] == '*') {
            neighbour++;
          }
        }
      }
      if (neighbour == 3 || (neighbour == 2 && matrix[i][j] == '*')) {
        new_matrix[i][j] = '*';
      } else {
        new_matrix[i][j] = ' ';
      }
    }
  }
  for (i = 1; i < HEIGHT - 1; i++) {
    for (j = 1; j < WIDTH - 1; j++) {
      matrix[i][j] = new_matrix[i][j];
    }
  }
}
