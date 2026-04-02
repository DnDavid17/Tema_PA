#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

struct Porto {
    double valoare;
    double randament;
    struct Porto *next;
};
typedef struct Porto Porto;

double create_porto(Porto **head,FILE *input);
double calculare_volatilitate(Porto *head,double rand_med);
double trunchiere(double valoare);
void elibereaza_porto(Porto **head);