// The default behavior is to not pass the optional parameter, in which case the interval is [0, B].
// If the user provides the "-i" parameter, the interval is changed to [-B, B].
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include "../include/sin_cos.h"

int main(int argc, char *argv[]) {
    char *filepath_cos_graphic = "../files/commande_cos.gp";
    char *filepath_sen_graphic = "../files/commande_sin.gp";
 
    pid_t childPid1, childPid2;
    float angle = 0.0;

    childPid1 = fork();
    childPid2 = fork();
    
    while(angle <= 360.0){
        if(childPid1 == 0){
            singal(SIGUSR1, calcul_cos_sin(1, angle));
            kill(childPid2, SIGUSR1);
        }else{
            perror("Error forking process Child One...");
            exit(EXIT_FAILURE);
        }

        if(childPid2 == 0){
            singal(SIGUSR2, calcul_cos_sin(1, angle));
            kill(childPid1, SIGUSR2);
        } else{
            perror("Error forking process Child Two...");
            exit(EXIT_FAILURE);
        }
        angle += 10.0;
    }

    wait(NULL);
    wait(NULL);

    printf("Father Process (%d): Ending...", getpid());
    return 0;
}

