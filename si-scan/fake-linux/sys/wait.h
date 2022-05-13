#ifndef __WAIT_H__
#define __WAIT_H__

int WIFSTOPPED(int status);
int WIFSIGNALED(int status);
int WIFEXITED(int status);
int WEXITSTATUS(int status);

#endif
