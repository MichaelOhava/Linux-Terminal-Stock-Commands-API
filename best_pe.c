#define _CRT_SECURE_NO_WARNINGS
#include "files_extract.h"

typedef struct stock {
    
    char name[20];
    int pe_value;
}Stock;

void Bubblesort(Stock arr[10],int stock_amount) {
    int temp;
    char temp2[20];
    for (int i = 0; i < stock_amount; i++)
    {
        for (int j = 0; j < stock_amount-i-1; j++)
        {
            if (arr[j].pe_value > arr[j + 1].pe_value) {
                temp = arr[j].pe_value;
                arr[j].pe_value = arr[j + 1].pe_value;
                arr[j + 1].pe_value = temp;
                strcpy(temp2, arr[j].name);
                strcpy(arr[j].name, arr[j+1].name);
                strcpy(arr[j + 1].name, temp2);
            }
        }
    }
}


int  main(int argc, char* argv[]) {
    if (argc == 1)
    {
        printf("no stocks were entered, exiting..");
        exit(1);
    }
    FILE* file_stock_names;
    file_stock_names = fopen("StocksNames.txt", "w");
    assert(file_stock_names);
    for (int i = 1; i < argc; i++)
    {
        fprintf(file_stock_names,"%s",argv[i]);
        fprintf(file_stock_names, "\n");
    }
    fclose(file_stock_names);
    //
    List* Stocks[10];
    Node* current;
    int stock_amount = load_db(Stocks);
    float   sum_of_prices = 0, sum_of_eps = 0;;
    int j = 0;
    Stock res[10];

    for (short int i = 0; i < stock_amount; i++)
    {
       
        current = Stocks[i]->head;
        strcpy(res[i].name, Stocks[i]->name);
        for (; current != NULL && j < 10; current = current->next) {

            for (int k = 0; k < 12; k++)
            {
                sum_of_prices += current->High[k];
            }
            sum_of_eps += current->Eps;
            j++;
        }
        j = 0;
        res[i].pe_value = 0;
        res[i].pe_value += (int)((sum_of_prices / 120) / (sum_of_eps / 10));
        sum_of_prices = 0;
        sum_of_eps = 0;
    }
    
    //qsort((void*)rescpy, stock_amount, sizeof(int), comparator);
    Bubblesort(res,stock_amount);
    printf("Stocks 10 year average ordered by P/E:\n");
    for (int i = 0; i < stock_amount; i++){
   
        if (strlen(res[i].name) == 2)
            printf("%s         %d \n", res[i].name, res[i].pe_value);
        else if (strlen(res[i].name) == 3)
            printf("%s        %d \n", res[i].name, res[i].pe_value);
        else
            printf("%s       %d \n", res[i].name, res[i].pe_value);
    }

    delete_db(Stocks, stock_amount);
    return 0;
}