#include "sharperatio.h"

double adauga_in_porto(Porto **head,double val) {
    Porto *aux = *head;
    Porto *nou= (Porto*)malloc(sizeof(Porto));
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
double create_porto(Porto **head,FILE *input){
    int total_nr;
    fscanf(input,"%d",&total_nr);
    if (total_nr!=0) {
        double rand_med=0;
        for (int cnt=0;cnt<total_nr;cnt++) {
            double val;
            fscanf(input,"%lf",&val);
            rand_med+=adauga_in_porto(head,val);
        }
        rand_med=rand_med/(total_nr);
        return rand_med;
    }
    else return 0;
}