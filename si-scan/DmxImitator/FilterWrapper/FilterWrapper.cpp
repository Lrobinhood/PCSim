
#include <stdio.h>

#include "AnaBase.h"

#include "TsPackageFilter.h"
#include "PidFilter.h"
#include "SectionFilter.h"

//#include "../Parser/ParserFunc.h"

#define _INSIDE_FILTER_WRAPPER_

#include "FilterWrapper.h"

// B: local variable define
static u8 sg_Filter_Loop_Flag = 0;
// E: local variable define

// B: Local Function Declare
static void ut_pid_filter_2_section_filter_2_parser(const char *file_name_ptr, u16 pid, u16 tableid, PARSER_FUNC parser_ptr);
// E: Location Function Declare


extern "C" void UT_PidFilter_2_SectionFilter_Parser(const char *file_name_ptr, u16 pid, u16 tableid, PARSER_FUNC parser_ptr)
{
    ut_pid_filter_2_section_filter_2_parser(file_name_ptr, pid, tableid, parser_ptr);
}

extern "C" void UT_Enable_FilterLoop()
{
    sg_Filter_Loop_Flag = 1;
}

extern "C" void UT_Disable_FilterLoop()
{
    sg_Filter_Loop_Flag = 0;
}



//---B: static function Define---
static void ut_pid_filter_2_section_filter_2_parser(const char *file_name_ptr, u16 pid, u16 tableid, PARSER_FUNC parser_ptr)
{
    u8 tsPackBuf[188];

    CFileStream fileStream(file_name_ptr);

    CRoundBuf roundBuf(1024);

    CTsPackageFilter tsFilter;


    size_t fileOffset = 0;

    roundBuf.ConnectFileSource(&fileStream);

    tsFilter.SetRoundBuf(&roundBuf);

    CPidFilter pidFilter;

    pidFilter.SetPid(pid);
    //pidFilter_0x11.SetDebug(true);
    pidFilter.SetRecord(false);
    pidFilter.EnableFilter();

    tsFilter.RegisterNotify(pid, &pidFilter);

    CSectionFilter secFilter;

    secFilter.SetFilterTableId(tableid);
    secFilter.SetDebug(false);
    secFilter.EnableFilter();
    secFilter.SetParserFunc(parser_ptr);


    pidFilter.RegisterNotify(static_cast<void *>(&secFilter), secFilter);

    UT_Enable_FilterLoop();

    while (0!= tsFilter.GetTsPackageEx(tsPackBuf, fileOffset) && 1 == sg_Filter_Loop_Flag)
    {
        ;
    }

    UT_Disable_FilterLoop();

    printf("\n");

}

//---E: static function Define---
