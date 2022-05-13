#ifndef __AUTOTEST_UPDATE_H__
#define __AUTOTEST_UPDATE_H__

bool is_update_test(unsigned int test_type);

int autotest_update(int argc, char* argv[], unsigned int test_type);

int autotest_update_basic(const char *TestIniFile);

#endif
