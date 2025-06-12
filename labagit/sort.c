#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void FillInc(int A[], int n) {
    for (int i = 0; i < n; i++)
        A[i] = i + 1;
}

void FillDec(int A[], int n) {
    for (int i = 0; i < n; i++)
        A[i] = n - i;
}

void FillRand(int A[], int n) {
    srand(time(NULL));
    for (int i = 0; i < n; i++)
        A[i] = rand() % 100;
}

int CheckSum(int A[], int n) {
    int sum = 0;
    for (int i = 0; i < n; i++)
        sum += A[i];
    return sum;
}

int RunNumber(int A[], int n) {
    int runs = 1;
    for (int i = 1; i < n; i++) {
        if (A[i] < A[i - 1]) runs++;
    }
    return runs;
}

void PrintMas(int A[], int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", A[i]);
    printf("\n");
}

int BubbleSort(int A[], int n) {
    int C = 0;
    int M = 0;
    int trud = 0;
    for (int i = 0; i < n - 1; i++) {
        for (int j = n-1; j > i; j--) {
            C++; // Подсчет сравнения
            if (A[j] < A[j - 1]) {
                M++;
                int temp = A[j];
                M++;
                A[j] = A[j - 1];
                M++;
                A[j - 1] = temp;
            }
        }
    }
    trud = M+C;
    return trud;
}

int main()
{
    printf("x---------------|----------------------------|--------------------------|--------------------------|-----------------------------x\n");
    printf("|       N       |     Трудоёмкость (теор)    |    Трудоемкость (убыв)   |    Трудоемкость (случ)   |    Трудоемкость (возраст)   |\n");
    printf("|---------------|----------------------------|--------------------------|--------------------------|-----------------------------|\n");

    for (int i = 1; i < 6; i++) {
        int trud;
        int n = 100*i;
        int A[n];
        int theor = 3 * (n * (n - 1) / 2) + (n * (n - 1) / 2);
        FillDec(A,n);
        trud = BubbleSort(A,n);
        FillRand(A,n);
        int trud_rand = BubbleSort(A,n);
        FillInc(A,n);
        int trud_inc = BubbleSort(A,n);
        printf("| %-12d  | %-26d | %-24d | %-24d | %-27d |\n", n, theor, trud, trud_rand, trud_inc);
    }

    printf("x---------------|----------------------------|--------------------------|--------------------------|-----------------------------x\n");

}