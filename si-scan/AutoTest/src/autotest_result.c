#include <stdio.h>
#include <string.h>

// third party header files

// Ocean Blue Software header files
#include "techtype.h"
#include "dbgfuncs.h"

//#include "frontend.h"
//#include "stbhwtun.h"
#include "stbdpc.h"


#include "stbsitab.h"

#include "ap_dbdef.h"
#include "dba.h"


// CERT Module header files
#include "cert_log.h"
#include "cert_misc.h"

#include "minIni.h"

#include "autotest_result.h"

#define TAG "AUTOTEST-RESULT"

// B: Local Func Declare
static BOOLEAN check_service(char* name, char* type, U16BIT no);
static BOOLEAN check_no_service(char *name, char *type);

static EM_SERVICE_CATEGORY convert_type(char* type);
static void write_failed_case(char* filename, char* str);
// E: Local Func Declare

int AutoTest_Result_check_service(int argc, char* argv[])
{
    int ret = 0;
    char name[64];
    char type[32];
    long no;

    long n;

    char section[32];
    int i = 1;

    BOOLEAN isOnlyChkNumber = AUTOTEST_isOnlyCheckTotalServiceNumber(argv[1]);

    U32BIT search_service_number = DBDEF_GetNumServices();
    U32BIT need_service_number = AUTOTEST_GetTotalServiceNumber(argv[1]);


    CERT_LOG_INFO(TAG, "[%s] Total Searched:%u, Need Searched:%u", __FUNCTION__,
                        search_service_number, need_service_number);

    if (search_service_number == need_service_number)
    {
        ret = 0;
        if (isOnlyChkNumber)
        {
            goto EXIT;
        }
    }
    else if (0 == need_service_number)
    {
        ret = 0;
    }
    else
    {
        ret = 1;
        goto EXIT;
    }



    // 1. Check Must In List Service
    sprintf(section, "RESULT%d", i);
    n = ini_gets(section, "NAME", "dummy", name, sizearray(name), argv[1]);

    if (0 != strcmp(name, "dummy"))
    {
        while (n > 0)
        {
            n = ini_gets(section, "TYPE", "dummy", type, sizearray(type), argv[1]);
            no = ini_getl(section, "NO", -1, argv[1]);

            if (!check_service(name, type, (U16BIT)no))
            {
                ret = 1;
                break;
            }
            else
            {
                ;
            }

            i++;
            sprintf(section, "RESULT%d", i);
            n = ini_gets(section, "NAME", "", name, sizearray(name), argv[1]);
        }
    }
    else // Empty List
    {
        ret = DBDEF_GetNumServices();   // Service Number == 0 is OK
    }

    // 2. Check Must Not In List Service
    if (0 == ret)
    {
        i = 1;

        sprintf(section, "NOT_IN_RESULT%d", i);
        n = ini_gets(section, "NAME", "dummy", name, sizearray(name), argv[1]);

        if (0 != strcmp(name, "dummy"))
        {
            while (n > 0)
            {
                n = ini_gets(section, "TYPE", "dummy", type, sizearray(type), argv[1]);
                no = ini_getl(section, "NO", -1, argv[1]);

                if (!check_no_service(name, type))
                {
                    ret = 1;
                    break;
                }

                i++;
                sprintf(section, "NOT_IN_RESULT%d", i);
                n = ini_gets(section, "NAME", "", name, sizearray(name), argv[1]);
            }
        }
    }

EXIT:

    if (0 != ret && argc > 1)
    {
        char tmp[256];
        sprintf(tmp, "%s %s > scan_result.txt\n", argv[0], argv[1]);
        write_failed_case(M_FAILEDCASES_FILENAME, tmp);
    }
    else if (0 == ret && argc > 1)
    {
        char tmp[256];
        sprintf(tmp, "%s %s\n", argv[0], argv[1]);
        write_failed_case(M_PASSEDCASES_FILENAME, tmp);
    }

    return ret;
}



void AutoTest_Result_Write_Case(char *filename, int argc, char* argv[])
{
    char tmp[256];
    sprintf(tmp, "%s %s > scan_result.txt\n", argv[0], argv[1]);
    write_failed_case(filename, tmp);
}


// B: Local Func Declare
static BOOLEAN check_service(char *name, char *type, U16BIT no)
{
    ADB_SERVICE_REC *s1_ptr     = NULL;
    ADB_TRANSPORT_REC *t_ptr    = NULL;

    s1_ptr = DBDEF_GetNextServiceRec(NULL);
    while (s1_ptr != NULL)
    {
        t_ptr = s1_ptr->transport;
        if ((t_ptr != NULL) /*&& ((tuner_type == SIGNAL_NONE) || (t_ptr->sig_type == tuner_type))*/)
        {
            if (convert_type(type) == CERT_Get_Serv_Category(s1_ptr->serv_type))
            {
                if (NULL != s1_ptr->name_str && NULL != s1_ptr->name_str->str_ptr)
                {
                    U16BIT nchar = 0;
                    U8BIT *utf8_name_ptr = STB_ConvertStringToUTF8(s1_ptr->name_str->str_ptr,
                                                                   &nchar, FALSE, s1_ptr->name_str->lang_code);

                    if (NULL != utf8_name_ptr && 0 == strcmp(name, utf8_name_ptr+1) && (U16BIT)no == s1_ptr->allocated_lcn)
                    {
                        CERT_LOG_DEBG(TAG, "[%s] matched: [name:%s] [type:%s], [no:%u]", __FUNCTION__, name, type, no);
                        return TRUE;
                    }

                    STB_FreeMemory(utf8_name_ptr);
               }
               else
               {
                    ;
               }
            }
        }

        s1_ptr = DBDEF_GetNextServiceRec(s1_ptr);
    }

    CERT_LOG_DEBG(TAG, "[%s] Can't find match: [name:%s] [type:%s], [no:%u]", __FUNCTION__, name, type, no);

    return FALSE;
}

static BOOLEAN check_no_service(char *name, char *type)
{
    ADB_SERVICE_REC *s1_ptr     = NULL;
    ADB_TRANSPORT_REC *t_ptr    = NULL;

    s1_ptr = DBDEF_GetNextServiceRec(NULL);
    while (s1_ptr != NULL)
    {
        t_ptr = s1_ptr->transport;
        if ((t_ptr != NULL) /*&& ((tuner_type == SIGNAL_NONE) || (t_ptr->sig_type == tuner_type))*/)
        {
            if (convert_type(type) == CERT_Get_Serv_Category(s1_ptr->serv_type))
            {
                if (NULL != s1_ptr->name_str && NULL != s1_ptr->name_str->str_ptr)
                {
                    U16BIT nchar = 0;
                    U8BIT *utf8_name_ptr = STB_ConvertStringToUTF8(s1_ptr->name_str->str_ptr,
                                                                   &nchar, FALSE, s1_ptr->name_str->lang_code);

                    if (NULL != utf8_name_ptr && 0 == strcmp(name, utf8_name_ptr+1))
                    {
                        CERT_LOG_DEBG(TAG, "[%s] ERR, find service: [name:%s] [type:%s] in list!", __FUNCTION__, name, type);

                        return FALSE;
                    }

                    STB_FreeMemory(utf8_name_ptr);
               }
               else
               {
                    ;
               }
            }
        }

        s1_ptr = DBDEF_GetNextServiceRec(s1_ptr);
    }

    return TRUE;
}



static EM_SERVICE_CATEGORY convert_type(char *type)
{
    EM_SERVICE_CATEGORY service_category = EM_OTHER_SERVICE;

    if (0 == strcmp(type, "tv"))
    {
        service_category = EM_TV_SERVICE;
    }
    else if (0 == strcmp(type, "radio"))
    {
        service_category = EM_RADIO_SERVICE;
    }
    else
    {
        service_category = EM_OTHER_SERVICE;
    }

    return service_category;
}


static void write_failed_case(char *filename, char *str)
{
    FILE *fp = fopen(filename, "a");

    if (NULL != fp)
    {
        fprintf(fp, "%s", str);

        fclose(fp);
    }
}


// E: Local Func Declare

