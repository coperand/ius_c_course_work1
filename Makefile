#Название целевого бинарника
PROG_NAME = course_work1

#Используемые директории
OBJECT_DIR = objects
BIN_DIR = binary

#Команды компиляции и очистки
CC = gcc
CLEAN = rm -rf

#Списки задействуемых файлов
SOURCES = $(sort $(wildcard src/*.c))
OBJECTS = $(patsubst %.c, $(OBJECT_DIR)/%.o, $(SOURCES))
DEPENDS = $(patsubst %.c, $(OBJECT_DIR)/%.d, $(SOURCES))

#Флаги компиляции
FLAGS = -Wall -MMD -MP -std=c99
LIBS = -lm
INCLUDES = -I src/

#Цель по умолчанию, создающая необходимые директории и производящая сборку
all: makedirs $(PROG_NAME)

#Сборка целевого бинарника
$(PROG_NAME): $(OBJECTS)
	$(CC) $^ -o $(BIN_DIR)/$@ $(LIBS)

#Отслеживание зависимостей
-include $(DEPENDS)

#Сборка объектных файлов из .c
$(OBJECT_DIR)/%.o: %.c
	$(CC) $(FLAGS) $(INCLUDES) -c $< -o $(OBJECT_DIR)/$*.o

#Создание директорий для бинарников и объектных файлов
makedirs:
	mkdir -p $(BIN_DIR)
	mkdir -p $(OBJECT_DIR)
	mkdir -p $(OBJECT_DIR)/src/

#Очистка проекта
cl: clean
clean:
	$(CLEAN) $(BIN_DIR)
	$(CLEAN) $(OBJECT_DIR)
