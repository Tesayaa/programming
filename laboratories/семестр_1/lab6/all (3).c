#include <stdio.h>

const int d = 10;

int main() {
  double A[d] = {1.0, 2.0, 3.0, 4.0, 5.0};
  double B[d] = {11.0, -12.0, 13.0, 14.0, -15.0};
  double C[d] = {0.0, 0.0, 0.0, 0.0, 0.0};

  double maxReal = A[0];
  for (int i = 1; i < d; i++) {
    if (A[i] > maxReal) {
      maxReal = A[i];
    }
  }

  int otricmnim = 0;
  for (int i = 0; i < d; i++) {
    if (B[i] < 0) {
      otricmnim++;
    }
  }

  for (int i = 0; i < d; i++) {
    C[i] += A[i] + B[i];
  }

  double sumC = 0;
  for (int i = 0; i < d; i++) {
    sumC += C[i];
  }
  double avgC = sumC / 2 * d;

  printf("Максимальная действительная часть в A: %.2lf\n", maxReal);
  printf("Количество мнимых частей меньше 0 в B: %d\n", otricmnim);
  printf("Среднее арифметическое в C: %.2lf\n", avgC);

  return 0;
}