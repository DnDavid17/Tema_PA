#include "sharperatio.h"
#include "arbitraj.h"

int main(int argc, const char *argv[]) {
    FILE *finput=fopen(argv[1], "r");
    if(finput==NULL) {
        exit(1);
    }
    FILE *foutput=fopen(argv[2], "w");
    if(foutput==NULL) {
        exit(1);
    }
    int numar_fisier=argv[1][strlen(argv[1])-4]-'0';
    char cifra2=argv[1][strlen(argv[1])-5];
    if (cifra2 > '0' && cifra2 <= '9') {
        numar_fisier=numar_fisier+(cifra2-'0')*10;
    }
    if(numar_fisier<=5) {//cazul pentru primul task
        Porto *head=NULL;
        double rand_med=create_porto(&head,finput);
        fprintf(foutput, "%.3lf\n", trunchiere(rand_med));

        double volatilitate=calculare_volatilitate(head,rand_med);
        fprintf(foutput, "%.3lf\n", trunchiere(volatilitate));

        double sharpe_ratio=rand_med/volatilitate;
        fprintf(foutput, "%.3lf\n", trunchiere(sharpe_ratio));

        elibereaza_porto(&head);
    }
    else if(numar_fisier<=10) {//cazul pentru al doilea task
        //creare de stive a celor 3 piete
        Piata *piata1,*piata2,*piata3;
        piata1=creeaza_stiva_piata(finput);
        piata2=creeaza_stiva_piata(finput);
        piata3=creeaza_stiva_piata(finput);

        //crearea cozii de oportunitati
        Queue* oportunitati=create_queue();
        gaseste_oportunitati(piata1,piata2,piata3,oportunitati);
        afisare_oportunitati(oportunitati,foutput);
        stergere_stiva(&piata1->stacktop);
        stergere_stiva(&piata2->stacktop);
        stergere_stiva(&piata3->stacktop);
        free(piata1);
        free(piata2);
        free(piata3);
    }
    fclose(finput);
    fclose(foutput);
    return 0;
}