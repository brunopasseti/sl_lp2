#ifndef SHELL_H
#define SHELL_H
#include <sys/wait.h>   /* Wait for Process Termination */
#include <stdlib.h>     /* General Utilities */

typedef struct Shell{
  char *user;
  char *machineName;
  pid_t fatherPid;
  char *history[100];
  char *PATH1;
  char *PATH2;
}Shell;

typedef char t_path;

void shellExec(Shell* shell, char* command, char* args);

t_path findBin(Shell* shell, char* command); // 0 = NULL, 1 = "/bin", 2 = "/usr/bin"

#endif //SHELL_H