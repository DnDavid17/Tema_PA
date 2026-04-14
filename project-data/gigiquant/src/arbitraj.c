#include "arbitraj.h"

//functie de adaugare a unui element intr o stiva
static void push(Node **top,double pret) {
    Node *newnode = (Node *)malloc(sizeof(Node));
    if(newnode==NULL) {
        exit(1);
    }
    newnode->pret=pret;
    newnode->next=*top;
    *top=newnode;
}

//functie care verifica daca o stiva e goala
static int isEmpty(const Node *top) {
    return top==NULL;
}

//functie de stergere a uni element dintr o stiva
double pop(Node **top) {
    Node *temp=*top;
    double aux=temp->pret;
    *top=(*top)->next;
    free(temp);
    return aux;
}

//functie de stergere a unei stive
void stergere_stiva(Node **top) {
    while((*top)!=NULL) {
        Node *temp=*top;
        *top=(*top)->next;
        free(temp);
    }
}

//functie de creare a unei cozi
Queue* create_queue() {
    Queue *q=(Queue*)malloc(sizeof(Queue));
    if(q==NULL) {
        exit(1);
    }
    q->first=NULL;
    q->last=NULL;
    return q;
}

//functie de adaugare a unui element in coada
static void enqueue(Queue *q,int zi,double pret,const char *oras) {
    Oportunitate *newnode=(Oportunitate *)malloc(sizeof(Oportunitate));
    if(newnode==NULL) {
        exit(1);
    }
    newnode->pret=pret;
    newnode->zi=zi;
    strcpy(newnode->oras,oras);
    newnode->next=NULL;
    if (q->last==NULL) q->last=newnode;
    else {
        q->last->next=newnode;
        q->last=newnode;
    }
    if (q->first==NULL) q->first=q->last;
}

//crearea stivei de preturi pentru fiecare piata
Piata* creeaza_stiva_piata(FILE *input) {
    Piata *aux = NULL;
    aux = (Piata*) malloc(sizeof(Piata));
    if(aux==NULL) {
        exit(1);
    }
    fgets(aux->nume,25,input);
    aux->stacktop=NULL;
    double val_pret;
    int control=fscanf(input,"%lf",&val_pret);//variabila care verifica daca s-au citit nr
    while (control != EOF && control == 1) {
        push(&aux->stacktop,val_pret);
        control=fscanf(input,"%lf",&val_pret);
    }
    return aux;
}

//gasirea zilelor in care se gaseau oportunitati
void gaseste_oportunitati(Piata *piata1,Piata *piata2,Piata *piata3,Queue* oportunitati) {
    int zi=1;
    while (!isEmpty(piata1->stacktop) && !isEmpty(piata2->stacktop) && !isEmpty(piata3->stacktop)) {
        double pret1=pop(&piata1->stacktop);
        double pret2=pop(&piata2->stacktop);
        double pret3=pop(&piata3->stacktop);
        if (pret1==pret2 && pret2!=pret3) {
            enqueue(oportunitati,zi,fabs(pret2-pret3),piata3->nume);
        }
        else if (pret1==pret3 && pret1!=pret2) {
            enqueue(oportunitati,zi,fabs(pret1-pret2),piata2->nume);
        }
        else if (pret2==pret3 && pret1!=pret3) {
            enqueue(oportunitati,zi,fabs(pret1-pret3),piata1->nume);
        }
        zi++;
    }
}

//afisarea cozii de oportunitati si stergerera ei
void afisare_oportunitati(Queue *q,FILE *output) {
    Oportunitate *aux;
    while (q->first!=NULL) {
        aux=q->first;
        q->first=aux->next;
        fprintf(output,"ziua %d - %.2lf - %s",aux->zi,aux->pret,aux->oras);
        free(aux);
    }
    free(q);
}