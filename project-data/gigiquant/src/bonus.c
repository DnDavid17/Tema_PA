#include "cJSON.h"

static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp) {
     size_t realsize = size * nmemb;
     struct MemoryStruct *mem = (struct MemoryStruct *)userp;
    char *ptr = realloc(mem->memory, mem->size + realsize + 1);
    if (!ptr) return 0;
    mem->memory = ptr;
    memcpy(&(mem->memory[mem->size]), contents, realsize);
    mem->size += realsize;
    mem->memory[mem->size] = 0;
    return realsize;
}

double* get_open_prices(const char* symbol, const char* interval, const char* range,int *count_out) {
    CURL *curl_handle;
    struct MemoryStruct chunk = {malloc(1), 0};
    char url[256];
    double *prices = NULL;
    sprintf(url, "https://query1.finance.yahoo.com/v8/finance/chart/%s?interval=%s&range=%s", symbol, interval, range);
    curl_handle = curl_easy_init();
    curl_easy_setopt(curl_handle, CURLOPT_URL, url);
    curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
    curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void *)&chunk);
    curl_easy_setopt(curl_handle, CURLOPT_USERAGENT, "libcurl-agent/1.0");

    if (curl_easy_perform(curl_handle) == CURLE_OK) {
        cJSON *json = cJSON_Parse(chunk.memory);
        cJSON *result = cJSON_GetArrayItem(cJSON_GetObjectItem(cJSON_GetObjectItem(json,"chart"), "result"), 0);
        cJSON *quote = cJSON_GetArrayItem(cJSON_GetObjectItem(cJSON_GetObjectItem(result, "indicators"), "quote"), 0);
        cJSON *open_prices = cJSON_GetObjectItem(quote, "open");

        *count_out = cJSON_GetArraySize(open_prices);
        prices = malloc((*count_out) * sizeof(double));
        for (int i = 0; i < *count_out; i++) {
            cJSON *val = cJSON_GetArrayItem(open_prices, i);
            prices[i] = cJSON_IsNumber(val) ? val->valuedouble : -1.0;
        }
        cJSON_Delete(json);
    }

    curl_easy_cleanup(curl_handle);
    free(chunk.memory);
    return prices;
}


void sharpe_ratio(double *preturi,const char *p,char const *range,int nr_preturi,FILE *foutput) {
    double randament_mediu=0;
    for (int i=1;i<nr_preturi;i++) {
        randament_mediu+=(preturi[i]-preturi[i-1])/preturi[i-1];
    }
    randament_mediu=randament_mediu/(nr_preturi-1);
    double volatilitate=0;
    for (int i=1;i<nr_preturi;i++) {
        double randament_curr=(preturi[i]-preturi[i-1])/preturi[i-1];
        volatilitate+=pow(randament_curr-randament_mediu,2);
    }
    volatilitate=volatilitate/(nr_preturi-1);
    volatilitate=sqrt(volatilitate);
    double sharpe_ratio=randament_mediu/volatilitate;
    fprintf(foutput,"Sharpe ratio pentru %s pe o durata de %s este :%.3lf\n",p,range,sharpe_ratio);
}
void short_vs_long_term(FILE* finput, FILE* foutput) {
    char lista_nume[55];
    fgets(lista_nume,55,finput);//citirea numelor actiunilor

    const char *p=strtok(lista_nume,",\n");
    while (p!=NULL) {
        double *preturi=calloc(35,sizeof(double));
        int nr_preturi;
        preturi=get_open_prices(p,"1d","1mo",&nr_preturi);
        preturi=realloc(preturi,(nr_preturi+1)*sizeof(double));
        sharpe_ratio(preturi,p,"1mo",nr_preturi,foutput);
        free(preturi);

        double *preturi2=calloc(367,sizeof(double));
        preturi2=get_open_prices(p,"1d","1y",&nr_preturi);
        preturi2=realloc(preturi2,(nr_preturi+1)*sizeof(double));
        sharpe_ratio(preturi2,p,"1y",nr_preturi,foutput);
        free(preturi2);
        p=strtok(NULL,",\n");
    }
}