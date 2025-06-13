#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct {
    int thread_num;
    const char* prefix;
} ThreadData;

// Функция очистки, которая будет вызвана при отмене потока
void cleanup_handler(void* arg) {
    ThreadData* data = (ThreadData*)arg;
    printf("--- Поток %d завершает работу (очистка) ---\n", data->thread_num);
    free((void*)data->prefix);  // Освобождаем память здесь
}

void* thread_function(void* arg) {
    ThreadData* data = (ThreadData*)arg;
    
    // Регистрируем функцию очистки
    pthread_cleanup_push(cleanup_handler, data);
    
    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
    pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED, NULL);

    for (int i = 1; i <= 5; i++) {
        pthread_testcancel();
        printf("%s: строка %d\n", data->prefix, i);
        sleep(1);
    }

    // Убираем обработчик очистки (не будет вызван, если поток завершится нормально)
    pthread_cleanup_pop(0); // 0 - не выполнять очистку
    
    printf("--- Поток %d завершил работу нормально ---\n", data->thread_num);
    return NULL;
}

int main() {
    pthread_t threads[4];
    ThreadData thread_data[4];

    // Создаем 4 потока
    for (int i = 0; i < 4; i++) {
        thread_data[i].thread_num = i + 1;
        char* prefix = malloc(50);
        snprintf(prefix, 50, "Дочерний поток %d", i + 1);
        thread_data[i].prefix = prefix;

        if (pthread_create(&threads[i], NULL, thread_function, &thread_data[i]) != 0) {
            perror("Ошибка создания потока");
            free(prefix);
            return 1;
        }
    }

    sleep(2);
    
    // Прерываем все дочерние потоки
    for (int i = 0; i < 4; i++) {
        pthread_cancel(threads[i]);
    }

    // Ожидаем завершения потоков
    for (int i = 0; i < 4; i++) {
        pthread_join(threads[i], NULL);
    }

    // Основной поток выводит свои строки
    printf("\nРодительский поток начинает вывод:\n");
    for (int i = 1; i <= 5; i++) {
        printf("Родительский поток: строка %d\n", i);
        sleep(1);
    }

    return 0;
}