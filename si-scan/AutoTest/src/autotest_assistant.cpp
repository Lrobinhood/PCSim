#include <stdio.h>
#include <iostream>
#include <io.h>

#include "autotest_assistant.h"

using namespace std;

#ifdef __cplusplus
extern "C" {
#endif

    long AUTOTEST_Get_FileLen(const char* FilePathName)
    {
        FILE* file = fopen(FilePathName, "rb");
        long size = 0;

        if (file)
        {
            size = filelength(fileno(file));
            fclose(file);
        }
        else
        {
            cout << "Open File: [" << *(FilePathName) << "] Failed!" << endl;
        }

        cout << "File:[" << *(FilePathName) << "] Length: " << size << endl;

        return size;
    }

#ifdef __cplusplus
}
#endif