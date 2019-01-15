//
//  Users.cpp
//  working_with_directory
//
//  Created by Евгений Бусс on 15/01/2019.
//  Copyright © 2019 Евгений Бусс. All rights reserved.
//

#include "header.h"
#include "Unit.h"
#include "Folder.h"
#include "File.h"
#include "Users.h"
#include "Exceptions.h"
Users :: Users() {}
Users :: ~Users() {}
//функция справки о доступных командах
void help()
{
    cout << "create  <archive_name> - создать архив" << endl;
    cout << "add file <file_name> archive <archive_name> -  добавить файл в архив" << endl;
    cout << "add file <file_name> archive <archive_name> folder <folder_name> -  добавить файл в папку архива" << endl;
    cout << "delete  archive <archive_name> folder <folder_name> -  удалить папку из архива" << endl;
    cout << "delete file <file_name> archive <archive_name> folder <folder_name -  удалить файл из папки архива" << endl;
    cout << "delete  <archive_name> - удалить архив" << endl;
    cout << "extract  archive <archive_name> folder <folder_name> -  удалить папку из архива" << endl;
    cout << "extract file <file_name> archive <archive_name> folder <folder_name -  удалить файл из папки архива" << endl;
    cout << "info <archive_name>  - вывести информацию об архиве" << endl;
    cout << "info file <file_name> archive <archive_name> - вывести информацию о файле из архива" << endl;
    cout << "info folder <folder_name> archive <archive_name> - вывести информацию о папке из архива" << endl;
}
//функция, обеспечивающая интерфейс
void interface(int argc, const char* argv[])
{
    fstream arch;
    File file_;
    Folder folder_;
    Users users_;
    if (argc == 1)
    {
        cout << "Введите help, чтобы получить список команд" << endl;
        return;
    }
    else if (strcmp(argv[1],"help") == 0 && argc == 2)
    {
        help();
    }
    else if (strcmp(argv[1],"create") == 0 && argc == 3)
    {
        users_.users_create(argc, argv);
    }
    else if (strcmp(argv[1],"add") == 0){
        users_.users_add(argc, argv);
    }
    else if (strcmp(argv[1],"info") == 0 && argc == 6)
    {
        users_.users_info(argc, argv);
    }
    else if (strcmp(argv[1],"delete")==0)
    {
        users_.users_delete(argc, argv);
    }
    else if (strcmp(argv[1],"extract")==0)
    {
        users_.users_extract(argc, argv);
    }
}
//функция, создающая архив
fstream create_archive(string archive_name)
{
    fstream arch;
    arch.open(archive_name,ios::out);
    if (!arch.is_open())
        throw 0;
    arch << "0   " << endl;
    arch.close();
    return arch;
}
//функция, удаляющая архив
void delete_archive(string archive_name)
{
    const char * name = archive_name.c_str();
    remove(name);
}
//функция, выводящая информацию об архиве
void info(string arch_name)
{
    unsigned count=0;
    string names = "";
    fstream stream;
    stream.open(arch_name,ios::in);
    stream >> count;
    cout << "Файл - " << arch_name << endl;
    cout << "Всего файлов: " << count << endl;
    for (int i=0; i < count; i++)
    {
        File file;
        cout << i+1 << ". " <<  file.get_shortname(stream) << endl;
        file.go_to_next(stream);
    }
}
//метод класса, создающий архив
fstream Users :: users_create(int argc, const char* argv[]) {
    fstream arch = create_archive(argv[2]);
    return arch;
}
//метод класса, считывающий аргументы и выполняющий добавление
void Users :: users_add (int argc, const char* argv[]) {
    {
        File file_;
        Folder folder_;
        if (argc == 6)
        {
            if (strcmp(argv[2],"file") == 0 && strcmp(argv[4],"archive") == 0)
            {
                file_.add_(argv[3], argv[5]);
            }
            else if (strcmp(argv[2],"archive") == 0 && strcmp(argv[4],"file") == 0)
            {
                file_.add_(argv[5], argv[3]);
            }
            else
            {
                throw argex;
            }
        }
        else if (argc == 8)
        {
            if (strcmp(argv[2],"file")==0 && strcmp(argv[4],"archive")==0 && strcmp(argv[6],"folder")==0)
            {
                folder_.add_to_folder(argv[3], argv[7], argv[5]);
            }
            else if (strcmp(argv[2],"file")==0 && strcmp(argv[4],"folder")==0 && strcmp(argv[6],"archive")==0)
            {
                folder_.add_to_folder(argv[3], argv[5], argv[7]);
            }
            else if (strcmp(argv[2],"folder")==0 && strcmp(argv[4],"archive")==0 && strcmp(argv[6],"file")==0)
            {
                folder_.add_to_folder(argv[7], argv[3], argv[5]);
            }
            else if (strcmp(argv[2],"folder")==0 && strcmp(argv[4],"file")==0 && strcmp(argv[6],"archive")==0)
            {
                folder_.add_to_folder(argv[5], argv[3], argv[7]);
            }
            else if (strcmp(argv[2],"archive")==0 && strcmp(argv[4],"file")==0 && strcmp(argv[6],"folder")==0)
            {
                folder_.add_to_folder(argv[5], argv[7], argv[3]);
            }
            else if (strcmp(argv[2],"archive")==0 && strcmp(argv[4],"folder")==0 && strcmp(argv[6],"file")==0)
            {
                folder_.add_to_folder(argv[7], argv[5], argv[3]);
            }
        }
        else
        {
            throw argex;
        }
}
}
//метод класса, считывающий аргументы и выполняющий извлечение
void Users :: users_extract(int argc, const char* argv[]){
    File file_;
    Folder folder_;
    if (argc == 6)
    {
        //const char* f="file";
        if (strcmp(argv[2],"file") == 0 && strcmp(argv[4],"archive") == 0)
        {
            string temp = string(argv[3]);
            file_.extract_(argv[3], argv[5]);
        }
        else if (strcmp(argv[2],"archive")==0 && strcmp(argv[4],"file")==0)
        {
            file_.extract_(argv[5], argv[3]);
        }
        else if (strcmp(argv[2],"archive")==0 && strcmp(argv[4],"folder")==0)
        {
            folder_.extract_(argv[5], argv[3]);
        }
        else if (strcmp(argv[2],"folder")==0 && strcmp(argv[4],"archive")==0)
        {
            folder_.extract_(argv[3], argv[5]);
        }
        else
        {
            throw argex;
        }
    }
    else if (argc == 8)
    {
        if (strcmp(argv[2],"file")==0 && strcmp(argv[4],"archive")==0 && strcmp(argv[6],"folder")==0)
        {
            folder_.extract_from_folder(argv[3], argv[7], argv[5]);
        }
        else if (strcmp(argv[2],"file")==0 && strcmp(argv[4],"folder")==0 && strcmp(argv[6],"archive")==0)
        {
            folder_.extract_from_folder(argv[3], argv[5], argv[7]);
        }
        else if (strcmp(argv[2],"folder")==0 && strcmp(argv[4],"archive")==0 && strcmp(argv[6],"file")==0)
        {
            folder_.extract_from_folder(argv[7], argv[3], argv[5]);
        }
        else if (strcmp(argv[2],"folder")==0 && strcmp(argv[4],"file")==0 && strcmp(argv[6],"archive")==0)
        {
            folder_.extract_from_folder(argv[5], argv[3], argv[7]);
        }
        else if (strcmp(argv[2],"archive")==0 && strcmp(argv[4],"file")==0 && strcmp(argv[6],"folder")==0)
        {
            folder_.extract_from_folder(argv[5], argv[7], argv[3]);
        }
        else if (strcmp(argv[2],"archive")==0 && strcmp(argv[4],"folder")==0 && strcmp(argv[6],"file")==0)
        {
            folder_.extract_from_folder(argv[7], argv[5], argv[3]);
        }
    }
    else
    {
        throw argex;
    }
}
//метод класса, считывающий аргументы и выполняющий удаление
void Users :: users_delete (int argc, const char* argv[]) {
    File file_;
    Folder folder_;
    if (argc == 3) delete_archive(argv[2]);
    if (argc == 6)
    {
        if (strcmp(argv[2],"file")==0 && strcmp(argv[4],"archive")==0)
        {
            file_.delete_(argv[3], argv[5]);
        }
        else if (strcmp(argv[2],"archive")==0 && strcmp(argv[4],"file")==0)
        {
            file_.delete_(argv[5], argv[3]);
        }
        else if (strcmp(argv[2],"archive")==0 && strcmp(argv[4],"folder")==0)
        {
            folder_.delete_(argv[5], argv[3]);
        }
        else if (strcmp(argv[2],"folder")==0 && strcmp(argv[4],"archive")==0)
        {
            folder_.delete_(argv[3], argv[5]);
        }
        else
        {
            throw argex;
        }
    }
    else if (argc == 8)
    {
        if (strcmp(argv[2],"file")==0 && strcmp(argv[4],"archive")==0 && strcmp(argv[6],"folder")==0)
        {
            folder_.delete_from_folder(argv[3], argv[7], argv[5]);
        }
        else if (strcmp(argv[2],"file")==0 && strcmp(argv[4],"folder")==0 && strcmp(argv[6],"archive")==0)
        {
            folder_.delete_from_folder(argv[3], argv[5], argv[7]);
        }
        else if (strcmp(argv[2],"folder")==0 && strcmp(argv[4],"archive")==0 && strcmp(argv[6],"file")==0)
        {
            folder_.delete_from_folder(argv[7], argv[3], argv[5]);
        }
        else if (strcmp(argv[2],"folder")==0 && strcmp(argv[4],"file")==0 && strcmp(argv[6],"archive")==0)
        {
            folder_.delete_from_folder(argv[5], argv[3], argv[7]);
        }
        else if (strcmp(argv[2],"archive")==0 && strcmp(argv[4],"file")==0 && strcmp(argv[6],"folder")==0)
        {
            folder_.delete_from_folder(argv[5], argv[7], argv[3]);
        }
        else if (strcmp(argv[2],"archive")==0 && strcmp(argv[4],"folder")==0 && strcmp(argv[6],"file")==0)
        {
            folder_.delete_from_folder(argv[7], argv[5], argv[3]);
        }
    }
    else
    {
        throw argex;
    }
}
//метод класса, считывающий аргументы и выполняющий вывод информации
void Users :: users_info(int argc, const char* argv[]) {
    File file_;
    Folder folder_;
    if (argc == 6)
    {
        if (strcmp(argv[2],"file")==0 && strcmp(argv[4],"archive")==0)
        {
            file_.info(argv[3], argv[5]);
        }
        else if (strcmp(argv[2],"archive")==0 && strcmp(argv[4],"file")==0)
        {
            file_.info(argv[5], argv[3]);
        }
        else if (strcmp(argv[2],"archive")==0 && strcmp(argv[4],"folder")==0)
        {
            folder_.info(argv[5], argv[3]);
        }
        else if (strcmp(argv[2],"folder")==0 && strcmp(argv[4],"archive")==0)
        {
            folder_.info(argv[3], argv[5]);
        }
        else
        {
            throw argex;
        }
    }
    else if (argc == 3) info(argv[2]);
    else
    {
        throw argex;
    }
}


