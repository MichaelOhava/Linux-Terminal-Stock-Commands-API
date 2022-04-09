#define _CRT_SECURE_NO_WARNINGS
#include "files_extract.h"

int main(int argc, char* argv[]) {

    List* Stocks[10];
    int size, year_index = 0;
    bool command_stockName = false, command_yearData = false;;
    //
    FILE* file_stock_names;
    file_stock_names = fopen("StocksNames.txt", "w");
    if (argc < 6&& argc>1) {
        for (int i = 1; i < argc; i++)
        {
            if (strcmp(argv[i], "-stockName") == 0)
            {
                fprintf(file_stock_names, "%s",argv[i + 1]);
                command_stockName = true;
            }
            if (strcmp(argv[i], "-yearData") == 0)
            {
                year_index = atoi(argv[i + 1]);
                command_yearData = true;
            }
        }
        fclose(file_stock_names);
        if (command_stockName == false)
        {
            printf("No '-stockName' command indicated followed by a stockname\n");
            exit(1);
        }
        if (command_yearData == false)
        {
            printf("No '-yearData' command indicated followed by a valid year\n");
            exit(1);
        }
        else
            size = load_db(Stocks);

        display_stock_by_year(Stocks[0]->name, year_index, Stocks, size);
        // display_stock_by_year("BBC", 2020, &Stocks, size);

         //
        delete_db(Stocks, size);
    }
    else { printf("Too many arguments!"); exit(1); }
    return 0;

}
