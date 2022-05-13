#ifndef __FILTER_WRAPPER_H__
#define __FILTER_WRAPPER_H__


#ifndef _INSIDE_FILTER_WRAPPER_

typedef unsigned int u32;
typedef unsigned short u16; /*!< 2 bytes, range: 0 to 65536 */
typedef unsigned char u8;

typedef void (*PARSER_FUNC)(u8 *pBuf, u32 u32DataLen);

void UT_PidFilter_2_SectionFilter_Parser(const char *file_name_ptr, u16 pid, u16 tableid, PARSER_FUNC parser_ptr);

void UT_Enable_FilterLoop();

void UT_Disable_FilterLoop();

#else

extern "C" void UT_PidFilter_2_SectionFilter_Parser(const char *file_name_ptr, u16 pid, u16 tableid, PARSER_FUNC parser_ptr);

extern "C" void UT_Enable_FilterLoop();

extern "C" void UT_Disable_FilterLoop();
#endif

#endif

