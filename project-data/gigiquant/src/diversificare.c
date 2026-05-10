#include "diversificare.h"


void creeaza_lista_actiuni(ListaActiuni** head,FILE* finput) {
    char lista_nume[55];
    fgets(lista_nume,55,finput);

    const char *p=strtok(lista_nume,",\n");
    ListaActiuni* aux=*head;
    while(p!=NULL) {
        ListaActiuni* nou=(ListaActiuni*)malloc(sizeof(ListaActiuni));
        if(nou==NULL) {
            exit(1);
        }
        nou->next=NULL;
        strcpy(nou->nume,p);
        if (*head==NULL) {
            *head=nou;
            aux=*head;
        }
        else {
            aux->next=nou;
            aux=aux->next;
        }
        p=strtok(NULL,",\n");
    }
    aux=*head;
    char lista_valori[100];
    fgets(lista_valori,100,finput);
    p=strtok(lista_valori,",\n");
    int i=0;
    while (p!=NULL) {
        double val=strtod(p,NULL);
        aux->val=val;
        aux->variatie=0;
        aux->index=i;
        aux=aux->next;
        i++;
        p=strtok(NULL,",\n");
    }
}
static void adauga_in_lista(ListaActiuni** head,double valoare,const char* nume,int index) {
    ListaActiuni* nou=(ListaActiuni*)malloc(sizeof(ListaActiuni));
    if(nou==NULL) {
        exit(1);
    }
    nou->val=valoare;
    nou->index=index;
    nou->next=NULL;
    nou->variatie=0;
    strcpy(nou->nume,nume);
    if (*head==NULL) {
        *head=nou;
    }
    else {
        ListaActiuni* aux=*head;
        while (aux->next!=NULL) {
            aux=aux->next;
        }
        aux->next=nou;
    }
}
void creeaza_arbore(NodArbore** root,FILE* finput) {
    char lista_valori[100];
    NodArbore* ultima_pozitie[10];
    for(int i=0;i<10;i++) {
        ultima_pozitie[i]=*root;
    }
    while (fgets(lista_valori,100,finput)!=NULL) {
        const char *p=strtok(lista_valori,",\n");
        int idx_curr=0;
        while (p!=NULL) {
            double valoare=strtod(p,NULL);
            NodArbore* aux_root=ultima_pozitie[idx_curr];
            ListaActiuni* aux=aux_root->head;
            while (aux->index!=idx_curr)
                aux=aux->next;
            if (aux->val<=valoare) {
                aux->variatie=1;
                if (aux_root->right==NULL) {
                    NodArbore* nou=malloc(sizeof(NodArbore));
                    if(nou==NULL) {
                        exit(1);
                    }
                    nou->left=NULL;
                    nou->right=NULL;
                    nou->head=NULL;
                    nou->depth=-1;
                    aux_root->right=nou;
                }
                adauga_in_lista(&aux_root->right->head,valoare,aux->nume,aux->index);
                ultima_pozitie[idx_curr]=aux_root->right;
            }
            else {
                aux->variatie=-1;
                if (aux_root->left==NULL) {
                    NodArbore* nou=malloc(sizeof(NodArbore));
                    if (nou==NULL) {
                        exit(1);
                    }
                    nou->left=NULL;
                    nou->right=NULL;
                    nou->head=NULL;
                    nou->depth=-1;
                    aux_root->left=nou;
                }
                adauga_in_lista(&aux_root->left->head,valoare,aux->nume,aux->index);
                ultima_pozitie[idx_curr]=aux_root->left;
            }
            if (aux_root->depth==0) {
                *root=aux_root;
            }
            idx_curr++;
            p= strtok(NULL,",\n");
        }
   }
}

void afiseaza_oglindit(NodArbore* root,FILE* foutput) {
    int prim=0;
    for (int idx=0;idx<10;idx++) {
        ListaActiuni* aux=root->head;
        while (aux->index!=idx) {
            aux=aux->next;
        }
        NodArbore* actiune=root;
        NodArbore* oglindit=root;
        while (aux->variatie!=0) {
            if (aux->variatie==1) {
                actiune=actiune->right;
                if (oglindit!=NULL)
                    oglindit=oglindit->left;
            }
            else if (aux->variatie==-1) {
                actiune=actiune->left;
                if (oglindit!=NULL)
                oglindit=oglindit->right;
            }
            aux=actiune->head;
            while (aux->index!=idx) {
                aux=aux->next;
            }
        }
        if (oglindit!=NULL) {
            ListaActiuni* aux_ogl=oglindit->head;
            while (aux_ogl!=NULL) {
                if (aux->index<aux_ogl->index) {
                    if (prim!=0) fprintf(foutput,"\n");
                    else prim=1;
                    fprintf(foutput,"%s-%s",aux->nume,aux_ogl->nume);
                }
                aux_ogl=aux_ogl->next;
            }
        }
    }
}
static void elibereaza_lista(ListaActiuni** head) {
    while (*head!=NULL) {
        ListaActiuni* aux=*head;
        *head=(*head)->next;
        free(aux);
    }
}
void elibereaza(NodArbore** root) {
    if ((*root)==NULL) return;
    elibereaza(&(*root)->left);
    elibereaza(&(*root)->right);
    elibereaza_lista(&(*root)->head);
    free(*root);
}