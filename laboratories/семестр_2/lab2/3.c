#include <stdio.h>
#include <stdlib.h>

// Определение структуры узла
struct node {
    int data;
    struct node *next;      // Указатель на следующий узел в текущем списке
    struct node *prev;      // Указатель на предыдущий узел (для второго списка)
    struct node *another;   // Указатель на соответствующий узел в другом списке
};

// Функция для добавления узла в конец списка
void append(struct node** head_ref, int new_data) {
    struct node* new_node = (struct node*) malloc(sizeof(struct node));
    struct node *last = *head_ref;

    // Заполнение данных нового узла
    new_node->data = new_data;
    new_node->next = NULL;
    new_node->prev = NULL;
    new_node->another = NULL;

    if (*head_ref == NULL) {
        *head_ref = new_node;
        return;
    }

    // Проходим до последнего узла
    while (last->next != NULL)
        last = last->next;

    // Меняем указатель последнего узла на новый узел
    last->next = new_node;
    new_node->prev = last; 
}

// Функция для связывания двух списков
void connectLists(struct node* head1, struct node* head2) {
    struct node* current1 = head1;
    struct node* current2 = head2;

    // Связываем соответствующие узлы
    while (current1 != NULL && current2 != NULL) {
        current1->another = current2;
        current2->another = current1;
        current1 = current1->next;
        current2 = current2->next;
    }

    // Если первый список длиннее, устанавливаем оставшиеся указатели в NULL
    while (current1 != NULL) {
        current1->another = NULL;
        current1 = current1->next;
    }

    // Если второй список длиннее, устанавливаем оставшиеся указатели в NULL
    while (current2 != NULL) {
        current2->another = NULL;
        current2 = current2->next;
    }
}

// Функция для навигации по спискам
void navigateLists(struct node* head1, struct node* head2) {
    struct node* current = head1;  // Начинаем с первого элемента первого списка
    char input;

    while (1) {
        // Выводим текущий узел
        printf("Текущий узел: %d\n", current->data);

        // Выводим связанный узел 
        if (current->another != NULL) {
            printf("Связанный узел: %d\n", current->another->data);
        } else {
            printf("Связанный узел: NULL\n");
        }

        // Запрос ввода от пользователя
        printf("Введите команду (W/A/S/D или 2/4/6/8): ");
        scanf(" %c", &input); 

        // Обработка ввода
        switch (input) {
            case 'D':  // Вправо 
            case '6':
                if (current->next != NULL) {
                    current = current->next;
                } else {
                    printf("Достигнут конец списка.\n");
                }
                break;

            case 'A':  // Влево 
            case '4':
                if (current->another != NULL) {
                    current = current->another;
                } else {
                    printf("Невозможно перейти в другой список.\n");
                }
                break;

            case 'S':  // Вернуться в начало 
                if (current == head1 || current == head2) {
                    printf("Уже в начале списка.\n");
                } else {
                    if (current == head1->another) {
                        current = head2;
                    } else {
                        current = head1;
                    }
                    printf("Возврат в начало списка.\n");
                }
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

int main() {
    struct node* head1 = NULL;  
    struct node* head2 = NULL;  
    int input;

    printf("Введите элементы первого списка (введите 0 для завершения):\n");
    while (1) {
        scanf("%d", &input);
        if (input == 0) {
            break;
        }
        append(&head1, input);
    }

    printf("Введите элементы второго списка (введите 0 для завершения):\n");
    while (1) {
        scanf("%d", &input);
        if (input == 0) {
            break;
        }
        append(&head2, input);
    }

    connectLists(head1, head2);

    navigateLists(head1, head2);

    return 0;
}