//
//  Users.h
//  working_with_directory
//
//  Created by Евгений Бусс on 15/01/2019.
//  Copyright © 2019 Евгений Бусс. All rights reserved.
//

#ifndef Users_h
#define Users_h
#include "header.h"
#include "Unit.h"
#include "Folder.h"
#include "File.h"
//класс, отвечающий за взаимодействие с пользователем
class Users {
public:
    //конструктор по умолчанию
    Users();
    //деструктор
    ~Users();
    //метод класса, считывающий аргументы и выполняющий удаление
    void users_delete(int argc, const char* argv[]);
    //метод класса, считывающий аргументы и выполняющий вывод информации
    void users_info(int argc, const char* argv[]);
    //метод класса, считывающий аргументы и выполняющий ивзлечение
    void users_extract(int argc, const char* argv[]);
    //метод класса, считывающий аргументы и выполняющий добавление
    void users_add (int argc, const char* argv[]);
    //метод класса, считывающий аргументы и выполняющий создание архива
    fstream users_create(int argc, const char* argv[]);
};
//функция создания архива
fstream create_archive(string archive_name);
//функция удаления архива
void delete_archive(string archive_name);
//функция вывода информации об архиве
void info(string arch_name);
//функция - интерфейс
void interface(int argc, const char* argv[]);
//функция вывода справки
void help();
#endif /* Users_h */
