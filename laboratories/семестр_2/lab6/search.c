#include "search.h"
#include <stdio.h>
#include <string.h>

void searchFile(const char* filename) {
    char choice;
    do {
        FILE* file = fopen(filename, "rb");
        if (file == NULL) {
            printf("Не удалось открыть файл!\n");
            break;
        }

        printf("\nПо какому полю выполнить поиск?\n");
        printf("1 - Фамилия\n");
        printf("2 - Имя\n");
        printf("3 - Знак Зодиака\n");
        printf("4 - День рождения (дд)\n");
        printf("5 - Месяц рождения (мм)\n");
        printf("6 - Год рождения (гггг)\n");
        printf("Выберите поле для поиска (1-6): ");

        int fieldChoice;
        scanf("%d", &fieldChoice);

        char searchStr[50] = {0};
        int searchInt = 0;

        if (fieldChoice >= 1 && fieldChoice <= 3) {
            printf("Введите значение для поиска: ");
            scanf("%49s", searchStr);
        } else if (fieldChoice >= 4 && fieldChoice <= 6) {
            printf("Введите значение для поиска: ");
            scanf("%d", &searchInt);
        } else {
            printf("Неверный выбор!\n");
            fclose(file);
            break;
        }

        Person person;
        int found = 0;

        printf("\nРезультаты поиска:\n");
        printf("%-20s%-15s%-15s%-15s\n", "Фамилия", "Имя", "Знак Зодиака", "    Дата рождения");
        printf("------------------------------------------------------------\n");

        while (fread(&person, sizeof(Person), 1, file) == 1) {
            int match = 0;

            switch (fieldChoice) {
                case 1:
                    match = (strcmp(person.surname, searchStr) == 0);
                    break;
                case 2:
                    match = (strcmp(person.name, searchStr) == 0);
                    break;
                case 3:
                    match = (strcmp(person.zodiacSign, searchStr) == 0);
                    break;
                case 4:
                    match = (person.birthday.day == searchInt);
                    break;
                case 5:
                    match = (person.birthday.month == searchInt);
                    break;
                case 6:
                    match = (person.birthday.year == searchInt);
                    break;
            }

            if (match) {
                found = 1;
                printf("%-15s%-15s%-15s%02d.%02d.%04d\n",
                    person.surname,
                    person.name,
                    person.zodiacSign,
                    person.birthday.day,
                    person.birthday.month,
                    person.birthday.year);
            }
        }

        if (!found) {
            printf("Записи не найдены.\n");
        }

        fclose(file);

        printf("\nХотите выполнить еще один поиск? (y/n): ");
        scanf(" %c", &choice);
    } while (choice == 'y' || choice == 'Y');
}
