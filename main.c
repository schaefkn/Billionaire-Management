#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "config.h"

typedef enum { false, true } bool;

struct billionaire_t {
    // Contained Data
    char name[128+1];
    char surname[128+1];
    float net_worth;
    int selfmade_score;

    // Pointers to next and previous list entry
    struct billionaire_t* next;
    struct billionaire_t* prev;
};

struct billionaire_t* balloc();
struct billionaire_t* fillBillonaire(char name[], char surname[], float net_worth, int selfmade_score);

void addBillionaireToLinkedList(struct billionaire_t *billionaire);
void createBillionaire(char name[], char surname[], float net_worth, int selfmade_score);

void printMenu(void);
void printAddBillionaireMenu(void);

void printBillionaires(void);

void handleInput(void);
void handleExit(void);


int getInput();

struct billionaire_t *head;
struct billionaire_t *tail;
struct billionaire_t *current;

int main(void) {
    while(true) {
        printMenu();
        handleInput();
    }
}

struct billionaire_t* balloc() {
    return (struct billionaire_t*) malloc(sizeof(struct billionaire_t));;
}

struct billionaire_t* fillBillonaire(char name[], char surname[], float net_worth, int selfmade_score) {
    struct billionaire_t* tmp = balloc();
    strcpy(tmp->name, name);
    strcpy(tmp->surname, name);
    tmp->net_worth = net_worth;
    tmp->selfmade_score = selfmade_score;
    tmp->next = NULL;
    tmp->prev = NULL;

    return tmp;
}

void addBillionaireToLinkedList(struct billionaire_t *billionaire) {
    struct billionaire_t* current = head;

    if(head == NULL)
        head = billionaire;

    if(tail == NULL) {
        tail = billionaire;
    } else {
        tail->next = billionaire;
        billionaire->prev = tail;
        tail = billionaire;
    }
}

void createBillionaire(char name[], char surname[], float net_worth, int selfmade_score) {
    struct billionaire_t* tmp = fillBillonaire(name, surname, net_worth, selfmade_score);
    addBillionaireToLinkedList(tmp);
}

int getInput() {
    int input = -1;

    do {
        printf("Selection: ");
        scanf("%d", &input);
    } while(input < 0 || input > 9);

    return input;
}

void handleInput() {
    int selection = getInput();

    switch (selection) {
        case 1:
            printAddBillionaireMenu();
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
            break;
        case 7:
            break;
        case 8:
            break;
        case 9:
            break;
        case 0:
            handleExit();
        default:
            break;
    }
}

void handleExit() {
    exit(0);
}

void printMenu(void) {
    printf("==================================================\n");
    printf("                      MENUE                       \n");
    printf("==================================================\n");
    printf("(1) - %s\n", menueItem1);
    printf("(2) - %s\n", menueItem2);
    printf("(3) - %s\n", menueItem3);
    printf("(4) - %s\n", menueItem4);
    printf("(5) - %s\n", menueItem5);
    printf("(6) - %s\n", menueItem6);
    printf("(7) - %s\n", menueItem7);
    printf("(8) - %s\n", menueItem8);
    printf("(9) - %s\n", menueItem9);
    printf("(0) - %s\n", menueItem0);
    printf("\n");
}

void printAddBillionaireMenu() {
    char name[128+1];
    char surname[128+1];
    float net_worth = 0;
    int selfmade_score = 0;

    printf("==================================================\n");
    printf("                  ADD BILLIONAIRE                 \n");
    printf("==================================================\n");
    printf("Name: ");
    scanf("%s", name);
    printf("Last Name: ");
    scanf("%s", surname);
    printf("Net-Worth in Billion Dollars: ");
    scanf("%f", &net_worth);
    printf("Selfmade-Score: ");
    scanf("%d", &selfmade_score);

    createBillionaire(name, surname, net_worth, selfmade_score);
    
    printf("\n");
    printf("%s %s was added to the list of Billionaires!\n", name, surname);

}

void printBillionaires(void) {
    printf("==================================================\n");
    printf("                WORLDS BILLIONAIRES               \n");
    printf("==================================================\n");
}