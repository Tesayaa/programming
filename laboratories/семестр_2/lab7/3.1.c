#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_SIZE 50
#define MAX_VALUE 100
#define NUMBERS_PER_LINE 10

typedef struct {
    int value;
    int print_order;  // Порядок печати
} ThreadData;

ThreadData data[ARRAY_SIZE];
int current_order = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

void* sleep_sort(void* arg) {
    ThreadData* d = (ThreadData*)arg;
    usleep(d->value * 1000);  // Микросекунды
    
    pthread_mutex_lock(&mutex);
    // Ждем своей очереди для вывода
    while (d->print_order != current_order) {
        pthread_cond_wait(&cond, &mutex);
    }
    
    printf("%4d ", d->value);
    if (++current_order % NUMBERS_PER_LINE == 0) {
        printf("\n");
    }
    
    pthread_cond_broadcast(&cond);
    pthread_mutex_unlock(&mutex);
    
    return NULL;
}

void print_array(const char* title, ThreadData arr[], int size) {
    printf("%s:\n", title);
    for (int i = 0; i < size; i++) {
        printf("%4d ", arr[i].value);
        if ((i + 1) % NUMBERS_PER_LINE == 0) {
            printf("\n");
        }
    }
    printf("\n\n");
}

int main() {
    srand(time(NULL));

    // Инициализация данных
    for (int i = 0; i < ARRAY_SIZE; i++) {
        data[i].value = rand() % MAX_VALUE + 1;
        data[i].print_order = i;  // Изначальный порядок
    }

    print_array("Сгенерированный массив", data, ARRAY_SIZE);

    // Сортировка: определяем правильный порядок вывода
    for (int i = 0; i < ARRAY_SIZE; i++) {
        data[i].print_order = 0;
        for (int j = 0; j < ARRAY_SIZE; j++) {
            if (data[j].value < data[i].value || 
                (data[j].value == data[i].value && j < i)) {
                data[i].print_order++;
            }
        }
    }

    printf("Отсортированный массив:\n");
    
    // Создание и запуск потоков
    pthread_t threads[ARRAY_SIZE];
    for (int i = 0; i < ARRAY_SIZE; i++) {
        pthread_create(&threads[i], NULL, sleep_sort, &data[i]);
    }

    // Ожидание завершения
    for (int i = 0; i < ARRAY_SIZE; i++) {
        pthread_join(threads[i], NULL);
    }

    if (ARRAY_SIZE % NUMBERS_PER_LINE != 0) {
        printf("\n");
    }

    return 0;
}