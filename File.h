//
//  File.h
//  working_with_directory
//
//  Created by Евгений Бусс on 12/12/2018.
//  Copyright © 2019 Евгений Бусс. All rights reserved.
//

#ifndef File_h
#define File_h
#include "header.h"
#include "Unit.h"
//класс, производный от класса Unit, предназначенный для работы с файлами
class File : public Unit
{
    //переменная, принимающая true, если файл был найден в архиве, false в обратном случае
    bool flag;
    //переменная, используемая для считывания количества файлов, лежащих в архиве
    int temp;
    //переменная, использующаяся для посимвольного считывания из файла/архива
    char sym;
    //переменная, хранящая в себе файловый поток для архива
    fstream stream;
    //переменная, хранящая в себе файловый поток для открытия временного файла при удалении/извлечении
    fstream tmp;
public :
    //конструктор по умолчанию
    File();
    //деструктор
    ~File();
    //функция, выводящая в консоль информацию о файле
    void info(string name,string arch_name);
    //функция добавления файла в архив
    void add_(string name,string arch_name);
    //функция удаления файла из архива
    void delete_(string name,string arch_name);
    //функция извлечения файла из архива
    void extract_(string name,string arch_name);
};
#endif /* File_h */
