//
//  main.cpp
//  working_with_directory
//
//  Created by Евгений Бусс on 12/12/2018.
//  Copyright © 2019 Евгений Бусс. All rights reserved.
//

#include "header.h"
#include "File.h"
#include "Folder.h"
#include "Users.h"
#include "Exceptions.h"
int main(int argc, const char * argv[])
{
    try
    {
        interface(argc, argv);
    }
    catch (exception &e)
    {
        cout << e.what() << endl;
    }
    catch (...)
    {
        cout << "Something went wrong!" << endl;
    }
    return 0;
}
