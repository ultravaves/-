#include <stdio.h>
#include <stdlib.h>

int input(int **data, int *n);
void sort(int *data, int n);
void output(int *data, int n);

int main() {
  int *data, n;
  if (!input(&data, &n)) {
    sort(data, n);
    output(data, n);
    free(data);
  } else {
    printf("n/a");
  }
  return 0;
}
int input(int **data, int *n) {
  int err = 0;
  if (scanf("%d", n) && *n > 0) {
    *data = (int *)malloc(*n * sizeof(int));
    char ch;
    for (int i = 0; i < *n; i++) {
      if (scanf("%d", *data + i)) {
        ch = getchar();
        if ((ch != '\n' && ch != ' ') || (ch == '\n' && i < *n - 1) ||
            (ch != '\n' && i >= *n - 1)) {
          err = 1;
        }
      } else {
        err = 1;
      }
      if (err == 1) {
        break;
      }
    }
  } else {
    err = 1;
  }
  return err;
}
void sort(int *data, int n) {
  int i, j, tmp;
  for (i = 0; i < n - 1; i++) {
    for (j = i + 1; j < n; j++) {
      if (data[i] > data[j]) {
        tmp = data[j];
        data[j] = data[i];
        data[i] = tmp;
      }
    }
  }
}
void output(int *data, int n) {
  int i;
  for (i = 0; i < n - 1; i++) {
    printf("%d ", data[i]);
  }
  printf("%d", data[i]);
}
