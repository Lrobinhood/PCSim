#ifndef __AUTOTEST_MAIN_H__
#define __AUTOTEST_MAIN_H__

typedef enum { false, true }bool;

int autotest_main(int argc, char* argv[]);

unsigned int autotest_setloglevel(char *loglevel);

#endif
