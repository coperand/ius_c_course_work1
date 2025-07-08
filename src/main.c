#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include <linux/limits.h>

#include "temp_functions.h"

//Путь к файлу
char file_path[PATH_MAX];
//Месяц
uint8_t month = 0xFF;


//Функция разбора опций командной строки
void parse_args(int argc, char* argv[])
{
    //Сообщений для вывода через -h или --help
    char help_str[] =
    "Calculate temperature statistic using data from a csv file. Options:\n"
    "-h, --help         - Print help and exit\n"
    "-f, --file <path>  - Set a csv file path\n"
    "-m, --month <num>  - Show only one month statistic (1-12)\n";

    //Заполняем параметры опций
    const struct option long_opts[] =
    {
        {"help", no_argument, NULL, 'h'},
        {"file", required_argument, NULL, 'f'},
        {"month", required_argument, NULL, 'm'},
        {NULL, 0, NULL, 0}
    };

    //Разбираем опции по одной
    int opt = 0;
    while( (opt = getopt_long(argc, argv, "hf:m:", long_opts, NULL)) != -1 )
    {
        switch (opt)
        {
            case 'h':
                printf("%s", help_str);
                exit(EXIT_SUCCESS);
            case 'f':
                if(optarg)
                    strncpy(file_path, optarg, PATH_MAX);
                break;
            case 'm':
                if(optarg)
                    month = atoi(optarg);
                break;
            default:
                printf("Failed to parse argument: %s\n", optarg);
                exit(EXIT_FAILURE);
        }
    }


    //Валидация параметров
    int8_t failure = 0;
    if(strlen(file_path) == 0)
    {
        printf("A file path is not specified\n");
        failure = 1;
    }
    if((month < 1 || month > 12) && month != 0xFF)
    {
        printf("A month value is invalid. Must be 1-12\n");
        failure = 1;
    }
    //Если параметров нет, выводим help
    if(argc == 1)
        printf("%s", help_str);
    if(failure)
        exit(EXIT_FAILURE);
}

int main(int argc, char* argv[])
{
    //Инициализируем путь к файлу
    memset(file_path, 0, sizeof(file_path));

    //Разбираем аргументы командной строки
    parse_args(argc, argv);

    //Разбираем файл
    if(parse_csv(file_path) < 0)
    {
        printf("Failed to parse file %s\n", file_path);
        exit(EXIT_FAILURE);
    }

    //Выводим статистику по месяцам
    printf("Statistic by month:\n");
    for(uint8_t i = 1; i < 13; i++)
    {
        //Если указан конкретный месяц и это не он, пропускаем
        if(month != 0xFF && i != month)
            continue;

        //Получаем статистику по месяцу
        float average = month_average(i);
        int8_t min = month_min(i);
        int8_t max = month_max(i);

        //Если конкретный месяц не указан, и статистика пуста, пропускаем месяц
        if(month == 0xFF && isnan(average) && min == INT8_MAX && max == INT8_MIN)
            continue;

        //Выводим читаемое название месяца
        switch(i)
        {
            case 1:
                printf("  January:\n");
                break;
            case 2:
                printf("  February:\n");
                break;
            case 3:
                printf("  March:\n");
                break;
            case 4:
                printf("  April:\n");
                break;
            case 5:
                printf("  May:\n");
                break;
            case 6:
                printf("  June:\n");
                break;
            case 7:
                printf("  July:\n");
                break;
            case 8:
                printf("  August:\n");
                break;
            case 9:
                printf("  September:\n");
                break;
            case 10:
                printf("  October:\n");
                break;
            case 11:
                printf("  November:\n");
                break;
            case 12:
                printf("  December:\n");
                break;
        }

        //Выводим статистику по месяцу при наличии
        if(!isnan(average))
            printf("    average: %f\n", average);
        if(min != INT8_MAX)
            printf("    min: %d\n", min);
        if(max != INT8_MIN)
            printf("    max: %d\n", max);
    }

    //Если конкретный месяц не указан, выводим ещё и общую статистику за год
    if(month == 0xFF)
    {
        printf("Statistic by year:\n");

        //Получаем и выводим статистику по году при наличии
        float average = year_average();
        if(!isnan(average))
            printf("  average: %f\n", average);
        int8_t min = year_min();
        if(min != INT8_MAX)
            printf("  min: %d\n", min);
        int8_t max = year_max();
        if(max != INT8_MIN)
            printf("  max: %d\n", max);
    }
}
