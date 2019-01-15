//
//  File.cpp
//  working_with_directory
//
//  Created by Евгений Бусс on 12/12/2018.
//  Copyright © 2019 Евгений Бусс. All rights reserved.
//

#include "header.h"
#include "File.h"
#include "Unit.h"
#include "Folder.h"
#include "Exceptions.h"
File :: File()  {}
File :: ~File() {}
void  File :: info(string name,string arch_name)
{
    temp=0;
    size=0;
    flag = false;
    string fname="";
    str="";
    stream.open(arch_name, ios_base::in | ios_base :: out);
    if (!stream.is_open())
        throw archex;
    stream >> temp;
    for (int i = 1;i <= temp; i++)
    {
        fname = get_shortname(stream);
        if (fname == name)
        {
            cout << "Имя - " << fname << endl;
            cout << "Путь - " << get_path(stream) << endl;
            stream >> str;
            stream >> size;
            cout << "Размер - " << size << " байт" << endl;
            flag = true;
        }
        go_to_next(stream);
    }
    if (flag == false)
    {
        cout << "Файла "<< name << " не существует." << endl;
    }
    stream.close();
}
void File :: add_ (string name, string arch_name)
{
    temp=0;
    sym=0;
    fstream file;
    stream.open(arch_name, ios_base::in | ios_base :: out);
    if (!stream.is_open())
        throw archex;
    stream.seekg(0,ios::end);
    file.open(name, std::ios::in);
    if (!file.is_open())
        throw fileex;
    size=getsize(file);
    stream<<name<<endl<<size<<endl;
    while(!file.eof())
    {
        file.get(sym);
        stream<<sym;
    }
    stream<<endl;
    stream.seekg(0,ios::beg);
    stream>>temp;
    stream.seekg(0,ios::beg);
    stream<<temp+1;
    file.close();
    stream.close();
}
void File :: delete_(string name, string arch_name)
{
    flag = false;
    temp=0;
    sym=0;
    stream.open(arch_name, ios_base::in | ios_base :: out);
    if (!stream.is_open())
        throw archex;
    tmp.open("/Users/evgenijbuss/Desktop/testfiles/TMP.txt",std::ios::out);
    if (!tmp.is_open())
        throw tmpex;
    stream.seekg(0,ios::beg);
    stream>>temp;
    string check="";
    string fullcheck="";
    for (int i=1; i<= temp; i++)
    {
        check=get_shortname(stream);
        fullcheck=get_pathname(stream);
        if (check == name || fullcheck == name)
        {
            flag = true;
            break;
        }
        go_to_next(stream);
    }
    if (flag == false)
    {
        cout << "Файл " << name << " не найден." << endl;
        remove("/Users/evgenijbuss/Desktop/testfiles/TMP.txt");
        return;
    }
    long marker = stream.tellg();
    stream.seekg(0,ios::beg);
    for (int i=0; i < marker; i++)
    {
        stream.get(sym);
        tmp<<sym;
    }
    go_to_next(stream);
    stream.get(sym);
    while (!stream.eof())
    {
        stream.get(sym);
        if (sym==EOF) break;
        tmp<<sym;
    }
    tmp.seekg(0,ios::beg);
    tmp<<temp-1;
    tmp.close();
    stream.close();
    stream.open(arch_name,std::ios::out);
    //stream.seekg(marker,ios::beg);
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
void File :: extract_(string name,string arch_name)
{
    temp=0;
    flag = false;
    sym=0;
    stream.open(arch_name, ios_base::in | ios_base :: out);
    if (!stream.is_open())
        throw archex;
    ofstream ex;
    tmp.open("/Users/evgenijbuss/Desktop/testfiles/TMP.txt",std::ios::out);
    if (!tmp.is_open())
        throw tmpex;
    stream.seekg(0,ios::beg);
    stream>>temp;
    string check="";
    string fullcheck="";
    for (int i =1; i<= temp; i++)
    {
        check=get_shortname(stream);
        fullcheck=get_pathname(stream);
        if (check == name || fullcheck == name)
        {
            flag = true;
            break;
        }
        go_to_next(stream);
    }
    if (flag == false)
    {
        cout << "Файл " << name << " не найден." << endl;
        remove("/Users/evgenijbuss/Desktop/testfiles/TMP.txt");
        return;
    }
    string exname=get_pathname(stream);
    ex.open(exname);
    long marker = stream.tellg();
    stream.seekg(0,ios::beg);
    for (int i=0;i<marker;i++)
    {
        stream.get(sym);
        tmp<<sym;
    }
    string s="";
    int temp1=0;
    stream>>s;
    stream>>temp1;
    stream.get(sym);
    for (int i=0;i<=temp1;i++)
    {
        stream.get(sym);
        
        if (sym==EOF) break;
        ex<<sym;
    }
    stream.get(sym);
    while (!stream.eof())
    {
        stream.get(sym);
        tmp<<sym;
        if (sym==EOF) break;
    }
    tmp.seekg(0,ios::beg);
    tmp<<temp-1;
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
    ex.close();
    tmp.close();
    stream.close();
    remove("/Users/evgenijbuss/Desktop/testfiles/TMP.txt");
}

