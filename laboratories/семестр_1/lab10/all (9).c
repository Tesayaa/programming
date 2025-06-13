#ifndef TIME_H
#define TIME_H

#include <stdio.h>
#include <stdlib.h>

// Структура для времени
typedef struct {
    int hours;
    int minutes;
} Time;

// Функция для инициализации структуры Time
Time createTime(int h, int m);

// Функция для вычисления разницы во времени в минутах, с обработкой ошибок
int timeDifference(Time start, Time end);

#endif // TIME_H