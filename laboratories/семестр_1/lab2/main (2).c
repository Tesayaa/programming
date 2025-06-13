#include <stdio.h>
int main()
{
    float temperatura;
    char unit;
    printf("Input temperature: ");
    scanf("%f", &temperatura);
    scanf("%c", &unit);
    if (unit == 'C' || unit == 'c')
        {
            printf("Out temperature: ");
            printf("%.1f f", (temperatura * 9.0f / 5.0f) + 32.0f);
        }
        else if (unit == 'f' || unit == 'F')
            {
                printf("Out temperature: ");
                printf("%.1f c", (temperatura - 32.0f) * 5.0f/9.0f);
            }
            else
            {
                printf("Ouput error");
            }
}