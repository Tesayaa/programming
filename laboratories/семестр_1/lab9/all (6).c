#include <stdio.h>
#include <stdlib.h>

int kakashka(int n,int matrix[n][n], int min_row, int min_col, double min_val){

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (matrix[i][j] < min_val) {
                min_val = matrix[i][j];
                min_row = i;
                min_col = j;
            }
        }
    }
}

int main() {
    int min_row = 0, min_col = 0;
    double min_val = 1e30;
    int n;
    printf("Введите размер квадратной матрицы: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Размер матрицы должен быть положительным числом.\n");
        return 1;
    }

    double matrix = (double )malloc(n * sizeof(double *));
    for (int i = 0; i < n; i++) {
        matrix[i] = (double *)malloc(n * sizeof(double));
        if (matrix[i] == NULL) {
            perror("Ошибка выделения памяти");
            return 1;
        }
    }

    printf("Введите элементы матрицы:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%lf", &matrix[i][j]);
        }
    }

    kakashka(n, matrix, min_row, min_col, min_val);
    int size_square = n - min_row > n - min_col ? n - min_col : n - min_row;
    double multiplier;
    printf("Введите множитель: ");
    scanf("%lf", &multiplier);

    double sum = 0;
    for (int i = min_row; i < min_row + size_square; i++) {
        for (int j = min_col; j < min_col + size_square; j++) {
            matrix[i][j] *= multiplier;
            sum += matrix[i][j];
        }
    }

    printf("Сумма элементов квадрата: %.2lf\n", sum);

    double arr[5*5];
    int k=0;
    for (int i = min_row; i < min_row + size_square; i++)
        for(int j=min_col; j< min_col + size_square; ++j)
            arr[k++] = matrix[i][j];

    printf("Массив из элементов квадрата:\n");
    for(int i=0; i< size_square*size_square; ++i) printf("%.2lf ", arr[i]);
    printf("\n");

    for (int i = 0; i < n; i++) free(matrix[i]);
    free(matrix);

    return 0;
}