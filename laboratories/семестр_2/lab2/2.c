#include <stdio.h>
#include <stdlib.h>

// Определение структуры узла
struct node {
    int data;
    struct node *next;      // Указатель на следующий узел
    struct node *prev;      // Указатель на предыдущий узел (для двунаправленного списка)
};

// Функция для добавления узла в конец списка
void append(struct node** head_ref, int new_data) {
    struct node* new_node = (struct node*) malloc(sizeof(struct node));
    struct node *last = *head_ref;

    // Заполнение данных нового узла
    new_node->data = new_data;
    new_node->next = NULL;
    new_node->prev = NULL;

    if (*head_ref == NULL) {
        *head_ref = new_node;
        return;
    }

    // Проходим до последнего узла
    while (last->next != NULL)
        last = last->next;

    // Меняем указатель последнего узла на новый узел
    last->next = new_node;
    new_node->prev = last;  // Устанавливаем обратную связь
}

// Функция для вывода текущего значения и навигации
void navigateList(struct node* head) {
    struct node* current = head;
    char input;

    if (head == NULL) {
        printf("Список пуст.\n");
        return;
    }

    while (1) {
        // Выводим текущее значение
        printf("Текущее значение: %d\n", current->data);

        // Запрос ввода от пользователя
        printf("Введите команду (W/A/S/D или 2/4/6/8): ");
        scanf(" %c", &input);  // Пробел перед %c, чтобы игнорировать пробелы и переводы строк

        // Обработка ввода
        switch (input) {
            case 'D':  // Вправо
            case '6':
                if (current->next != NULL) {
                    current = current->next;
                } else {
                    printf("Достигнут конец списка. Вернуться в начало? (Y/N): ");
                    scanf(" %c", &input);
                    if (input == 'Y' || input == 'y') {
                        current = head;  // Возврат в начало
                    }
                }
                break;

            case 'A':  // Влево
            case '4':
                if (current->prev != NULL) {
                    current = current->prev;
                } else {
                    printf("Достигнуто начало списка.\n");
                }
                break;

            case 'S':  // Вернуться в начало
                current = head;
                printf("Возврат в начало списка.\n");
                break;

            case 'W':  // Выход
            case '8':
                printf("Выход из программы.\n");
                return;

            default:
                printf("Неверная команда. Используйте W/A/S/D или 2/4/6/8.\n");
                break;
        }
    }
}

// Основная функция
int main() {
    struct node* head = NULL;
    int input;

    // Создаем список
    printf("Введите элементы списка (введите 0 для завершения):\n");
    while (1) {
        scanf("%d", &input);
        if (input == 0) {
            break;
        }
        append(&head, input);
    }

    // Начинаем навигацию по списку
    navigateList(head);

    return 0;
}