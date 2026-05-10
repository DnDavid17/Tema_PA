#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

struct ListaActiuni {
    char nume[5];
    double val;
    int variatie;
    int index;
    struct ListaActiuni* next;
};
typedef struct ListaActiuni ListaActiuni;

struct NodArbore {
    ListaActiuni* head;
    struct NodArbore* left;
    struct NodArbore* right;
    int depth;
};
typedef struct NodArbore NodArbore;

void creeaza_lista_actiuni(ListaActiuni** head,FILE* finput);
void creeaza_arbore(NodArbore** root,FILE* finput);
void afiseaza_oglindit(NodArbore* root,FILE* foutput);
void elibereaza(NodArbore** root);