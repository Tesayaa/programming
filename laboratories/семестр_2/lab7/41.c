#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct {
    int thread_id;
    int **A;
    int **B;
    int **C;
    int N;
    int start_row;
    int end_row;
} ThreadData;

void* multiply_part(void* arg) {
    ThreadData* data = (ThreadData*)arg;
    for (int i = data->start_row; i < data->end_row; i++) {
        for (int j = 0; j < data->N; j++) {
            data->C[i][j] = 0;
            for (int k = 0; k < data->N; k++) {
                data->C[i][j] += data->A[i][k] * data->B[k][j];
            }
        }
    }
    pthread_exit(NULL);
}

int** create_matrix(int N) {
    int** matrix = (int**)malloc(N * sizeof(int*));
    for (int i = 0; i < N; i++) {
        matrix[i] = (int*)malloc(N * sizeof(int));
    }
    return matrix;
}

void free_matrix(int** matrix, int N) {
    for (int i = 0; i < N; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

void fill_matrix_with_ones(int** matrix, int N) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            matrix[i][j] = 1;
        }
    }
}

void print_matrix(int** matrix, int N) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int N, threads;

    printf("Введите размер матрицы (N): ");
    scanf("%d", &N);

    printf("Введите количество потоков: ");
    scanf("%d", &threads);

    if (N <= 0 || threads <= 0) {
        printf("Ошибка: N и threads должны быть > 0\n");
        return 1;
    }

    if (threads > N) {
        printf("Ошибка: Количество потоков не может быть больше размера матрицы\n");
        return 1;
    }

    // Создаем и заполняем матрицы в основном потоке
    int** A = create_matrix(N);
    int** B = create_matrix(N);
    int** C = create_matrix(N);
    fill_matrix_with_ones(A, N);
    fill_matrix_with_ones(B, N);

    pthread_t* thread_ids = (pthread_t*)malloc(threads * sizeof(pthread_t));
    ThreadData* thread_data = (ThreadData*)malloc(threads * sizeof(ThreadData));

    // Вычисляем размер блока для каждого потока
    int block_size = N / threads;
    int remainder = N % threads;

    printf("\nРаспределение работы:\n");
    printf("Каждый поток обрабатывает блок %dx%d\n", block_size, N);
    if (remainder > 0) {
        printf("Основной поток дополнительно обрабатывает блок %dx%d\n", remainder, N);
    }

    // Распределяем работу между потоками
    int current_row = 0;
    for (int i = 0; i < threads; i++) {
        thread_data[i].thread_id = i;
        thread_data[i].A = A;
        thread_data[i].B = B;
        thread_data[i].C = C;
        thread_data[i].N = N;
        thread_data[i].start_row = current_row;
        thread_data[i].end_row = current_row + block_size;
        current_row += block_size;

        pthread_create(&thread_ids[i], NULL, multiply_part, &thread_data[i]);
    }

    // Обработка остатка в основном потоке
    if (remainder > 0) {
        for (int i = current_row; i < current_row + remainder; i++) {
            for (int j = 0; j < N; j++) {
                C[i][j] = 0;
                for (int k = 0; k < N; k++) {
                    C[i][j] += A[i][k] * B[k][j];
                }
            }
        }
    }

    // Ожидаем завершения всех потоков
    for (int i = 0; i < threads; i++) {
        pthread_join(thread_ids[i], NULL);
    }

    // Вывод результатов
    if (N < 5) {
        printf("\nМатрица A:\n");
        print_matrix(A, N);
        printf("\nМатрица B:\n");
        print_matrix(B, N);
    }
    printf("\nРезультат умножения (матрица C):\n");
    print_matrix(C, N);

    // Освобождение памяти
    free_matrix(A, N);
    free_matrix(B, N);
    free_matrix(C, N);
    free(thread_ids);
    free(thread_data);

    return 0;
}