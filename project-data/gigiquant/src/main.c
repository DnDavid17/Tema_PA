#include "sharperatio.h"

int main(int argc, char *argv[]) {
    FILE *finput=fopen(argv[1], "r");
    FILE *foutput=fopen(argv[2], "w");
    Porto *head=NULL;

    double rand_med=create_porto(&head,finput);
    fprintf(foutput, "%.3lf\n", trunchiere(rand_med));

    double volatilitate=calculare_volatilitate(head,rand_med);
    fprintf(foutput, "%.3lf\n", trunchiere(volatilitate));

    double sharpe_ratio=rand_med/volatilitate;
    fprintf(foutput, "%.3lf\n", trunchiere(sharpe_ratio));
    fclose(finput);
    fclose(foutput);
    return 0;
}