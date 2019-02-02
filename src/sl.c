#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include "../include/sl.h"

t_path findBin(Shell* shell, char* command){
    char flag1 = 0, flag2 = 0;
    DIR *d1 = opendir(shell->PATH1);
    struct dirent *dir;
    if(d1){
        while((dir = readdir(d1))){
            //printf("%s\n",dir->d_name);

            if(!strcmp(dir->d_name, command)){
      	        flag1 = 1;
            	break;
            }
        }
        closedir(d1);
    }
    if(flag1) 
        return 1;
    else{
        DIR *d2 = opendir(shell->PATH2);
        if(d2){
            while((dir = readdir(d2))){
                //printf("%s",dir->d_name);
                if(!strcmp(dir->d_name, command)){
                    flag2 = 1;
                    break;
                }
            }
            closedir(d2);
        }
    }
    
    if(flag2)
        return 2;
    return 0;
}
