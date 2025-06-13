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

void print_distribution(int N, int threads, int block_size, int remainder) {
    printf("\nДетальное распределение строк:\n");
    printf("Всего строк: %d\n", N);
    printf("Потоков: %d\n", threads);
    printf("Базовый размер блока: %d строк на поток\n", block_size);
    printf("Остаток: %d строк\n\n", remainder);
    
    printf("| Поток | Начало | Конец | Строк |\n");
    printf("|-------|--------|-------|-------|\n");
    
    int current_row = 0;
    for (int i = 0; i < threads; i++) {
        int rows_for_thread = block_size + (i < remainder ? 1 : 0);
        printf("| %5d | %6d | %5d | %5d |\n", 
               i, current_row, current_row + rows_for_thread - 1, rows_for_thread);
        current_row += rows_for_thread;
    }
    
    if (remainder > 0) {
        printf("\nОстаточные строки %d-%d будут обработаны в основном потоке\n",
               current_row, current_row + remainder - 1);
    }
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

    int** A = create_matrix(N);
    int** B = create_matrix(N);
    int** C = create_matrix(N);
    fill_matrix_with_ones(A, N);
    fill_matrix_with_ones(B, N);

    pthread_t* thread_ids = (pthread_t*)malloc(threads * sizeof(pthread_t));
    ThreadData* thread_data = (ThreadData*)malloc(threads * sizeof(ThreadData));

    int block_size = N / threads;
    int remainder = N % threads;
    
    print_distribution(N, threads, block_size, remainder);

    int current_row = 0;
    for (int i = 0; i < threads; i++) {
        int rows_for_thread = block_size + (i < remainder ? 1 : 0);
        thread_data[i].thread_id = i;
        thread_data[i].A = A;
        thread_data[i].B = B;
        thread_data[i].C = C;
        thread_data[i].N = N;
        thread_data[i].start_row = current_row;
        thread_data[i].end_row = current_row + rows_for_thread;
        current_row += rows_for_thread;

        pthread_create(&thread_ids[i], NULL, multiply_part, &thread_data[i]);
    }

    // Обработка остатка в основном потоке
    if (remainder > 0) {
        printf("\nОсновной поток начинает обработку остатка...\n");
        for (int i = current_row; i < N; i++) {
            for (int j = 0; j < N; j++) {
                C[i][j] = 0;
                for (int k = 0; k < N; k++) {
                    C[i][j] += A[i][k] * B[k][j];
                }
            }
        }
        printf("Основной поток завершил обработку остатка\n");
    }

    for (int i = 0; i < threads; i++) {
        pthread_join(thread_ids[i], NULL);
    }

    if (N < 5) {
        printf("\nМатрица A:\n");
        print_matrix(A, N);
        printf("\nМатрица B:\n");
        print_matrix(B, N);
    }
    printf("\nРезультат умножения (матрица C):\n");
    print_matrix(C, N);

    free_matrix(A, N);
    free_matrix(B, N);
    free_matrix(C, N);
    free(thread_ids);
    free(thread_data);

    return 0;
}