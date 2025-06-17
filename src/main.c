#include <stdio.h>

#include "temp_api.h"

int main()
{
    struct temperature_on_date_data temperature_on_date1;
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
    temperature_on_date3.date.month = 4;
    temperature_on_date3.date.day = 23;
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

    destroy_list();
}
