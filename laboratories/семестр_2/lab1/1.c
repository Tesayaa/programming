#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define N 10000

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

void selectionSort(struct Student a[], int n) {
    int i, j, maxIndex;
    struct Student temp;
    
    for (i = 0; i < n - 1; i++) {
        maxIndex = i;
        for (j = i + 1; j < n; j++) {
            if (a[j].total > a[maxIndex].total) {
                maxIndex = j;
            }
        }
        temp = a[i];
        a[i] = a[maxIndex];
        a[maxIndex] = temp;
    }
}


int main() {
    struct Student students[N];
    srand(time(NULL));

    for (int i = 0; i < N; i++) {
        char name[64];
        sprintf(name, "Student%d", i+1);
        students[i] = addStudent(name, rand() % 101, rand() % 101, rand() % 101);
    }

    selectionSort(students, N);

    // for (int i = 0; i < N; i++) {
    //     printStudent(students[i]);
    // }
}