#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

// Рекурсивная функция для генерации анаграмм
void generateAnagrams(char *current, char *remaining, FILE *file) {
    if (strlen(remaining) == 0) {
        printf("%s\n", current);
        fprintf(file, "%s\n", current);
        return;
    }

    int len = strlen(remaining);
    for (int i = 0; i < len; i++) {
        // Создаем новую строку с добавленным символом
        char *newCurrent = (char *)malloc(strlen(current) + 2);
        strcpy(newCurrent, current);
        strncat(newCurrent, &remaining[i], 1);

        // Создаем новую строку без использованного символа
        char *newRemaining = (char *)malloc(len);
        strncpy(newRemaining, remaining, i);
        strcpy(newRemaining + i, remaining + i + 1);

        generateAnagrams(newCurrent, newRemaining, file);

        free(newCurrent);
        free(newRemaining);
    }
}

int main(int argc, char *argv[]) {
    setlocale(LC_ALL, "Russian");

    if (argc != 2) {
        printf("Использование: %s <имя_файла>\n", argv[0]);
        return 1;
    }

    FILE *inputFile = fopen(argv[1], "r");
    if (!inputFile) {
        perror("Не удалось открыть файл");
        return 1;
    }

    // Определяем размер файла
    fseek(inputFile, 0, SEEK_END);
    long fileSize = ftell(inputFile);
    rewind(inputFile);

    // Динамическое выделение памяти под слово
    char *word = (char *)malloc(fileSize + 1);
    if (!word) {
        perror("Ошибка выделения памяти");
        fclose(inputFile);
        return 1;
    }

    fread(word, sizeof(char), fileSize, inputFile);
    word[fileSize] = '\0';
    fclose(inputFile);

    // Убираем возможные переносы строки
    word[strcspn(word, "\r\n")] = '\0';

    printf("Анаграммы для слова \"%s\":\n", word);

    FILE *outputFile = fopen("anagrams.txt", "w");
    if (!outputFile) {
        perror("Не удалось создать файл для вывода");
        free(word);
        return 1;
    }

    char *empty = "";
    generateAnagrams(empty, word, outputFile);

    fclose(outputFile);
    free(word);

    printf("Список анаграмм сохранён в файл anagrams.txt\n");
    return 0;
}