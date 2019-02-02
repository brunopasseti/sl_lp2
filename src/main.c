#include <unistd.h>     /* Symbolic Constants */
#include <sys/types.h>  /* Primitive System Data Types */
#include <errno.h>      /* Errors */
#include <stdio.h>      /* Input/Output */
#include <sys/wait.h>   /* Wait for Process Termination */
#include <stdlib.h>     /* General Utilities */
#include <string.h>

#include "../include/sl.h"
#include "../include/colors.h"

int main(int argc, char const *argv[])
{
  int status;
  char *newargv = "/home/user/brunopasseti";
  char *cd = "..";
  char *string;
  char input[100];
  char *file = NULL;
  char *args = NULL;
  char finalpath[32] = {};
  Shell shell = {.user = "user", .machineName="machine-pc", .fatherPid = getpid(), .PATH1="/bin", .PATH2="/usr/bin"};
  char color[8];

  //ENQUNTO LOOP PRINCIPAL RODA FAÇA:
    //RECEBA O INPUT ####
    //SE RECEBER EXIT PARA A EXECUÇÃO #######
    //PROCESSA O INPUT(SEPARA O BIN DOS ARGS) ######
    //LOCALIZA O EXECUTAVEL SE ESTA NO /bin OU NO /usr/bin/ #######
    //FORKA O PROCESSO SE FOR O PAI ######
      //ESPERA PELO O FIM DO FILHO (PAI É ESSE PROGRAMA) #######
    //SE NÃO É O FILHO: ######
      // COMBINA O PATH DO BIN COM O BIN ####
      // EXECUTA O BIN COM OS ARGS ####

  if(argc < 2){
    strcpy(color, RESET);
  }else{
    if(!strcmp(argv[1], "-l")){
      puts("Use: ./sl COLOR\nAvailable colors: \n--red or -r\n--green or -g\n--yellow or -y\n--blue or -b\n--magenta or -m\n--cyan or -c");
      return 33;
    }else{
      if(!strcmp(argv[1], "--red") || !strcmp(argv[1], "-r")){
        strcpy(color, Red);
      }else if(!strcmp(argv[1], "--green") || !strcmp(argv[1], "-g")){
        strcpy(color, Green);
      }else if(!strcmp(argv[1], "--yellow") || !strcmp(argv[1], "-y")){
        strcpy(color, Yellow);
      }else if(!strcmp(argv[1], "--blue") || !strcmp(argv[1], "-b")){
        strcpy(color, Blue);
      }else if(!strcmp(argv[1], "--magenta") || !strcmp(argv[1], "-m")){
        strcpy(color, Magenta);
      }else if(!strcmp(argv[1], "--cyan") || !strcmp(argv[1], "-c")){
        strcpy(color, Cyan);
      }
    }
  }

  while(1){
    char console[64];
    sprintf(console, "%s[%s@%s]> %s", color, shell.user, shell.machineName, RESET);
    printf("%s", console);
    if (fgets(input, sizeof input, stdin) != NULL) {

      size_t len = strlen(input);
      if (len > 0 && input[len-1] == '\n') {
        input[--len] = '\0';
      }


      if(len < 1){
        continue;
      }
      if(!strcmp(input, "EXIT")){
        printf("Exiting.\n");
        break;
      }

      char *deli = " ";
      file = strtok(input, deli);
      args = strtok(NULL, deli);

      t_path path = findBin(&shell, file);


      if(fork() != 0){
        waitpid(-1, &status, 0);

        #if DEBUG == 1
        printf("FATHER PID FOR FATHER: %i\n", getpid());
        printf("status filho: %d\n", WEXITSTATUS(status)); // printa na tela o status recebido do filho.
        #endif
      }else{
        if(path == 1){
          strcat(finalpath, "/bin/");

        }else if(path == 2){
          strcat(finalpath, "/usr/bin/");
        }
        strcat(finalpath, file);

        int err = execl(finalpath, file, args, (void *)0);

        if(err == -1)
          printf("Command \'%s\' not found!\n", file);
        #if DEBUG == 1
        printf("SON PID FOR SON: %i\n", getpid());
        printf("FATHER PID FOR SON: %i\n", getppid());
        #endif
      }
    }
    strcpy(finalpath, "");
  }

  return 0;
}
