#ifndef __TEMP_FUNCTIONS_H__
#define __TEMP_FUNCTIONS_H__

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <math.h>

//Данные о дате
struct date_data
{
    uint16_t year;
    uint8_t month;
    uint8_t day;
    uint8_t hour;
    uint8_t minute;
};

//Компараторы дат
int8_t date_less(struct date_data date1, struct date_data date2);
int8_t date_equal(struct date_data date1, struct date_data date2);

//Данные о температуре на дату
struct temperature_on_date_data
{
    struct date_data date;
    int8_t temperature;
};

//Функция валидации структуры temperature_on_date_data
int8_t is_temperature_on_date_valid(struct temperature_on_date_data temperature_on_date);

//Функции получения статистики по месяцу или году
float month_average(uint8_t month);
int8_t month_min(uint8_t month);
int8_t month_max(uint8_t month);
float year_average();
int8_t year_min();
int8_t year_max();


//Связный список данных о температуре
struct temperatures_list
{
    struct temperature_on_date_data temp_on_date;
    struct temperatures_list* prev;
    struct temperatures_list* next;
};

//Функции работы со связным списком
void destroy_list();
int8_t push_to_list_front(struct temperature_on_date_data temperature_on_date);
int8_t push_to_list_back(struct temperature_on_date_data temperature_on_date);
int8_t remove_from_list(struct date_data date);
void sort_list();
void print_list();


//Функция разбора CSV-файла
int8_t parse_csv(char* file_path);

#endif
