#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"


Node* createnode(int year) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    assert(newNode);
    newNode->year = year;
    newNode->Eps = 0.0;
    newNode->next = NULL;
    return newNode;
}

List* makelist() {
    List* list = (List*)malloc(sizeof(List));
    if (!list) {
        return NULL;
    }
    list->head = NULL;
    list->serial_num = 0;
    return list;
}


void display(List* Stock, int year, const char* stock) {
    Node* current = Stock->head;
    if (Stock->head == NULL)
        return;
    if (year != 0)
        printf(" Displaying Stock %s  prices of year %d :                      \n\n", stock, year);
    else
        printf(" Displaying Stock %s                                             \n", stock);
    for (; current != NULL; current = current->next) {
        if ((current->year == year) || (year == 0))
        {
            printf(" Yearly EPS:%f, Year:%d                                        \n\n", current->Eps, current->year);
            for (int i = 11; i >= 0; i--)
            {
                if (i < 9)
                    printf(" Month:%d  { 1.Open: %.4f, 2.High: %.4f, 3.Low: %.4f, 4.Close: %.4f, 5.Volume: %.4f },                                \n", i + 1, current->Open[i], current->High[i],
                        current->Low[i], current->close[i], current->Volume[i]);
                else
                    printf(" Month:%d { 1.Open: %.4f, 2.High: %.4f, 3.Low: %.4f, 4.Close: %.4f, 5.Volume: %.4f },                                \n", i + 1, current->Open[i], current->High[i],
                        current->Low[i], current->close[i], current->Volume[i]);

            }
        }
    }
}

void add(List* list, Node* N) {
    Node* current = NULL;
    if (list->head == NULL) {
        list->head = N;
    }
    else {
        current = list->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = N;

    }
}

//deleting by year
void _delete(int year, List* list) {
    Node* current = list->head;
    Node* previous = current;
    while (current != NULL) {
        if (current->year == year) {
            previous->next = current->next;
            if (current == list->head)
                list->head = current->next;
            free(current);
            return;
        }
        previous = current;
        current = current->next;
    }
}

void reverse(List* list) {
    Node* reversed = NULL;
    Node* current = list->head;
    Node* temp = NULL;
    while (current != NULL) {
        temp = current;
        current = current->next;
        temp->next = reversed;
        reversed = temp;
    }
    list->head = reversed;
}

//Reversing the entire list by changing the direction of link from forward to backward using two pointers
void reverse_using_two_pointers(List* list) {
    Node* previous = NULL;
    while (list->head)
    {
        Node* next_node = list->head->next; //points to second node in list
        list->head->next = previous;//at initial making head as NULL
        previous = list->head;//changing the nextpointer direction as to point backward node 
        list->head = next_node; //moving forward by next node
    }
    list->head = previous;
}
//deleting list
void destroy(List* list) {
    Node* current = list->head;
    Node* next = current;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    free(list);
}