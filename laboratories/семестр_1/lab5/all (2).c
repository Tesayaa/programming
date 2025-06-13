#include <stdio.h>

int main() {
    int a;

    printf("Введите число: ");
    scanf("%d", &a);

    // Используем битовые операции для перестановки
    a = ((a >> 8) & 0xFF) | ((a << 8) & 0xFFFF00);

    printf("Число с переставленными байтами: %d\n", a);

    return 0;
}