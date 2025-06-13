// main.cpp
#include "time.h"
#include <stdio.h>

int main() {
    int numDays;

    printf("Введите количество дней: ");
    if (scanf("%d", &numDays) != 1 || numDays <= 0) {
        fprintf(stderr, "Ошибка ввода количества дней.\n");
        return 1;
    }

    int totalMinutes = 0;
    for (int i = 0; i < numDays; i++) {
        Time startTime, endTime;
        printf("День %d:\n", i + 1);

        printf("  Введите время начала (часы минуты): ");
        if (scanf("%d %d", &startTime.hours, &startTime.minutes) != 2) {
            fprintf(stderr, "Ошибка ввода времени начала.\n");
            return 1;
        }

        printf("  Введите время окончания (часы минуты): ");
        if (scanf("%d %d", &endTime.hours, &endTime.minutes) != 2) {
            fprintf(stderr, "Ошибка ввода времени окончания.\n");
            return 1;
        }

        totalMinutes += timeDifference(startTime, endTime);
    }

    printf("Общее время работы: %d час(ов) %d минут(ы).\n", totalMinutes / 60, totalMinutes % 60);
    return 0;
}