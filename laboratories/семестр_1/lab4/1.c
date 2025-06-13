#include <stdio.h>

int main() {
  int N;

  printf("Введите размер прямоугольника (N): ");
  scanf("%d", &N);

  int count = 1;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      printf("%d ", count);
      count++;
    }
    printf("\n");
  }

  return 0;
}
