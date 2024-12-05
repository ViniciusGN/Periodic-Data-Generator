#include "../include/sin_cos_g.h"
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/wait.h>

void generate_graphics(const char *sin_filepath, const char *cos_filepath, const char *gnuplot_cmd_sin, const char *gnuplot_cmd_cos) {
    pid_t graphChild1, graphChild2;

    graphChild1 = fork();
    if (graphChild1 == 0) {
        execlp("gnuplot", "gnuplot", "-persist", gnuplot_cmd_sin, NULL);
        perror("Error executing gnuplot for sine");
        exit(EXIT_FAILURE);
    } else if (graphChild1 > 0) {
        graphChild2 = fork();
        if (graphChild2 == 0) {
            execlp("gnuplot", "gnuplot", "-persist", gnuplot_cmd_cos, NULL);
            perror("Error executing gnuplot for cosine");
            exit(EXIT_FAILURE);
        } else if (graphChild2 > 0) {
            wait(NULL);
            wait(NULL);
        } else {
            perror("Error forking process for cosine graph");
            exit(EXIT_FAILURE);
        }
    } else {
        perror("Error forking process for sine graph");
        exit(EXIT_FAILURE);
    }
}
