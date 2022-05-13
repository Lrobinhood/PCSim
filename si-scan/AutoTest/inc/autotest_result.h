#ifndef __AUTOTEST_RESULT_H__
#define __AUTOTEST_RESULT_H__

#define M_FAILEDCASES_FILENAME "FailedCases.txt"
#define M_PASSEDCASES_FILENAME "PassedCases.txt"

int AutoTest_Result_check_service(int argc, char* argv[]);

void AutoTest_Result_Write_Case(char *filename, int argc, char* argv[]);
#endif 