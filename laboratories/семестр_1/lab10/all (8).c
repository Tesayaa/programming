// time.cpp
#include "time.h"

// Функция для инициализации структуры Time
Time createTime(int h, int m) {
    Time t;
    t.hours = h;
    t.minutes = m;
    return t;
}

// Функция для вычисления разницы во времени в минутах, с обработкой ошибок
int timeDifference(Time start, Time end) {
    int diffMinutes = (end.hours - start.hours) * 60 + (end.minutes - start.minutes);
    if (diffMinutes < 0) {
        fprintf(stderr, "Ошибка: время окончания меньше времени начала!\n");
        exit(EXIT_FAILURE);
    }
    return diffMinutes;
}