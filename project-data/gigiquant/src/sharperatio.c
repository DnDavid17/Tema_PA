#include "sharperatio.h"

//functie de adaugare elemente la sfarsitului listei
static double adauga_in_porto(Porto **head,double val) {
    Porto *aux = *head;
    Porto *nou= (Porto*)malloc(sizeof(Porto));
    if(nou==NULL) {
        exit(1);
    }
    nou->valoare=val;
    nou->next=NULL;
    if(*head==NULL) {
        nou->randament=0;
        *head=nou;
    }
    else {
        while(aux->next!=NULL) aux=aux->next;
        nou->randament=(val-aux->valoare)/aux->valoare;
        aux->next=nou;
    }
    return nou->randament;
}

//functie de creare a prtofoliului/listei+calculare randament mediu
double create_porto(Porto **head,FILE *input){
    int total_nr;
    fscanf(input,"%d",&total_nr);
        double rand_med=0;
        for (int cnt=0;cnt<total_nr;cnt++) {
            double val;
            fscanf(input,"%lf",&val);
            rand_med+=adauga_in_porto(head,val);
        }
        rand_med=rand_med/(total_nr-1);
        return rand_med;
}

//functie de calculare a volatilitatii
double calculare_volatilitate(Porto *head,double rand_med) {
    double volatilitate=0;
    head=head->next;
    int total_nr=1;
    while(head!=NULL) {
        volatilitate+=pow(head->randament-rand_med,2);
        total_nr++;
        head=head->next;
    }
    volatilitate/=total_nr-1;
    volatilitate=sqrt(volatilitate);
    return volatilitate;
}

//functie de trunchiere a numerelor de tip double
double trunchiere(double valoare) {
    return trunc(valoare*1000.0)/1000.0;
}

//functie de eliberare a memoriei ocupat anterior de lista
void elibereaza_porto(Porto **head) {
    Porto *copie;
    while(*head!=NULL) {
        copie=(*head)->next;
        free(*head);
        *head=copie;
    }
    *head=NULL;
}