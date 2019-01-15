//
//  Exceptions.h
//  working_with_directory
//
//  Created by Евгений Бусс on 15/01/2019.
//  Copyright © 2019 Евгений Бусс. All rights reserved.
//

#ifndef Exceptions_h
#define Exceptions_h
class archive_opening : public exception
{
public:
    archive_opening() {}
    ~archive_opening() {}
    virtual const char* what() const throw()
    {
        return "Archive opening exception happened";
    }
} archex;
class file_opening : public exception
{
public:
    file_opening() {}
    ~file_opening() {}
    virtual const char* what() const throw()
    {
        return "File opening exception happened";
    }
} fileex;
class tmp_opening : public exception
{
public:
    tmp_opening() {}
    ~tmp_opening() {}
    virtual const char* what() const throw()
    {
        return "Temp file opening exception happened";
    }
} tmpex;
class argument_opening : public exception
{
public:
    argument_opening() {}
    ~argument_opening() {}
    virtual const char* what() const throw()
    {
        return "Archive opening exception happened";
    }
} argex;



#endif /* Exceptions_h */
