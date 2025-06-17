#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include "temp_api.h"

//Головной элемент связного списка
struct temperatures_list* list_head = NULL;


int8_t date_less(struct date_data date1, struct date_data date2)
{
    //TODO: Реализовать

    return -1;
}
int8_t date_equal(struct date_data date1, struct date_data date2)
{
    //TODO: Реализовать

    return -1;
}


int8_t is_temperature_on_date_valid(struct temperature_on_date_data temperature_on_date)
{
    //TODO: Реализовать

    return -1;
}


float month_average(uint8_t month)
{
    //TODO: Реализовать

    return -1;
}

int8_t month_min(uint8_t month)
{
    //TODO: Реализовать

    return -1;
}

int8_t month_max(uint8_t month)
{
    //TODO: Реализовать

    return -1;
}

float year_average()
{
    //TODO: Реализовать

    return -1;
}

int8_t year_min()
{
    //TODO: Реализовать

    return -1;
}

int8_t year_max()
{
    //TODO: Реализовать

    return -1;
}


void destroy_list()
{
    //TODO: Реализовать
}

int8_t push_to_list_front(struct temperature_on_date_data temperature_on_date)
{
    //TODO: Реализовать

    return -1;
}

int8_t push_to_list_back(struct temperature_on_date_data temperature_on_date)
{
    //TODO: Реализовать

    return -1;
}

int8_t remove_from_list(struct date_data date)
{
    //TODO: Реализовать

    return -1;
}

void sort_list()
{
    //TODO: Реализовать
}

void print_list()
{
    //TODO: Реализовать
}


int8_t parse_csv(char* file_path)
{
    //TODO: Реализовать

    return -1;
}
