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

void printGreeting(void);
void printMenu(void);
void printAddBillionaireMenu(void);

void printWhitespace(int number);
void printWhitespaceOnce(void);

void printAllBillionaires(void);
void printBillionareProperties(struct billionaire_t* billionaire, int number);

void handleInput(void);
void handleExit(void);


int getInput();

struct billionaire_t *head;
struct billionaire_t *tail;
struct billionaire_t *current;

int main(void) {
    printGreeting();
    while(true) {
        printMenu();
        handleInput();
    }
}

struct billionaire_t* balloc(void) {
    return (struct billionaire_t*) malloc(sizeof(struct billionaire_t));;
}

struct billionaire_t* fillBillonaire(char name[], char surname[], float net_worth, int selfmade_score) {
    struct billionaire_t* tmp = balloc();
    strcpy(tmp->name, name);
    strcpy(tmp->surname, surname);
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

int getInput(void) {
    int input = -1;

    do {
        printf("Selection: ");
        scanf("%d", &input);
    } while(input < 0 || input > 9);

    return input;
}

void handleInput(void) {
    int selection = getInput();

    switch (selection) {
        case 1:
            printAddBillionaireMenu();
            break;
        case 2:
            printAllBillionaires();
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

void handleExit(void) {
    exit(0);
}

void printGreeting(void) {
    printf("==================================================\n");
    printf("          Welcome Forbes Billionaires List        \n");
    printf("                   Version: 0.0.1                 \n");
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
    printWhitespaceOnce();
}

void printAddBillionaireMenu(void) {
    char name[128+1];
    char surname[128+1];
    float net_worth = 0;
    int selfmade_score = 0;

    printf("==================================================\n");
    printf("                  ADD BILLIONAIRE                 \n");
    printf("==================================================\n");
    printf("First Name: ");
    scanf("%s", name);
    printf("Last Name: ");
    scanf("%s", surname);
    printf("Net-Worth in Billion Dollars: ");
    scanf("%f", &net_worth);
    printf("Selfmade-Score: ");
    scanf("%d", &selfmade_score);

    createBillionaire(name, surname, net_worth, selfmade_score);
    
    printWhitespaceOnce();
    printf("%s %s was added to the list of Billionaires!\n", name, surname);

}

void printAllBillionaires(void) {
    printf("==================================================\n");
    printf("                WORLDS BILLIONAIRES               \n");
    printf("==================================================\n");

    printWhitespace(2);

    if(head == NULL) {
        printf("There are no Billionaires in your list!\n");
        printWhitespace(2);
    } else {
        int number = 1;
        current = head;
        printBillionareProperties(current, number);
        while(current->next != NULL) {
            number++;
            current = current->next;
            printBillionareProperties(current, number);
        }
        printWhitespaceOnce();
    }

}

void printBillionareProperties(struct billionaire_t* billionaire, int number) {
    printf("================= Billionaire %d =================\n", number);
    printf("First Name: %s\n", billionaire->name);
    printf("Last Name: %s\n", billionaire->surname);
    printf("Net-Worth: $%0.2f Billion Dollars.\n", billionaire->net_worth);
    printf("Selfmade-Score: %d\n", billionaire->selfmade_score);
    printWhitespaceOnce();
}

void printWhitespaceOnce(void) {
    printWhitespace(1);
}


void printWhitespace(int number) {
    for (int i = 0; i < number; ++i) {
        printf("\n");
    }
}