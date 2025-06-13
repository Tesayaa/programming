#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

#define PARENT_COUNT 5
#define CHILD_COUNT 4

typedef struct {
    int parent_num;
    int child_num;
    const char* prefix;
    pthread_mutex_t* mutex;
    pthread_cond_t* cond;
    int* turn;
    int* current_parent;
    bool* shutdown_flag;
} ThreadData;

void cleanup_handler(void* arg) {
    ThreadData* data = (ThreadData*)arg;
    printf("--- Дочерний поток %d-%d завершает работу (очистка) ---\n", 
           data->parent_num, data->child_num);
    free((void*)data->prefix);
}

void* child_thread_function(void* arg) {
    ThreadData* data = (ThreadData*)arg;
    
    pthread_cleanup_push(cleanup_handler, data);
    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
    pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED, NULL);

    for (int i = 1; i <= 5 && !*(data->shutdown_flag); i++) {
        pthread_testcancel();
        
        pthread_mutex_lock(data->mutex);
        
        while ((*(data->turn) != 1 || *(data->current_parent) != data->parent_num) 
               && !*(data->shutdown_flag)) {
            pthread_cond_wait(data->cond, data->mutex);
        }
        
        if (*(data->shutdown_flag)) {
            pthread_mutex_unlock(data->mutex);
            break;
        }
        
        printf("%s: строка %d\n", data->prefix, i);
        
        *(data->turn) = 0;
        pthread_cond_broadcast(data->cond);
        
        pthread_mutex_unlock(data->mutex);
        
        usleep(100000);
    }

    pthread_cleanup_pop(0);
    return NULL;
}

void* parent_thread_function(void* arg) {
    ThreadData* data = (ThreadData*)arg;
    pthread_t children[CHILD_COUNT];
    ThreadData child_data[CHILD_COUNT];
    
    pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
    pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
    int turn = 0;
    int current_parent = data->parent_num;
    bool shutdown_flag = false;

    // Создаем дочерние потоки
    for (int i = 0; i < CHILD_COUNT; i++) {
        child_data[i].parent_num = data->parent_num;
        child_data[i].child_num = i + 1;
        char* prefix = malloc(50);
        snprintf(prefix, 50, "Родитель %d, Дочерний %d", 
                data->parent_num, i + 1);
        child_data[i].prefix = prefix;
        child_data[i].mutex = &mutex;
        child_data[i].cond = &cond;
        child_data[i].turn = &turn;
        child_data[i].current_parent = &current_parent;
        child_data[i].shutdown_flag = &shutdown_flag;

        if (pthread_create(&children[i], NULL, child_thread_function, &child_data[i]) != 0) {
            perror("Ошибка создания дочернего потока");
            free(prefix);
            continue;
        }
    }

    time_t start_time = time(NULL);
    
    // Родительский поток выводит свои строки
    printf("\nРодительский поток %d начинает вывод:\n", data->parent_num);
    for (int i = 1; i <= 5 && !shutdown_flag; i++) {
        pthread_mutex_lock(&mutex);
        
        while ((turn != 0 || current_parent != data->parent_num) && !shutdown_flag) {
            pthread_cond_wait(&cond, &mutex);
        }
        
        if (shutdown_flag) {
            pthread_mutex_unlock(&mutex);
            break;
        }
        
        printf("Родитель %d: строка %d\n", data->parent_num, i);
        
        turn = 1;
        pthread_cond_broadcast(&cond);
        
        pthread_mutex_unlock(&mutex);
        
        usleep(100000);
        
        // Проверяем, прошло ли 2 секунды
        if (time(NULL) - start_time >= 2) {
            shutdown_flag = true;
            pthread_cond_broadcast(&cond);
            break;
        }
    }

    // Устанавливаем флаг завершения
    shutdown_flag = true;
    pthread_cond_broadcast(&cond);
    
    // Прерываем все дочерние потоки
    for (int i = 0; i < CHILD_COUNT; i++) {
        pthread_cancel(children[i]);
    }

    // Ожидаем завершения дочерних потоков
    for (int i = 0; i < CHILD_COUNT; i++) {
        pthread_join(children[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);
    return NULL;
}

int main() {
    pthread_t parents[PARENT_COUNT];
    ThreadData parent_data[PARENT_COUNT];

    // Создаем родительские потоки
    for (int i = 0; i < PARENT_COUNT; i++) {
        parent_data[i].parent_num = i + 1;
        
        if (pthread_create(&parents[i], NULL, parent_thread_function, &parent_data[i]) != 0) {
            perror("Ошибка создания родительского потока");
            continue;
        }
    }

    // Ожидаем завершения всех родительских потоков
    for (int i = 0; i < PARENT_COUNT; i++) {
        pthread_join(parents[i], NULL);
    }

    printf("Все потоки завершены. Программа завершается.\n");
    return 0;
}