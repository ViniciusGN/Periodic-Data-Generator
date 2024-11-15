#include "../include/sin_cos.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void plot_data(const char *filepath) {
    execlp("gnuplot", "gnuplot", "-persist", filepath, NULL);
    perror("Error executing gnuplot");
    exit(EXIT_FAILURE);
}

double calcul_cos_sin(int type, float angle){
    double radians = angle * (M_PI / 180.0);
    switch(type){
        case 1: return sin(radians);
        case 2: return cos(radians);
    }
}

void print_data(int type, int child_number, int pid_child, double value, float angle){
    char *filepath_cos_data = "../files/cosinus.txt";
    char *filepath_sin_data = "../files/sinus.txt";

    switch(type){
        case 1:
            printf("Fils %d (%d): sinus(%f)    =   %f", child_number, pid_child, angle, value);
            register_data(type, angle, value, filepath_sin_data);
            break;
        case 2:
            printf("Fils %d (%d): cosinus(%f)  =   %f", child_number, pid_child, angle, value);
            register_data(type, angle, value, filepath_cos_data);
            break;
    }

}

void register_data(int type, float angle, double value, const char *filepath){
    FILE *pont_file;
    pont_file = fopen(filepath, "a");
    fprintf(pont_file, "%f %f\n", angle, value);
    fclose(pont_file);
}