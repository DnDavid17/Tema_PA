#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

//structura lista pentru stive
struct Node {
    double pret;
    struct Node *next;
};
typedef struct Node Node;

//structura piata
struct piata {
    char nume[25];
    Node *stacktop;
};
typedef struct piata Piata;

//structura liste pentru cozi
struct Oportunitate {
    int zi;
    char oras[25];
    double pret;
    struct Oportunitate *next;
};
typedef struct Oportunitate Oportunitate;

//structura coada
struct Queue {
    Oportunitate *first;
    Oportunitate *last;
};
typedef struct Queue Queue;

Piata* creeaza_stiva_piata(FILE *input);
Queue* create_queue();
void gaseste_oportunitati(Piata *piata1,Piata *piata2,Piata *piata3,Queue* oportunitati);
void afisare_oportunitati(Queue *q,FILE *output);
void stergere_stiva(Node **top);
