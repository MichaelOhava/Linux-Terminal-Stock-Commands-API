#include "files_extract.h"

#define BUFFER_SIZE 333
#define ARR_OFFSET 1

void Insert_data_to_Db(List* stock, char* Stockname) {

    char str[20] = "", str2[20] = "", * espname, * S_name, buffer[BUFFER_SIZE] = { 0 };
    int totalyears_esp = 0, totalyears_stocks = 0, To_esp, To_s, From_esp, From_s, From_both, To_both;
    FILE* fesp, * fstock;
    Node* temp;
    strcpy(str, Stockname);
    strcpy(str2, Stockname);
    str[strlen(Stockname) + 1] = '\0';
    str2[strlen(Stockname) + 1] = '\0';
    espname = Creat_esp_filename(str); //$name.esp
    S_name = Creat_Stock_filename(str2); //$name.stock

    fesp = fopen(espname, "r"); //files access to the esp and the stock script output
    fstock = fopen(S_name, "r");
    if (fesp == NULL || fstock == NULL) { printf("One of the file isn't exist / there is no match stock to input!\n"); return; }
        

    totalyears_esp = Find_How_Many_Years(fesp, &From_esp, &To_esp); //number of years in the file
    totalyears_stocks = Find_How_Many_Years(fstock, &From_s, &To_s); //the for loop needs to run on the smaller o

    True_Range(&From_esp, &To_esp, &From_s, &To_s, &From_both, &To_both); //extract the years that overlap in both files

    for (float year = From_both; year >= To_both; year--)
    {
        temp = Extract_And_Update_Per_Year(year, Stockname, fesp, fstock); // take the eps , and the stock price 
        add(stock, temp);
    }

    fclose(fesp);
    fclose(fstock);
}


Node* Extract_And_Update_Per_Year(float year, char* Stockname, FILE* fesp, FILE* fstock) {
    Node* T = createnode((int)year);
    T->Eps = get_esp_by_year(year, fesp);
    float* arr;
    arr= Fillup_arr(fstock, year, "open");
    memcpy(T->Open, arr, 12 * sizeof(float));
    free(arr);
    arr=Fillup_arr(fstock, year, "high");
    memcpy(T->High,arr, 12 * sizeof(float));
    free(arr);
    arr=Fillup_arr(fstock, year, "low");
    memcpy(T->Low,arr, 12 * sizeof(float));
    free(arr);
    arr=Fillup_arr(fstock, year, "close");
    memcpy(T->close,arr, 12 * sizeof(float));
    free(arr);
    arr=Fillup_arr(fstock, year, "volume");
    memcpy(T->Volume,arr, 12 * sizeof(float));
    free(arr);

    return T;
}


char* Creat_Stock_filename(char* name) {
    char str[] = ".stock";
    return (strcat(name, str));
}

char* Creat_esp_filename(char* name) {
    char str[] = ".esp";
    return (strcat(name, str));
}

float get_esp_by_year(int year, FILE* fesp) {
    char buffer[BUFFER_SIZE];
    rewind(fesp);
    bool Its_Req_year = false;
    float returningval = 0.0;
    int counter = 0;
    char seps[] = ", :", * token;
    while (fscanf(fesp, "%[^\n] ", buffer) != EOF && Its_Req_year != true) {
        token = strtok(buffer, seps);
        while (token != NULL)
        {
            if ((strlen(token) == 4) && (atof(token) != year) && !ISfloat(token)) token = NULL;

            else if (atof(token) == year)  Its_Req_year = true;

            else if (ISfloatesp(token)) returningval = (float)atof(token);

            token = strtok(NULL, seps);

        }
    }
    return returningval;
}

float* Fillup_arr(FILE* fstock, float currentyear, const char* value) {
    float* arr;
     arr = (float*)malloc(12*sizeof(float));
     for (int j = 0; j < 12; j++)
        arr[j] = 0.0;
    rewind(fstock);
    char buffer[BUFFER_SIZE];
    int counter = 0, currenmonth;
    char seps[] = ", :-", * token;
    while (fscanf(fstock, "%[^\n] ", buffer) != EOF) {
        token = strtok(buffer, seps);
        while (token != NULL)
        {
            if ((strlen(token) == 4) && (atof(token) != currentyear) && !ISfloat(token) && counter == 0) {
                token = NULL;
            }

            else if ((float)atof(token) == currentyear) {
                counter++;

            }

            else if (counter == 1)
            {
                currenmonth = atoi(token);
                counter++;
            }
            else if (strcmp(token, value) == 0 && counter == 2) {
                counter++;
            }
            else if (token != NULL && counter == 3) {
                if (strcmp(value, "volume") != 0) {
                    if (/*strlen(token) > 5*/ISfloat(token)) {
                        arr[currenmonth - ARR_OFFSET] = (float)atof(token);
                    }
                }
                else { arr[currenmonth - ARR_OFFSET] = (float)atof(token); }
                counter = 0;
            }
            token = strtok(NULL, seps);

        }
        counter = 0;
    }
    return arr;
}

bool ISfloat(char* string) {
    bool IsFloat = false;
    for (int i = 0; i < (signed)strlen(string); i++)
    {
        if (string[i] == '.') return true;
        if (string[i] < '0' || string[i]>'9') return false;
    }
    return false;
}

bool ISfloatesp(char* string) {
    bool IsFloat = false;
    for (int i = 0; i < (signed)strlen(string); i++)
    {
        if (string[i] == '.') return true;
        if ((string[i] < '0' || string[i]>'9')&&string[i]!='-') return false;
    }
    return false;
}

int Find_How_Many_Years(FILE* file, int* From, int* To) {
    char buff[10];
    int lenght;
    char buffer[100];
    fscanf(file, "%[^\n] ", buffer);
    lenght = (strlen(buffer) + 2);
    rewind(file);
    fscanf(file, "%4s", buff);
    *From = atoi(buff);
    rewind(file);
    while (!feof(file))
    {
        fscanf(file, "%[^\n]\n", buffer);
    }
    sscanf(buffer, "%4s", buff);
    //fscanf(file, "%4s", buff);
    *To = atoi(buff);
    rewind(file);
    return (abs(*From - *To));
}

void True_Range(int* From_esp, int* To_esp, int* From_s, int* To_s, int* From_both, int* To_both)
//we want the years that overlap, and exist
// in both the EPS file and the STOCK file
{
    if (*From_s < *From_esp)
        *From_both = *From_s;
    else *From_both = *From_esp;
    if (*To_s < *To_esp)
        *To_both = *To_esp;
    else *To_both = *To_s;
}

void delete_db(List* Stocks[10],int stocks_amount) {

    for (int i = 0; i < stocks_amount; i++)
    {
        destroy(Stocks[i]);
    }
}

int load_db(List* Stocks[10])
{
    int stock_amount = get_stocks_names_in_folder(Stocks);
    for (int i = 0; i < stock_amount; i++) 
    {//a max of 10 stocks possible
        Insert_data_to_Db(Stocks[i], Stocks[i]->name);
    }
    return stock_amount;
}

void display_db(List* Stocks[10], int stocks_amount)
{
    for (int i = 0; i < stocks_amount; i++)
    {
        display(Stocks[i], 0, Stocks[i]->name);
       
    }

}

void display_stock(const char* stock, List* Stocks[10])
{
    int i = 0;
    for (int i = 0; i < 10; i++)
        if (strcmp(Stocks[i]->name, stock) == 0)
            break;
    display(Stocks[i], 0, Stocks[i]->name);

   
}

int convert_stock_to_num(const char* stock, List** Stocks,int size)
{ //need to be generic stock!!
    short int i = 0;
    for (i = 0; i < size; i++)
    {
        if (strcmp(stock ,Stocks[i]->name)==0)
            return Stocks[i]->serial_num;
    }
    return -1; //default stock
}

void display_stock_by_year(const char* stock, int year, List** Stocks,int size)
{
    int validstock= convert_stock_to_num(stock, Stocks,size);
    if (validstock != -1) {
        if (year < 2023)
            display(Stocks[validstock], year, stock);
        else printf("year doesnt exist in DB");
    }
    else printf("Invalid stock/stock doesn't exist in DB");

}


short int get_stocks_names_in_folder(List*Stocks[10])
{//no more than 10 stocks in one moment.
    char line[20],*stockname;
    size_t len = 0;
    size_t read;
    short int counter_stocks = 0;
    FILE* file_stock_names;
  file_stock_names = fopen("StocksNames.txt", "r");
   //file_stock_names = fopen("Test.txt","r");
    if (file_stock_names == NULL)
        exit(EXIT_FAILURE);
    
    while (fscanf(file_stock_names,"%[^\n] ", line) != EOF) {
        Stocks[counter_stocks] = makelist();
        stockname = strtok(line, ".");
       strcpy(Stocks[counter_stocks]->name,stockname);
        
        Stocks[counter_stocks]->name[strlen(stockname)+1] = '\0';
        Stocks[counter_stocks]->serial_num = counter_stocks;
        counter_stocks++;
    }


    return counter_stocks;
}

