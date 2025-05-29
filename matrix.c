#include <stdio.h>
#include <stdlib.h>
#define NMAX 100

int input_menu(int *n);
int input1(int **data);  // static
int input2(int **data);  //
int input3(int **data);  //
int input4(int **data);  //
// void output(int **data);

int main() {
  int /**data,*/ n;
  if (!input_menu(&n)) {
    // output(data, n);
    // free(data);
  } else {
    printf("n/a");
  }
  return 0;
}

int input_menu(int *n) {
  int err = 0;
  printf("Input method of creating array (1, 2, 3, 4): ");
  if (scanf("%d", n) && *n > 0) {
  } else {
    err = 1;
  }
  return err;
}
// int input1(int **data) {
//   *data = (int *)malloc(*n * sizeof(int));
//   char ch;
//   for (int i = 0; i < *n; i++) {
//     if (scanf("%d", *data + i)) {
//       ch = getchar();
//       if ((ch != '\n' && ch != ' ') || (ch == '\n' && i < *n - 1) ||
//           (ch != '\n' && i >= *n - 1)) {
//         err = 1;
//       }
//     } else {
//       err = 1;
//     }
//     if (err == 1) {
//       break;
//     }
//   }
// }
// int input2(int **data) {}
// int input3(int **data) {}
// int input4(int **data) {}

// void output(int *data, int n) {
//   int i;
//   for (i = 0; i < n - 1; i++) {
//     printf("%d ", data[i]);
//   }
//   printf("%d", data[i]);
// }
