//
//  Folder.cpp
//  working_with_directory
//
//  Created by Евгений Бусс on 12/12/2018.
//  Copyright © 2019 Евгений Бусс. All rights reserved.
//

#include "header.h"
#include "Unit.h"
#include "Folder.h"
#include "File.h"
#include "Exceptions.h"
Folder :: Folder() {}
Folder :: ~Folder() {}
void  Folder :: info(string name,string arch_name)
{
    temp=0;
    flag = false;
    string fname="";
    stream.open(arch_name, ios_base::in | ios_base :: out);
    if (!stream.is_open())
        throw archex;
    stream >> temp;
    for (int i = 1;i <= temp; i++)
    {
        fname = get_foldername(stream);
        if (fname == name)
        {
            cout << i << ". " <<  get_shortname(stream) << endl;
            cout << "Путь - " << get_path(stream) << endl;
            flag = true;
        }
        go_to_next(stream);
    }
    if (flag == false)
    {
        cout << "Папки " << name << " не существует или она пуста." << endl;
    }
    stream.close();
}
void Folder :: add_to_folder (string file_name,string folder_name,string arch_name)
{
    temp=0;
    sym=0;
    flag = false;
    stream.open(arch_name, ios_base::in | ios_base :: out);
    if (!stream.is_open())
        throw archex;
    tmp.open("/Users/evgenijbuss/Desktop/testfiles/TMP.txt",std::ios::out);
    if (!tmp.is_open())
        throw tmpex;
    stream.seekg(0,ios::beg);
    stream >> temp;
    string check="";
    for (int i = 1; i <= temp; i++)
    {
        check = get_shortname(stream);
        if (check == file_name)
        {
            flag = true;
            break;
        }
        go_to_next(stream);
    }
    if (flag == false)
    {
        cout << "Файл " << file_name << " не найден" << endl;
    }
    string exname=get_pathname(stream);
    long marker = stream.tellg();
    stream.seekg(0,ios::beg);
    for (int i=0;i<marker;i++)
    {
        stream.get(sym);
        tmp<<sym;
    }
    tmp<<get_pathname(stream)<<'$'<<folder_name;
    stream>>exname;
    while (!stream.eof())
    {
        stream.get(sym);
        tmp<<sym;
        if (sym==EOF) break;
        
    }
    tmp.close();
    stream.close();
    stream.open(arch_name,std::ios::out);
    tmp.open("/Users/evgenijbuss/Desktop/testfiles/TMP.txt",std::ios::in);
    while(!tmp.eof())
    {
        tmp.get(sym);
        stream<<sym;
    }
    tmp.close();
    stream.close();
    remove("/Users/evgenijbuss/Desktop/testfiles/TMP.txt");
}
void Folder :: extract_from_folder(string file_name, string folder_name, string arch_name)
{
    temp=0;
    flag = false;
    string fname = "";
    stream.open(arch_name, ios_base::in | ios_base :: out);
    if (!stream.is_open())
        throw archex;
    tmp.open("/Users/evgenijbuss/Desktop/testfiles/TMP.txt",std::ios::out);
    if (!tmp.is_open())
        throw tmpex;
    stream.seekg(0,ios::beg);
    stream>>temp;
    string check="";
    for (int i = 1; i<=temp; i++)
    {
        check = get_foldername(stream);
        fname = get_shortname(stream);
        long begin=stream.tellg();
        if (check==folder_name && fname == file_name)
        {
            File file;
            file.extract_(fname, arch_name);
            flag = true;
        }
        long end=stream.tellg();
        stream.seekg(-end+begin,ios::cur);
        go_to_next(stream);
    }
    if (flag == false)
    {
        cout << "Файл " << file_name << " не найден." << endl;
    }
    stream.close();
    remove("/Users/evgenijbuss/Desktop/testfiles/TMP.txt");
}
void Folder :: delete_from_folder (string file_name, string folder_name, string arch_name)
{
    temp=0;
    sym=0;
    flag = false;
    string fname="";
    stream.open(arch_name, ios_base::in | ios_base :: out);
    if (!stream.is_open())
        throw archex;
    tmp.open("/Users/evgenijbuss/Desktop/testfiles/TMP.txt",std::ios::out);
    if (!tmp.is_open())
        throw tmpex;
    stream.seekg(0,ios::beg);
    stream>>temp;
    string check=get_shortname(stream);
    for ( int i = 1; i<= temp; i++)
    {
        go_to_next(stream);
        check=get_shortname(stream);
        fname = get_foldername(stream);
        if (check == file_name && fname==folder_name)
        {
            flag = true;
            break;
        }
    }
    if (flag == false)
    {
        cout << "Файл " << file_name << " в папке не найден" << endl;
        return;
    }
    string exname=get_pathname(stream);
    long marker = stream.tellg();
    stream.seekg(0,ios::beg);
    for (int i=0;i<marker;i++)
    {
        stream.get(sym);
        tmp<<sym;
    }
    tmp<<get_pathname(stream);
    stream>>exname;
    while (!stream.eof())
    {
        stream.get(sym);
        tmp<<sym;
        if (sym==EOF) break;
        
    }
    tmp.close();
    stream.close();
    stream.open(arch_name,std::ios::out);
    tmp.open("/Users/evgenijbuss/Desktop/testfiles/TMP.txt",std::ios::in);
    if (!tmp.is_open())
        throw tmpex;
    while(!tmp.eof())
    {
        tmp.get(sym);
        stream<<sym;
    }
    tmp.close();
    stream.close();
    remove("/Users/evgenijbuss/Desktop/testfiles/TMP.txt");
}
void Folder :: delete_(string name,string arch_name)
{
    temp=0;
    flag = false;
    stream.open(arch_name, ios_base::in | ios_base :: out);
    if (!stream.is_open())
        throw archex;
    tmp.open("/Users/evgenijbuss/Desktop/testfiles/TMP.txt",std::ios::out);
    if (!tmp.is_open())
        throw tmpex;
    stream.seekg(0,ios::beg);
    stream>>temp;
    string check="";
    for (int i = 1; i <= temp; i++)
    {
        check=get_foldername(stream);
        long begin=stream.tellg();
        if (check==name)
        {
            File file;
            file.delete_(get_shortname(stream),arch_name);
            flag  = true;
        }
        long end=stream.tellg();
        stream.seekg(-end+begin,ios::cur);
        go_to_next(stream);
        if (stream.eof()) return;
    }
    if (flag == false)
    {
        cout << "Папки " << name << " не существует." << endl;
    }
    stream.close();
    tmp.close();
    remove("/Users/evgenijbuss/Desktop/testfiles/TMP.txt");
}
void Folder :: extract_(string name,string arch_name)
{
    temp=0;
    flag = false;
    stream.open(arch_name, ios_base::in | ios_base :: out);
    if (!stream.is_open())
        throw archex;
    tmp.open("/Users/evgenijbuss/Desktop/testfiles/TMP.txt",std::ios::out);
    if (!tmp.is_open())
        throw tmpex;
    stream.seekg(0,ios::beg);
    stream>>temp;
    string check="";
    for (int i = 1; i <= temp; i++)
    {
        check=get_foldername(stream);
        long begin=stream.tellg();
        if (check==name)
        {
            File file;
            file.extract_(get_shortname(stream),arch_name);
            flag = true;
        }
        long end=stream.tellg();
        stream.seekg(-end+begin,ios::cur);
        go_to_next(stream);
    }
    if (flag == false)
    {
        cout << "Папки " << name << " не существует или она пуста." << endl;
    }
    stream.close();
    tmp.close();
    remove("/Users/evgenijbuss/Desktop/testfiles/TMP.txt");
}
