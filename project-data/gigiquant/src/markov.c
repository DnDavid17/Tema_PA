#include "markov.h"

graf* initializare_graf(float float_start,float float_dim) {
    graf *graf_Markov=malloc(sizeof(graf));
    if (graf_Markov==NULL) {
        exit(1);
    }
    graf_Markov->noduri=calloc(1,sizeof(interval));
    if (graf_Markov->noduri==NULL) {
        exit(1);
    }
    int rest=(int)float_start%(int)float_dim;
    graf_Markov->noduri[0].valoare=(int)float_start-rest;//stiind ca prima valoare observata se afla in acelasi interval cu valoarea de inceput, creez un caz special pentru aceasta
    graf_Markov->noduri[0].iesiri=-1;
    graf_Markov->mat_de_adiacenta=malloc(sizeof(int*));
    if(graf_Markov->mat_de_adiacenta==NULL) {
        exit(1);
    }
    *(graf_Markov->mat_de_adiacenta)=calloc(1,sizeof(int));
    if (*graf_Markov->mat_de_adiacenta==NULL) {
        exit(1);
    }
    graf_Markov->mat_de_adiacenta[0][0]=-1;
    graf_Markov->NR_noduri=1;
    return graf_Markov;
}

void creeaza_graf(graf *graf_Markov,int nr_observatii,float dim_interval,FILE *finput) {
    int poz_curenta=0;
    for(int i=0;i<nr_observatii;i++) {
        float val_curenta;
        int ok=0;
        fscanf(finput,"%f",&val_curenta);
        graf_Markov->noduri[poz_curenta].iesiri++;
        for(int j=0;j<graf_Markov->NR_noduri;j++) {//caz pentru cand o tranzitie se face intre noduri deja create
            if (val_curenta<(float)graf_Markov->noduri[j].valoare+dim_interval && val_curenta>=(float)graf_Markov->noduri[j].valoare) {
                graf_Markov->mat_de_adiacenta[poz_curenta][j]++;
                poz_curenta=j;
                ok=1;
            }
        }
        if(ok==0) {//ok variabila de control, daca ok=0 intram pe cazul in care trebuie sa cream un nod nou
            graf_Markov->NR_noduri++;
            graf_Markov->noduri=realloc(graf_Markov->noduri,graf_Markov->NR_noduri*sizeof(interval));
            if(graf_Markov->noduri==NULL) {
                exit(1);
            }
            graf_Markov->mat_de_adiacenta=realloc(graf_Markov->mat_de_adiacenta,graf_Markov->NR_noduri*sizeof(int*));
            if(graf_Markov->mat_de_adiacenta==NULL) {
                exit(1);
            }
            for (int k=0;k<graf_Markov->NR_noduri-1;k++) {//alocam spatiu in plus pentru liniile deja existente din matrice
                graf_Markov->mat_de_adiacenta[k]=realloc(graf_Markov->mat_de_adiacenta[k],(graf_Markov->NR_noduri)*sizeof(int));
                if(graf_Markov->mat_de_adiacenta[k]==NULL) {
                    exit(1);
                }
                graf_Markov->mat_de_adiacenta[k][graf_Markov->NR_noduri-1]=0;
            }
            graf_Markov->mat_de_adiacenta[graf_Markov->NR_noduri-1]=calloc(graf_Markov->NR_noduri,sizeof(int));//adaugarea unei noi linii initializata cu 0
            int rest=(int)val_curenta%(int)dim_interval;
            graf_Markov->noduri[graf_Markov->NR_noduri-1].valoare=(int)val_curenta-rest;
            graf_Markov->noduri[graf_Markov->NR_noduri-1].iesiri=0;
            graf_Markov->mat_de_adiacenta[poz_curenta][graf_Markov->NR_noduri-1]++;
            poz_curenta=graf_Markov->NR_noduri-1;
        }
    }
}

static int cmmdc(int a,int b) {//functie de calculare a celui mai mic divizor comun
    while (b!=0) {
        int r=a%b;
        a=b;
        b=r;
    }
    return a;
}

void simulare_zile(graf *g,int nr_zile,int val_cautata,FILE* foutput) {
    int ind_final=-1;
    for (int i=0;i<g->NR_noduri && ind_final==-1;i++) {//gasirea pozitiei nodului in care se afla valoarea finala
        if (g->noduri[i].valoare==val_cautata)
                ind_final=i;
    }
    fractie *probabilitate_past=malloc(g->NR_noduri*sizeof(fractie));
    if (probabilitate_past==NULL) {
        exit(1);
    }
    for (int i=0;i<g->NR_noduri;i++) {
        probabilitate_past[i].numarator=0;
        probabilitate_past[i].numitor=0;
    }
    probabilitate_past[0].numarator=1;
    probabilitate_past[0].numitor=1;
    for (int k=0;k<nr_zile;k++) {
        if (probabilitate_past[ind_final].numarator==0||probabilitate_past[ind_final].numitor==1)//cazul in care un este o fractie probabilitatea
            fprintf(foutput,"%d",probabilitate_past[ind_final].numarator);
        else fprintf(foutput,"%d/%d",probabilitate_past[ind_final].numarator,probabilitate_past[ind_final].numitor);
        if (k!=nr_zile-1) fprintf(foutput,"\n");
        fractie *probabilitate_curr=malloc(g->NR_noduri*sizeof(fractie));
        if (probabilitate_curr==NULL) {
            exit(1);
        }
        for (int i=0;i<g->NR_noduri;i++) {
            probabilitate_curr[i].numarator=0;
            probabilitate_curr[i].numitor=0;
        }
        for (int idx=0;idx<g->NR_noduri;idx++) {//cautarea nodurilor active
            if (probabilitate_past[idx].numarator!=0) {
                for (int j=0;j<g->NR_noduri;j++) {//cautarea vecinilor nodurilor active
                    if (g->mat_de_adiacenta[idx][j]!=0) {
                        int numarator=g->mat_de_adiacenta[idx][j]*probabilitate_past[idx].numarator;
                        int numitor=g->noduri[idx].iesiri*probabilitate_past[idx].numitor;
                        if (probabilitate_curr[j].numitor==0) {
                            probabilitate_curr[j].numarator=numarator;
                            probabilitate_curr[j].numitor=numitor;
                        }
                        else {
                            int div_comun=cmmdc(probabilitate_curr[j].numitor,numitor);
                            int multiplu_comun=(probabilitate_curr[j].numitor)*(numitor)/div_comun;
                            probabilitate_curr[j].numarator*=(multiplu_comun/probabilitate_curr[j].numitor);
                            probabilitate_curr[j].numarator+=(numarator)*(multiplu_comun/numitor);
                            probabilitate_curr[j].numitor=multiplu_comun;
                        }
                    }
                }
            }
        }
        for (int idx=0;idx<g->NR_noduri;idx++) {//actualizarea vectorului de probabilitati
            int div_comun=cmmdc(probabilitate_curr[idx].numarator,probabilitate_curr[idx].numitor);
            probabilitate_past[idx].numarator=probabilitate_curr[idx].numarator/div_comun;
            probabilitate_past[idx].numitor=probabilitate_curr[idx].numitor/div_comun;
        }
        free(probabilitate_curr);
    }
    free(probabilitate_past);
}