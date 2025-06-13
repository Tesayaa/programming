#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define N 100
#define N2 10000
#define N3 100000

struct Student {
    char name[64];
    int math;
    int phy;
    int inf;
    int total;
};

struct Student addStudent(char name[], int math, int phy, int inf) {
    struct Student newStudent;
    strcpy(newStudent.name, name);
    newStudent.math = math;
    newStudent.phy = phy;
    newStudent.inf = inf;
    newStudent.total = math + phy + inf;
    return newStudent;
}

void printStudent(struct Student student) {
    printf("Name: %s\nMath: %d, Physics: %d, Informatics: %d\nTotal: %d\n", student.name, student.math, student.phy, student.inf, student.total);
}

void countingSortByDigit(struct Student students[], int n, int exp, struct Student output[]) {
    int count[10] = {0};

    for (int i = 0; i < n; i++) 
        count[9 - (students[i].total / exp) % 10]++; 
    for (int i = 1; i < 10; i++) 
        count[i] += count[i - 1];
    for (int i = n - 1; i >= 0; i--) 
        output[--count[9 - (students[i].total / exp) % 10]] = students[i]; 
    for (int i = 0; i < n; i++) 
        students[i] = output[i];
}

void RadixSort(struct Student students[], int n) {
    int maxTotal = students[0].total;
    for (int i = 1; i < n; i++) 
        if (students[i].total > maxTotal) 
            maxTotal = students[i].total;
    
    struct Student *output = (struct Student*)malloc(n * sizeof(struct Student));
    if (output == NULL) {
        printf("Memory allocation failed. Exiting.");
        exit(1);
    }

    for (int exp = 1; maxTotal / exp > 0; exp *= 10) 
        countingSortByDigit(students, n, exp, output);

    free(output);
}

void generateRandomStudents(struct Student students[], int n) {
    for (int i = 0; i < n; i++) {
        char name[64];
        sprintf(name, "Student%d", i + 1);
        students[i] = addStudent(name, rand() % 101, rand() % 101, rand() % 101);
    }
}

void measureSortingTime(int n) {
    struct Student students[n];
    generateRandomStudents(students, n);

    clock_t start = clock();
    RadixSort(students, n);
    clock_t end = clock();

    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Time for N = %d: %.6f seconds\n", n, time_spent);
}

int main() {
    struct Student students[N];
    srand(time(NULL));

    for (int i = 0; i < N; i++) {
        char name[64];
        sprintf(name, "Student%d", i + 1);
        students[i] = addStudent(name, rand() % 101, rand() % 101, rand() % 101);
    }

    RadixSort(students, N);

    for (int i = 0; i < N; i++) {
        printStudent(students[i]);
        printf("\n");
    }

    system("cat /proc/cpuinfo | grep 'model name\\|MHz'");
    printf("\n");

    measureSortingTime(N);
    measureSortingTime(N2);
    measureSortingTime(N3); 

    printf("Размер данных: %lu bytes\n", N * sizeof(struct Student));
    printf("Размер данных: %lu bytes\n", N2 * sizeof(struct Student));
    printf("Размер данных: %lu bytes\n\n", N3 * sizeof(struct Student));

    return 0;
}