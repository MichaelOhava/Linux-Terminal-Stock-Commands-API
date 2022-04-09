#define _CRT_SECURE_NO_WARNINGS
#ifndef _FILES_EX
#define  _FILES_EX
#include "linkedlist.h" 
#include <stdio.h> 


   
void Insert_data_to_Db(List* stock, char* Stockname);
Node* Extract_And_Update_Per_Year(float year, char* Stockname, FILE* fesp, FILE* fstock);
char* Creat_esp_filename(char* name);
char* Creat_Stock_filename(char* name);
int Find_How_Many_Years(FILE* file, int* From, int* To);
float* Fillup_arr(FILE* fstock, float currentyear, const char* value);
float get_esp_by_year(int year, FILE* fesp);
void True_Range(int* From_esp, int* To_esp, int* From_s, int* To_s, int* From_both, int* To_both);
int convert_stock_to_num(const char* stock, List** Stocks,int size);
void display_stock(const char* stock, List* Stocks[10]);
void display_db(List* Stocks[10], int stocks_amount);
int load_db(List* Stocks[10]);
void delete_db(List* Stocks[10], int stocks_amount);
//short int get_amount_stocks(List* Stocks[10]);
void display_stock_by_year(const char* stock, int year, List** Stocks,int size);
short int get_stocks_names_in_folder(List* Stocks[10]);
//char* Get_stock_name(int indx);
///Node 
bool ISfloat(char* string);
bool ISfloatesp(char* string);


#endif