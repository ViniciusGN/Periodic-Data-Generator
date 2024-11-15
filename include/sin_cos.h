#ifndef SINCOS_H
#define SINCOS_H

double calcul_cos_sin(int type, float angle);
void plot_data(const char *filepath);
void print_data(int type, int child_number, int pid_child, double value, float angle);
void register_data(int type, float angle, double value, const char *filepath);

#endif  // SINCOS_H