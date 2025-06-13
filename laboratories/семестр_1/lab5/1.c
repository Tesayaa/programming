#include <stdio.h>

int main() {
    int num;

    printf("Введите число: ");
    scanf("%d", &num);

    // Проверка на кратность 16 с помощью битовых операций
    if ((num & 0xF) == 0) {
        printf("%d кратно 16.\n", num);
    } else {
        printf("%d не кратно 16.\n", num);
    }

    return 0;
}