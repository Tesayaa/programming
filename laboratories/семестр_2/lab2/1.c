#include <stdio.h>
#include <stdlib.h>

// Определение структуры узла
struct node {
    int data;
    struct node *next;
};

// Функция для добавления узла в конец списка
void append(struct node** head_ref, int new_data) {
    struct node* new_node = (struct node*) malloc(sizeof(struct node));
    struct node *last = *head_ref;

    new_node->data = new_data;
    new_node->next = NULL;

    if (*head_ref == NULL) {
        *head_ref = new_node;
        return;
    }

    while (last->next != NULL)
        last = last->next;

    last->next = new_node;
}

// Функция для вывода списка на экран
void printList(struct node *node) {
    while (node != NULL) {
        printf("%d ", node->data);
        node = node->next;
    }
    printf("\n");
}

// Основная функция для создания списка из вводимых элементов
int main() {
    struct node* head = NULL;
    int input;

    printf("Введите элементы списка (введите 0 для завершения):\n");

    while (1) {
        scanf("%d", &input);
        if (input == 0) {
            break;
        }
        // Добавляем элемент a_i
        append(&head, input);
    }

    printf("Созданный список: ");
    printList(head);

    return 0;
}