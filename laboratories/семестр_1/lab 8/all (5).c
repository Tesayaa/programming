#include <stdio.h>

int main() {
  double det;
  int size;
  printf("Введите размер матрицы (2 или 3): ");
  scanf("%d", &size);
  double matrix [size][size];
    

    for (int i = 0; i < size; i++ )  // size 2x2
    {
            for (int j = 0; j < size; j++ ) {
                 printf("matrix[%d][%d]: ", i, j);
                scanf("%lf", &matrix [i][j]);
            }

    }
  if (size == 2) {
    printf("Введите элементы матрицы 2x2:\n");

 

    det = matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];

    printf("Определитель матрицы: %.2lf\n", det);
  } else if (size == 3) {
    printf("Введите элементы матрицы 3x3:\n");
  

    det = matrix[0][0] * (matrix[1][1]  * matrix[2][2]  - matrix[2][1]  * matrix[1][2] ) - matrix[1][0] * (matrix[0][1]  * matrix[2][2]  - matrix[2][1]  * matrix[0][2] ) + matrix[2][0] * (matrix[0][1]  * matrix[1][2]  - matrix[1][1]  * matrix[0][2] );
    printf("1 det %lf \n", matrix[1][0] * (matrix[0][1]  * matrix[2][2]  - matrix[2][1]  * matrix[0][2] ));
    printf("Определитель матрицы: %.2lf\n", det);
  } else {
    printf("Неверный размер матрицы.\n");
  }

  return 0;
}