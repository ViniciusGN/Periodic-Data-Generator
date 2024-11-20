#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include "../include/sin_cos.h"

volatile sig_atomic_t angle = 0;

void handle_sigusr1(int sig) {
    angle += 10;
}

void handle_sigusr2(int sig) {
    angle += 10;
}

int main(int argc, char *argv[]) {
    char *filepath_cos_graphic = "../files/commande_cos.gp";
    char *filepath_sin_graphic = "../files/commande_sin.gp";
 
    pid_t childPid1, childPid2;

    childPid1 = fork();
    if (childPid1 == 0) {
        signal(SIGUSR1, handle_sigusr1);
        while (angle <= 360) {
            double value = calcul_cos_sin(1, angle);
            print_data(1, 1, getpid(), value, angle);
            kill(getppid(), SIGUSR2);
            pause();
        }
        exit(EXIT_SUCCESS);
    } else if (childPid1 > 0) {
        childPid2 = fork();
        if (childPid2 == 0) {
            signal(SIGUSR2, handle_sigusr2);
            while (angle <= 360) {
                double value = calcul_cos_sin(2, angle);
                print_data(2, 2, getpid(), value, angle);
                kill(getppid(), SIGUSR1);
                pause(); 
            }
            exit(EXIT_SUCCESS);
        } else if (childPid2 > 0) {
            signal(SIGUSR1, SIG_IGN);
            signal(SIGUSR2, SIG_IGN);

            kill(childPid1, SIGUSR1);

            wait(NULL);
            wait(NULL);

            plot_data(filepath_sin_graphic);
            plot_data(filepath_cos_graphic);

            printf("Father Process (%d): Ending...\n", getpid());
        } else {
            perror("Error forking process Child Two...");
            exit(EXIT_FAILURE);
        }
    } else {
        perror("Error forking process Child One...");
        exit(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}
