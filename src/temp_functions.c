#include "temp_api.h"

//Головной элемент связного списка
struct temperatures_list* list_head = NULL;


int8_t date_less(struct date_data date1, struct date_data date2)
{
    return date1.year < date2.year ||
          (date1.year == date2.year && date1.month < date2.month) ||
          (date1.year == date2.year && date1.month == date2.month && date1.day < date2.day) ||
          (date1.year == date2.year && date1.month == date2.month && date1.day == date2.day && date1.hour < date2.hour) ||
          (date1.year == date2.year && date1.month == date2.month && date1.day == date2.day && date1.hour == date2.hour && date1.minute < date2.minute);
}
int8_t date_equal(struct date_data date1, struct date_data date2)
{
    return date1.year == date2.year && date1.month == date2.month && date1.day == date2.day && date1.hour == date2.hour && date1.minute == date2.minute;
}


int8_t is_temperature_on_date_valid(struct temperature_on_date_data temperature_on_date)
{
    //Если какое-либо из полей имеет некорректное значение, возвращаем 0 (аля false)
    if(temperature_on_date.date.month < 1 || temperature_on_date.date.month > 12)
        return 0;
    if(temperature_on_date.date.day < 1 || temperature_on_date.date.day > 31)
        return 0;
    if(temperature_on_date.date.hour > 23)
        return 0;
    if(temperature_on_date.date.minute > 59)
        return 0;
    if(temperature_on_date.temperature < -99 || temperature_on_date.temperature > 99)
        return 0;

    //Если всё ок, возвращаем 1 (аля true)
    return 1;
}


float month_average(uint8_t month)
{
    //Суммарная температура и количество записей
    int64_t sum = 0;
    uint64_t count = 0;

    //Перебираем все записи и забираем данные из подходящих
    struct temperatures_list* tmp = list_head;
    while(tmp != NULL)
    {
        if(tmp->temp_on_date.date.month == month)
        {
            sum += tmp->temp_on_date.temperature;
            count++;
        }

        tmp = tmp->next;
    }

    //Если ни одного подходящего значения нет, возвращаем NAN
    if(!count)
        return NAN;

    //Возвращаем результат, поделив сумму на количество
    return 1.0 * sum / count;
}

int8_t month_min(uint8_t month)
{
    //В качестве начального значения берем максимальное для int8_t
    int8_t min = INT8_MAX;

    //Перебираем список в поисках меньших значений
    struct temperatures_list* tmp = list_head;
    while(tmp != NULL)
    {
        if(tmp->temp_on_date.date.month == month && tmp->temp_on_date.temperature < min)
            min = tmp->temp_on_date.temperature;

        tmp = tmp->next;
    }

    //Возвращаем найденное минимальное или INT8_MAX
    return min;
}

int8_t month_max(uint8_t month)
{
    //В качестве начального значения берем минимальное для int8_t
    int8_t max = INT8_MIN;

    //Перебираем список в поисках больших значений
    struct temperatures_list* tmp = list_head;
    while(tmp != NULL)
    {
        if(tmp->temp_on_date.date.month == month && tmp->temp_on_date.temperature > max)
            max = tmp->temp_on_date.temperature;

        tmp = tmp->next;
    }

    //Возвращаем найденное максимальное или INT8_MIN
    return max;
}

float year_average()
{
    //Суммарная температура и количество записей
    int64_t sum = 0;
    uint64_t count = 0;

    //Перебираем все записи и забираем данные из подходящих
    struct temperatures_list* tmp = list_head;
    while(tmp != NULL)
    {
        sum += tmp->temp_on_date.temperature;
        count++;

        tmp = tmp->next;
    }

    //Если ни одного подходящего значения нет, возвращаем NAN
    if(!count)
        return NAN;

    //Возвращаем результат, поделив сумму на количество
    return 1.0 * sum / count;
}

int8_t year_min()
{
    //В качестве начального значения берем максимальное для int8_t
    int8_t min = INT8_MAX;

    //Перебираем список в поисках меньших значений
    struct temperatures_list* tmp = list_head;
    while(tmp != NULL)
    {
        if(tmp->temp_on_date.temperature < min)
            min = tmp->temp_on_date.temperature;

        tmp = tmp->next;
    }

    //Возвращаем найденное минимальное или INT8_MAX
    return min;
}

int8_t year_max()
{
    //В качестве начального значения берем минимальное для int8_t
    int8_t max = INT8_MIN;

    //Перебираем список в поисках больших значений
    struct temperatures_list* tmp = list_head;
    while(tmp != NULL)
    {
        if(tmp->temp_on_date.temperature > max)
            max = tmp->temp_on_date.temperature;

        tmp = tmp->next;
    }

    //Возвращаем найденное максимальное или INT8_MIN
    return max;
}


void destroy_list()
{
    //Проходим по списку и очищаем память каждого элемента
    while(list_head != NULL)
    {
        struct temperatures_list* tmp = list_head;
        list_head = tmp->next;
        free(list_head);
    }
}

int8_t push_to_list_front(struct temperature_on_date_data temperature_on_date)
{
    //Валидируем полученные данные
    if(!is_temperature_on_date_valid(temperature_on_date))
        return -1;

    //Выделяем память под новый элемент
    struct temperatures_list* new_item = malloc(sizeof(struct temperatures_list));
    if(!new_item)
        return -2;

    //Интегрируем элемент в список
    if(list_head)
        list_head->prev = new_item;
    new_item->temp_on_date = temperature_on_date;
    new_item->prev = NULL;
    new_item->next = list_head;

    //Устанавливаем новый элемент в качестве головного
    list_head = new_item;

    return 0;
}

int8_t push_to_list_back(struct temperature_on_date_data temperature_on_date)
{
    //Валидируем полученные данные
    if(!is_temperature_on_date_valid(temperature_on_date))
        return -1;

    //Выделяем память под новый элемент
    struct temperatures_list* new_item = malloc(sizeof(struct temperatures_list));
    if(!new_item)
        return -2;

    //Ищем последний элемент списка, чтобы вставить новый после него
    struct temperatures_list* last_item = list_head;
    while(last_item != NULL && last_item->next != NULL)
        last_item = last_item->next;

    //Интегрируем элемент в список
    new_item->temp_on_date = temperature_on_date;
    new_item->prev = last_item;
    new_item->next = NULL;
    if(last_item)
        last_item->next = new_item;

    //Если головного элемента нет, Устанавливаем новый элемент в качестве него
    if(!list_head)
        list_head = new_item;

    return 0;
}

int8_t remove_from_list(struct date_data date)
{
    //Ищем подходящий элемент в списке путём сравнения дат
    struct temperatures_list* tmp_item = list_head;
    while(tmp_item != NULL && !date_equal(tmp_item->temp_on_date.date, date))
        tmp_item = tmp_item->next;

    //Если не нашли, выходим
    if(tmp_item == NULL)
        return -1;

    //Пересматриваем взаимосвязи между элементами списка с учетом планируемого удаления
    if(tmp_item->prev)
        tmp_item->prev->next = tmp_item->next;
    if(tmp_item->next)
        tmp_item->next->prev = tmp_item->prev;
    if(tmp_item->prev == NULL)
        list_head = tmp_item->next;

    //Очищаем память элемента
    free(tmp_item);

    return 0;
}

void sort_list()
{
    //Двигаемся от первого элемента списка к предпоследнему
    struct temperatures_list* tmp_item = list_head;
    while(tmp_item != NULL && tmp_item->next != NULL)
    {
        //Сравнивам текущий элемент со следующим по дате и в случае необходимости вносим изменения
        if(date_less(tmp_item->next->temp_on_date.date, tmp_item->temp_on_date.date))
        {
            //Меняем текущий и следующий элемент местами в списке
            struct temperatures_list* next_next_item = tmp_item->next->next;
            tmp_item->next->prev = tmp_item->prev;
            tmp_item->prev = tmp_item->next;
            tmp_item->next->next = tmp_item;
            tmp_item->next = next_next_item;

            //Обновляем головной элемент при необходимости
            if(list_head == tmp_item)
                list_head = tmp_item->prev;

            //Сдвигаемся на один элемент назад, чтобы компенсировать смену позиции
            if(tmp_item->prev)
                tmp_item = tmp_item->prev;

            //Двигаемся от текущего элемента списка ко второму
            struct temperatures_list* tmp_item2 = tmp_item;
            while(tmp_item2 != NULL && tmp_item2->prev != NULL)
            {
                //Сравнивам текущий элемент с предыдущим по дате и в случае необходимости вносим изменения
                if(date_less(tmp_item2->temp_on_date.date, tmp_item2->prev->temp_on_date.date))
                {
                    //Меняем текущий и предыдущий элемент местами в списке
                    struct temperatures_list* prev_prev_item = tmp_item2->prev->prev;
                    tmp_item2->prev->next = tmp_item2->next;
                    tmp_item2->next = tmp_item2->prev;
                    tmp_item2->prev->prev = tmp_item2;
                    tmp_item2->prev = prev_prev_item;

                    //Обновляем головной элемент при необходимости
                    if(list_head == tmp_item2->next)
                        list_head = tmp_item2;

                    //Сдвигаемся на один элемент вперед, чтобы компенсировать смену позиции
                    if(tmp_item2->next)
                        tmp_item2 = tmp_item2->next;
                }

                //Сдвигаемся к предыдущему элементу
                tmp_item2 = tmp_item2->prev;
            }
        }

        //Сдвигаемся к следующему элементу
        tmp_item = tmp_item->next;
    }
}

void print_list()
{
    //Проходимся по списку и пишем в стандартный вывод данные каждого
    printf("List:\n");
    struct temperatures_list* tmp_item = list_head;
    while(tmp_item != NULL)
    {
        printf("  %.4u-%.2u-%.2u %.2u:%.2u t: %d\n", tmp_item->temp_on_date.date.year, tmp_item->temp_on_date.date.month, tmp_item->temp_on_date.date.day, tmp_item->temp_on_date.date.hour,
                                                   tmp_item->temp_on_date.date.minute, tmp_item->temp_on_date.temperature);
        tmp_item = tmp_item->next;
    }
}


int8_t parse_csv(char* file_path)
{
    //TODO: Реализовать

    return -1;
}
