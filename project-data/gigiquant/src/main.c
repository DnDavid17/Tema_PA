#include "sharperatio.h"

int main(int argc, const char *argv[]) {
    FILE *finput=fopen(argv[1], "r");
    if(finput==NULL) {
        exit(EXIT_FAILURE);
    }
    FILE *foutput=fopen(argv[2], "w");
    if(foutput==NULL) {
        exit(EXIT_FAILURE);
    }

    Porto *head=NULL;

    double rand_med=create_porto(&head,finput);
    fprintf(foutput, "%.3lf\n", trunchiere(rand_med));

    double volatilitate=calculare_volatilitate(head,rand_med);
    fprintf(foutput, "%.3lf\n", trunchiere(volatilitate));

    double sharpe_ratio=rand_med/volatilitate;
    fprintf(foutput, "%.3lf\n", trunchiere(sharpe_ratio));

    elibereaza_porto(&head);

    fclose(finput);
    fclose(foutput);
    return 0;
}