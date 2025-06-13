#include <stdio.h>
#include "person.h"
#include "search.h"

int main() {
    const char* filename = "Znak.dat";
    int N;

    printf("Сколько записей вы хотите создать? ");
    scanf("%d", &N);

    createFile(filename, N);
    searchFile(filename);

    return 0;
}

//gcc -c person.c search.c
// ar rcs libperson.a person.o search.o
// gcc main.c -L. -lperson -o main_static
// ./main_static


// gcc -fPIC -c person.c search.c
// gcc -shared -o libperson.so person.o search.o
// gcc main.c -L. -lperson -o main_dynamic
// export LD_LIBRARY_PATH=.
// ./main_dynamic