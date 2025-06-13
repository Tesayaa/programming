#ifndef PERSON_H
#define PERSON_H

typedef struct {
    int day;
    int month;
    int year;
} Birthday;

typedef struct {
    char surname[50];
    char name[50];
    char zodiacSign[20];
    Birthday birthday;
} Person;

void createFile(const char* filename, int N);

#endif // PERSON_H
