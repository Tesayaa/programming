#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE_LENGTH 1000
#define MAX_WORD_LENGTH 100

void swap_words(char *str) {
    // Удаляем символ новой строки, если он есть
    str[strcspn(str, "\n")] = '\0';
    
    // Пропускаем начальные пробелы
    char *start = str;
    while (isspace(*start)) start++;
    
    // Если строка пустая
    if (*start == '\0') {
        printf("Empty line - nothing to swap\n");
        return;
    }
    
    // Находим конец первого слова
    char *first_end = start;
    while (*first_end && !isspace(*first_end)) first_end++;
    
    // Если в строке только одно слово
    if (*first_end == '\0') {
        printf("Single word line - nothing to swap\n");
        return;
    }
    
    // Находим начало последнего слова
    char *last_end = str + strlen(str) - 1;
    while (last_end > str && isspace(*last_end)) last_end--;
    
    char *last_start = last_end;
    while (last_start > str && !isspace(*last_start)) last_start--;
    if (isspace(*last_start)) last_start++;
    
    // Копируем первое и последнее слова
    char first_word[MAX_WORD_LENGTH], last_word[MAX_WORD_LENGTH];
    strncpy(first_word, start, first_end - start);
    first_word[first_end - start] = '\0';
    
    strncpy(last_word, last_start, last_end - last_start + 1);
    last_word[last_end - last_start + 1] = '\0';
    
    // Формируем новую строку
    char new_line[MAX_LINE_LENGTH] = "";
    strcat(new_line, last_word);
    strcat(new_line, " ");
    
    // Добавляем среднюю часть (если есть)
    char *middle_start = first_end;
    while (isspace(*middle_start)) middle_start++;
    
    if (middle_start < last_start) {
        strncat(new_line, middle_start, last_start - middle_start);
        strcat(new_line, " ");
    }
    
    strcat(new_line, first_word);
    
    // Копируем обратно в исходную строку
    strcpy(str, new_line);
}

void process_file(const char *filename) {
    FILE *file = fopen(filename, "r+");
    if (!file) {
        exit(EXIT_FAILURE);
    }

    char line[MAX_LINE_LENGTH];
    char longest_line[MAX_LINE_LENGTH] = "";
    long longest_pos = 0;
    size_t max_len = 0;
    int line_number = 0;
    int longest_line_number = 0;

    // Читаем файл и находим самую длинную строку
    while (fgets(line, sizeof(line), file)) {
        line_number++;
        size_t len = strlen(line);
        if (len > max_len) {
            max_len = len;
            strcpy(longest_line, line);
            longest_pos = ftell(file) - len;
            longest_line_number = line_number;
        }
    }

    if (max_len == 0) {
        fprintf(stderr, "File is empty\n");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    printf("Самая длинная строчка (#%d, длина %zu): %s", 
           longest_line_number, max_len, longest_line);
    
    // Меняем местами слова только в самой длинной строке
    swap_words(longest_line);
    printf("После замены: %s\n", longest_line);

    // Записываем измененную строку обратно в файл
    fseek(file, longest_pos, SEEK_SET);
    fprintf(file, "%s\n", longest_line);
    fclose(file);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 0;
    }

    process_file(argv[1]);

    return 0;
}