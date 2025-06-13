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

void swap(struct Student* a, struct Student* b) {
    struct Student temp = *a;
    *a = *b;
    *b = temp;
}

int partition(struct Student arr[], int low, int high) {
    int pivot = arr[high].total; 
    int i = (low - 1); 

    for (int j = low; j <= high - 1; j++) {
        if (arr[j].total >= pivot) {
            i++; 
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quickSort(struct Student arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
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
    quickSort(students, 0, n - 1);
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

    quickSort(students, 0, N - 1);

    for (int i = 0; i < N; i++) {
        printStudent(students[i]);
    }

    measureSortingTime(N); 
    measureSortingTime(N2); 
    measureSortingTime(N3); 

    printf("Размер данных: %lu bytes\n", N * sizeof(struct Student));
    printf("Размер данных: %lu bytes\n", N2 * sizeof(struct Student));
    printf("Размер данных: %lu bytes\n\n", N3 * sizeof(struct Student));

    return 0;
}