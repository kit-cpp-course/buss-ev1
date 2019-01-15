//
//  Folder.h
//  working_with_directory
//
//  Created by Евгений Бусс on 12/12/2018.
//  Copyright © 2019 Евгений Бусс. All rights reserved.
//

#ifndef Folder_h
#define Folder_h
#include "header.h"
#include "Unit.h"
#include "File.h"
//класс, производный от класса Unit, предназначенный для работами с папками в архиве
class Folder : public Unit
{
    //переменная, принимающая true, если папка была найдена в архиве, false в обратном случае
    bool flag;
    //переменная, используемая для считывания количества файлов, лежащих в архиве
    int temp;
    //переменная, использующаяся для посимвольного считывания из файла/архива
    char sym;
    //переменная, хранящая в себе файловый поток для архива
    fstream stream;
    //переменная, хранящая в себе файловый поток для открытия временного файла при удалении/извлечении 
    fstream tmp;
public:
    //конструктор по умолчанию
    Folder();
    //деструктор
    ~Folder();
    //функция, выводящая в консоль информацию о выбранной папке
    void info(string name,string arch_name);
    //функция добавления файла в папку
    void add_to_folder (string file_name,string folder_name,string arch_name);
    //функция удаления файла из папки
    void delete_from_folder(string file_name,string folder_name,string arch_name);
    //функция извлечения файла из папки
    void extract_from_folder(string file_name,string folder_name,string arch_name);
    //функция, удаляющая папку из архива
    void delete_(string name, string arch_name);
    //функция, извлекающая папку из архива
    void extract_(string name, string arch_name);
};

#endif /* Folder_h */
