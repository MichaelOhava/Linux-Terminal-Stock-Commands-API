
#define _CRT_SECURE_NO_WARNINGS
#include "files_extract.h"

int main(int argc, char* argv[]) {
    if (argc == 1)
    {
        printf("no stocks were entered, exiting..");
        exit(1);
    }
    List* Stocks[10];
    Node* current;
    FILE* file_stock_names;
    file_stock_names = fopen("StocksNames.txt", "w");
    assert(file_stock_names);
    for (int i = 1; i < argc; i++)
    {
        fprintf(file_stock_names,"%s",argv[i]);
        fprintf(file_stock_names, "\n");
    }
    fclose(file_stock_names);

    int stock_amount = load_db(Stocks);
    char* buff = NULL;
    FILE* fp = fopen("Data.csv", "a");
    assert(fp);
    for (int j = 0; j < stock_amount; j++) {
        current = Stocks[j]->head;
        fprintf(fp, "\n%s\n", Stocks[j]->name);
        for (; current != NULL; current = current->next) {

            fprintf(fp, "Yearly EPS:%f, Year:%d\n\n", current->Eps, current->year);


            for (int i = 11; i >= 0; i--)
            {
                fprintf(fp, "%.4f,%.4f,%.4f,%.4f,%.4d\n", current->Open[i], current->High[i],
                    current->Low[i], current->close[i], (int)current->Volume[i]);
            }

        }
    }
    delete_db(Stocks, stock_amount);
    fclose(fp);
    return 0;
}
