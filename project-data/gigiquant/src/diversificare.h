#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

struct ListaActiuni {
    char nume[5];//numele actiunii
    double val;//valoarea actiunii la un moment dat
    int variatie;//indica cum se va misca actiunea,pentru a stii cum sa fie parcurs arborele
    int index;//index ul actiunii pentru a tine minte ordinea in care au fost adaugate
    struct ListaActiuni* next;
};
typedef struct ListaActiuni ListaActiuni;

struct NodArbore {
    ListaActiuni* head;
    struct NodArbore* left;
    struct NodArbore* right;
};
typedef struct NodArbore NodArbore;

void creeaza_lista_actiuni(ListaActiuni** head,FILE* finput);
void creeaza_arbore(NodArbore** root,FILE* finput);
void afiseaza_oglindit(NodArbore* root,FILE* foutput);
void elibereaza(NodArbore** root);