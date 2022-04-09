#ifndef LINKEDLIST_HEADER
#define LINKEDLIST_HEADER
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <malloc.h>

typedef struct node {
    int year;
    float Open[12];
    float High[12];
    float Low[12];
    float close[12];
    float Volume[12];
    float Eps;
    struct node* next;
}Node;



typedef struct list {
    Node* head;
    char name[20];
    short int serial_num;
}List;

List* makelist();
Node* createnode(int year);
void add(List* list, Node* N);
void _delete(int data, List* list);
void display(List* Stock, int year, const char* stock);
void reverse(List* list);
void reverse_using_two_pointers(List* list);
void reverse_using_two_pointers(List* list);
void destroy(List* list);

#endif