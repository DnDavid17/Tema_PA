#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
struct fractie {
    int numarator;
    int numitor;
};
typedef struct fractie fractie;

struct interval {
    int valoare;
    int iesiri;
};
typedef struct interval interval;

struct graf {
    int NR_noduri;
    interval* noduri;
    int **mat_de_adiacenta;
};
typedef struct graf graf;


graf* initializare_graf(float float_start,float float_dim);
void creeaza_graf(graf* graf_Markov,int nr_observatii,float dim_interval,FILE* finput);
void simulare_zile(graf *g,int nr_zile,int val_cautata,FILE* foutput);