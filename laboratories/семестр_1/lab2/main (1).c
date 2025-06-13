    #include <stdio.h>
int main()
{
   int year;
   printf("Введите год\n");
   scanf("%d", &year);
   if (year % 400 == 0)
    {
        printf("Yes\n");
    }
    else if (year % 100 == 0)
        {
            printf("No\n");
        }
        else if (year% 4 == 0)
            {
                printf("Yes\n");
            }
            else
                {
                    printf("No\n");
                }
}