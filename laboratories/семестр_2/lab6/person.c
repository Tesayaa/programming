#include "person.h"
#include <stdio.h>

void createFile(const char* filename, int N) {
    FILE* file = fopen(filename, "wb");
    if (file == NULL) {
        printf("Не удалось создать файл!\n");
        return;
    }

    for (int i = 0; i < N; ++i) {
        Person person;
        printf("\nЗапись #%d:\n", i + 1);

        printf("Фамилия: ");
        scanf("%49s", person.surname);

        printf("Имя: ");
        scanf("%49s", person.name);

        printf("Знак Зодиака: ");
        scanf("%19s", person.zodiacSign);

        printf("День рождения (дд мм гггг): ");
        scanf("%d %d %d", &person.birthday.day, &person.birthday.month, &person.birthday.year);

        fwrite(&person, sizeof(Person), 1, file);
    }
    fclose(file);
}
