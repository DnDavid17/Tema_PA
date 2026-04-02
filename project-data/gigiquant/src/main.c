#include "sharperatio.h"

int main(int argc, char *argv[]) {
    FILE *finput=fopen(argv[1], "r");
    FILE *foutput=fopen(argv[2], "w");
    Porto *head=NULL;
    double rand_med=create_porto(&head,finput);
    fprintf(foutput, "%lf\n", rand_med);
    double volatilitate=calculare_volatilitate(head,rand_med);
    fprintf(foutput, "%lf\n", volatilitate);
    fclose(finput);
    fclose(foutput);
    return 0;
}