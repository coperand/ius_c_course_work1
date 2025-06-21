#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include <linux/limits.h>

#include "temp_api.h"

//Путь к файлу
char file_path[PATH_MAX];
//Месяц
uint8_t month = 0xFF;


//Функция разбора опций командной строки
void parse_args(int argc, char* argv[])
{
    //Сообщений для вывода через -h или --help
    char help_str[] =
    "Options:\n"
    "-h, --help                          - Print help and exit\n"
    "-f, --file <path>                   - Set a csv file path\n"
    "-m, --month <num>                   - Show only one month statistic (0-11)\n";

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
    if(month > 11 && month != 0xFF)
    {
        printf("A month value is invalid. Must be 0-11\n");
        failure = 1;
    }
    if(failure)
        exit(EXIT_FAILURE);
}

int main(int argc, char* argv[])
{
    //Инициализируем путь к файлу
    memset(file_path, 0, sizeof(file_path));

    //Разбираем аргументы командной строки
    parse_args(argc, argv);

    //DEBUG
    /* struct temperature_on_date_data temperature_on_date1;
    temperature_on_date1.date.year = 2024;
    temperature_on_date1.date.month = 4;
    temperature_on_date1.date.day = 25;
    temperature_on_date1.date.hour = 11;
    temperature_on_date1.date.minute = 41;
    temperature_on_date1.temperature = 6;
    if(push_to_list_back(temperature_on_date1) < 0)
        return -1;

    struct temperature_on_date_data temperature_on_date2;
    temperature_on_date2.date.year = 2024;
    temperature_on_date2.date.month = 5;
    temperature_on_date2.date.day = 26;
    temperature_on_date2.date.hour = 12;
    temperature_on_date2.date.minute = 42;
    temperature_on_date2.temperature = 12;
    if(push_to_list_front(temperature_on_date2) < 0)
        return -1;

    struct temperature_on_date_data temperature_on_date3;
    temperature_on_date3.date.year = 2024;
    temperature_on_date3.date.month = 3;
    temperature_on_date3.date.day = 25;
    temperature_on_date3.date.hour = 11;
    temperature_on_date3.date.minute = 41;
    temperature_on_date3.temperature = 6;
    if(push_to_list_back(temperature_on_date3) < 0)
        return -1;

    sort_list();

    remove_from_list(temperature_on_date3.date);

    print_list();

    printf("month_avg: %f\n", month_average(5));
    printf("month_min: %d\n", month_min(5));
    printf("month_max: %d\n", month_max(5));
    printf("year_avg: %f\n", year_average());
    printf("year_min: %d\n", year_min());
    printf("year_max: %d\n", year_max());

    destroy_list(); */

    //TODO: Реализовать функционал
}
