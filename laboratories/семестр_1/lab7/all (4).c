//В заданном предложении найти самое короткое и самое длинное слово и поменять их местами.

#include <stdio.h>

int main() {
  char sentence[1000];
  char words[100][100];
  int wordCount = 0;
  int shortestWordLength = 100;
  int longestWordLength = 0;
  int shortestWordIndex = 0;
  int longestWordIndex = 0;
  int i, j, k;

  printf("Введите предложение: ");
  fgets(sentence, sizeof(sentence), stdin);

  // Разбиваем предложение на слова
  i = 0;
  j = 0;
  while (sentence[i] != '\0') {
    if (sentence[i] == ' ' || sentence[i] == '\n') {
      words[wordCount][j] = '\0';
      int wordLength = j;

      if (wordLength < shortestWordLength) {
        shortestWordLength = wordLength;
        shortestWordIndex = wordCount;
      }

      if (wordLength > longestWordLength) {
        longestWordLength = wordLength;
        longestWordIndex = wordCount;
      }

      wordCount++;
      j = 0;
    } else {
      words[wordCount][j] = sentence[i];
      j++;
    }
    i++;
  }

  // Меняем местами самое короткое и самое длинное слово
  char temp[100];
  for (k = 0; words[shortestWordIndex][k] != '\0'; k++) {
    temp[k] = words[shortestWordIndex][k];
  }
  temp[k] = '\0';

  for (k = 0; words[longestWordIndex][k] != '\0'; k++) {
    words[shortestWordIndex][k] = words[longestWordIndex][k];
  }
  words[shortestWordIndex][k] = '\0';

  for (k = 0; temp[k] != '\0'; k++) {
    words[longestWordIndex][k] = temp[k];
  }
  words[longestWordIndex][k] = '\0';

  // Выводим результат
  printf("Измененное предложение: ");
  for (i = 0; i < wordCount; i++) {
    printf("%s ", words[i]);
  }
  printf("\n");

  return 0;
}