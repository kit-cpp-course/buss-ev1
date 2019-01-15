//
//  Unit.cpp
//  working_with_directory
//
//  Created by Евгений Бусс on 12/12/2018.
//  Copyright © 2019 Евгений Бусс. All rights reserved.
//

#include "header.h"
#include "Unit.h"
Unit :: Unit() {}
unsigned long long Unit :: getsize(fstream &stream)
{
    size=0;
    stream.seekg(0,ios::end);
    size = stream.tellg();
    stream.seekg(0,ios::beg);
    return size+1;
}
string Unit :: get_pathname(fstream & stream)
{
    str = "";
    stream >> str;
    string pathname = "";
    str_size = strlen(str.c_str());
    for (size_t i=0;(i<str_size)&&(str[i]!='$');i++)
    {
        pathname+=str[i];
    }
    stream.seekg(-str_size,ios::cur);
    return pathname;
}
string Unit :: get_shortname(fstream & stream)
{
    str = "";
    i = 0;
    snbeg = 0;
    stream >> str;
    string shortname = "";
    str_size = strlen(str.c_str());
    for (i = 0; i < str_size; i++)
    {
        if (str[i] == '/')
            snbeg = i + 1;
    }
    for (i = snbeg; (i < str_size) && (str[i] != '$'); i++)
    {
        shortname += str[i];
    }
    stream.seekg(-str_size,ios::cur);
    return shortname;
}
string Unit :: get_path (fstream & stream)
{
    str = "";
    i = 0;
    snbeg = 0;
    stream >> str;
    string path = "";
    str_size = strlen(str.c_str());
    for (i = 0; i < str_size; i++)
    {
        if (str[i] == '/')
        {
            snbeg = i;
        }
    }
    for (i = 0; i < snbeg; i++)
    {
        path += str[i];
    }
    stream.seekg(-str_size,ios::cur);
    return path;
}
string Unit :: get_foldername(fstream & stream)
{
    string foldername = "";
    str = "";
    i = 0;
    fnbeg = 0;
    stream >> str;
    str_size = strlen(str.c_str());
    for (i = 0; i < str_size; i++)
    {
        if (str[i] == '$')
            fnbeg = i + 1;
    }
    for (i = fnbeg; i < str_size; i++)
    {
        foldername += str[i];
    }
    stream.seekg(-str_size,ios::cur);
    return foldername;
}
void Unit :: go_to_next(fstream & stream)
{
    str = "";
    char sym = 0;
    int temp = 0;
    stream >> str;
    stream >> temp;
    for (int i = 0;i <= temp; i++)
    {
        stream.get(sym);
        if (sym == EOF) break;
    }
}
Unit :: ~Unit() {}
