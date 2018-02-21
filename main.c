#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "config.h"

typedef enum { false, true } bool;

typedef struct billionaire_t {
    // Contained Data
    char name[128+1];
    char surname[128+1];
    float net_worth;
    int selfmade_score;

    // Pointers to next and previous list entry
    struct billionaire_t* next;
    struct billionaire_t* prev;
} Billionaire;

typedef struct billionaire_management {
    struct billionaire_t* head;
    struct billionaire_t* tail;
} BillionaireManagement;

struct billionaire_t* balloc();
struct billionaire_t* fillBillonaire(char name[], char surname[], float net_worth, int selfmade_score);
struct billionaire_t* getBillionaireByIndex(int index);

void addBillionaireToLinkedList(struct billionaire_t *billionaire);
void createBillionaire(char name[], char surname[], float net_worth, int selfmade_score);
void deleteBillionaireFromList(int index);
void editBillionaireFromList(int index);
void swapBillionaireWithNextBillionaire(int index);
void sortBillionairesByCategory(int category);
bool billionaireComesBefore(int category, struct billionaire_t* first, struct billionaire_t* second);
bool searchForProperty(int property, struct billionaire_t* current, char searchFor[]);

void getMemorySizeAllocated(void);
int getLengthOfLinkedList(void);

void printGreeting(void);
void printMenu(void);
void printAddBillionaireMenu(void);
void printDeleteBillionairesMenu(void);
void printShowBillionairesMenu(void);
void printEditBillionairesMenu(void);
void printSortBillionairesMenu(void);
void printSearchForBillionairesMenu(void);
void printSaveInFileMenu(void);
void printLoadFromFileMenu(void);

void printWhitespace(int times);
void printWhitespaceOnce(void);

int printAllBillionares(bool shortened);
void printBillionareProperties(struct billionaire_t* billionaire, int number, bool shortened);

void handleInput(void);
void handleExit(void);

int getInput(int min, int max);

struct billionaire_t *head;
struct billionaire_t *tail;
struct billionaire_t *current;


void insertSampleData(void) {
    createBillionaire("Bill", "Gates", 91.7, 8);
    createBillionaire("Jeff", "Bezos", 120.8, 8);
    createBillionaire("Warren", "Buffet", 87.5, 8);
    createBillionaire("Berta", "Berta", 200, 10);
    createBillionaire("Alpha", "Centaury", 201, 10);
}

int main(void) {
    printGreeting();
    insertSampleData();

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

struct billionaire_t* getBillionaireByIndex(int index) {
    if(index == 0) {
        return head;
    } else {
        int i = 0;
        struct billionaire_t* billionaireToReturn = head;
        while(i < index) {
            if(billionaireToReturn->next != NULL) {
                i++;
                billionaireToReturn = billionaireToReturn->next;
            } else {
                return NULL;
            }
        }
        return billionaireToReturn;
    }
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

void deleteBillionaireFromList(int index) {
    struct billionaire_t* toDelete = getBillionaireByIndex(index);
    char name[128+1];
    char surname[128+1];

    if(toDelete == NULL) {
        printf("Error, there is no Billionaire with index %d\n", index);
        return;
    } else {
        strcpy(name, toDelete->name);
        strcpy(surname, toDelete->surname);

        if (toDelete == head) {
            if(toDelete->next != NULL) {
                toDelete->next->prev = NULL;
                head = toDelete->next;
            } else {
                head = NULL;
            }
        } else if (toDelete == tail) {
            toDelete->prev->next = NULL;
            tail = toDelete->prev;
        } else {
            toDelete->prev->next = toDelete->next;
            toDelete->next->prev = toDelete->prev;
        }
        free(toDelete);
        printf("Deleted Billionaire %s %s\n", name, surname);
    }
}

void getMemorySizeAllocated(void) {
    printf("%lu Bytes allocated\n", getLengthOfLinkedList() * sizeof(struct billionaire_t));
}

int getLengthOfLinkedList(void) {
    struct billionaire_t* current = head;
    int i = 1;

    if(current) {
        while (current->next) {
            i++;
            current = current->next;
        }
    } else {
        i = 0;
    }

    return i;
}

int getInput(int min, int max) {
    int input = -1;

    do {
        printf("Selection: ");
        scanf("%d", &input);
    } while(input < min || input > max);

    return input;
}

void handleInput(void) {
    int selection = getInput(0, 9);

    switch (selection) {
        case 1:
            printAddBillionaireMenu();
            break;
        case 2:
            printShowBillionairesMenu();
            break;
        case 3:
            printDeleteBillionairesMenu();
            break;
        case 4:
            printSortBillionairesMenu();
            break;
        case 5:
            printSaveInFileMenu();
            break;
        case 6:
            printLoadFromFileMenu();
            break;
        case 7:
            printSearchForBillionairesMenu();
            break;
        case 8:
            getMemorySizeAllocated();
            break;
        case 9:
            printEditBillionairesMenu();
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
    printf("Do you want to add another Billionaire ? y/n: ");

    char selection;
    scanf(" %c", &selection);
    getchar();

    if(selection == 'y'|| selection == 'Y') {
        printWhitespaceOnce();
        printAddBillionaireMenu();
    }

    printWhitespaceOnce();
}

void printShowBillionairesMenu(void) {
    printf("==================================================\n");
    printf("                WORLDS BILLIONAIRES               \n");
    printf("==================================================\n");

    printAllBillionares(false);
}

void printDeleteBillionairesMenu(void) {
    printf("==================================================\n");
    printf("                DELETE BILLIONAIRE                \n");
    printf("==================================================\n");

    int number = printAllBillionares(true);
    printWhitespaceOnce();
    if(number != -1) {
        int input = getInput(1, number) - 1;
        deleteBillionaireFromList(input);
    }
}

void printEditBillionairesMenu(void) {
    printf("==================================================\n");
    printf("                 EDIT BILLIONAIRE                 \n");
    printf("==================================================\n");

    int number = printAllBillionares(true);
    printWhitespaceOnce();
    if(number != -1) {
        int index = getInput(1, number) - 1;
        editBillionaireFromList(index);
    }
}

void printSortBillionairesMenu(void) {
    printf("==================================================\n");
    printf("                 SORT BILLIONAIRE                 \n");
    printf("==================================================\n");
    printf("On which property do you want to sort ?\n");
    printf("(1) First Name\n");
    printf("(2) Last Name\n");
    printf("(3) Net-Worth\n");
    printf("(4) Selfmade-Score\n");

    printWhitespaceOnce();
    int input = getInput(1, 4);

    sortBillionairesByCategory(input);
}

void printSearchForBillionairesMenu(void) {
    printf("==================================================\n");
    printf("                SEARCH BILLIONAIRE                \n");
    printf("==================================================\n");
    printf("On which property do you want to search ?\n");
    printf("(1) First Name\n");
    printf("(2) Last Name\n");
    printf("(3) Net-Worth\n");
    printf("(4) Selfmade-Score\n");

    printWhitespaceOnce();
    int input = getInput(1, 4);

    char searchString[128+1];
    printf("Search For: ");
    scanf("%s", searchString);

    printWhitespace(2);

    bool printedOnce = false;

    for(int i = 0; i < getLengthOfLinkedList(); i++) {
        struct billionaire_t* current = getBillionaireByIndex(i);
        if(searchForProperty(input, current, searchString)) {
            printBillionareProperties(current, i+1, false);
            printedOnce = true;
        }
    }

    if(!printedOnce) {
        printf("There are no matching Billionaires!\n");
    }
}

void printSaveInFileMenu(void) {
    printf("==================================================\n");
    printf("                SAVE BILLIONAIRES                 \n");
    printf("==================================================\n");
    printf("Which file do you want to save too: ");

    char file_name[128+1];
    scanf("%s", file_name);
    sprintf(file_name, "%s.csv", file_name);


    FILE *fileToSaveTo = fopen(file_name, "w");
    if(fileToSaveTo == NULL) {
        printf("Fatal error trying to open file!");
        return;
    }

    struct billionaire_t* current;

    for(int i = 0; i < getLengthOfLinkedList(); i++) {
        current = getBillionaireByIndex(i);
        fprintf(fileToSaveTo, "%s %s %f %d\n", current->name, current->surname, current->net_worth, current->selfmade_score);
    }

    fclose(fileToSaveTo);
    printWhitespaceOnce();
    printf("Sucessfully saved to file: %s\n", file_name);
    printWhitespace(3);
}

void printLoadFromFileMenu(void) {
    printf("==================================================\n");
    printf("                LOAD BILLIONAIRES                 \n");
    printf("==================================================\n");
    printf("From which file do you want to load: \n");

}

bool searchForProperty(int property, struct billionaire_t* current, char searchFor[]) {

    char net_worth[64];
    sprintf(net_worth, "%d", (int) current->net_worth);

    char selfmade_score[32];
    sprintf(selfmade_score, "%d", current->selfmade_score);

    switch(property) {
        case 1:
            if(strstr(current->name, searchFor))
                return true;
            else
                return false;
        case 2:
            if(strstr(current->surname, searchFor))
                return true;
            else
                return false;
        case 3:
            if(strcmp(net_worth, searchFor) == 0)
                return true;
            else
                return false;
        case 4:
            if(strcmp(selfmade_score, searchFor) == 0)
                return true;
            else
                return false;
        default:
            return false;
    }
}

void editBillionaireFromList(int index) {
    struct billionaire_t* billionaireToEdit = getBillionaireByIndex(index);
    printBillionareProperties(billionaireToEdit, 0, false);
    printf("Which Property do you want to edit ?\n");
    printf("(1) First Name\n");
    printf("(2) Last Name\n");
    printf("(3) Net Worth\n");
    printf("(4) Selfmade-Score\n");
    int input = getInput(1, 4);

    switch(input) {
        case 1:
            printf("New First Name: ");
            scanf("%s", billionaireToEdit->name);
            break;
        case 2:
            printf("New Last Name: ");
            scanf("%s", billionaireToEdit->surname);
            break;
        case 3:
            printf("New Net-worth: ");
            scanf("%f", &billionaireToEdit->net_worth);
            break;
        case 4:
            printf("New Selfmade-Score: ");
            scanf("%d", &billionaireToEdit->selfmade_score);
            break;
        default:
            break;
    }
}

void sortBillionairesByCategory(int category) {
    for(int i = getLengthOfLinkedList(); i > 1; i--) {
        for(int n = 0; n < i -1; n++) {
            struct billionaire_t* current = getBillionaireByIndex(n);
            if(!billionaireComesBefore(category, current, current->next)) {
                swapBillionaireWithNextBillionaire(n);
            }
        }
    }
}

bool billionaireComesBefore(int category, struct billionaire_t* first, struct billionaire_t* second) {
    if(first == NULL || second == NULL)
        return false;

    switch(category) {
        case 1:
            if(strcmp(first->name, second->name) < 0)
                return true;
            else
                return false;
        case 2:
            if(strcmp(first->surname, second->surname) < 0)
                return true;
            else
                return false;
        case 3:
            if(first->net_worth > second->net_worth)
                return true;
            else
                return false;
        case 4:
            if(first->selfmade_score > second->selfmade_score)
                return true;
            else
                return false;
        default:
            return false;
    }
}


void swapBillionaireWithNextBillionaire(int index) {
    struct billionaire_t* billionaireToSwap = getBillionaireByIndex(index);
    struct billionaire_t* billionaireAfter = billionaireToSwap->next;

    if(billionaireAfter) {
        billionaireToSwap->next = billionaireAfter->next;
        billionaireAfter->prev = billionaireToSwap->prev;
        billionaireAfter->next = billionaireToSwap;
        billionaireToSwap->prev = billionaireAfter;

        if(billionaireToSwap->next) billionaireToSwap->next->prev = billionaireToSwap;
        if(billionaireAfter->prev) billionaireAfter->prev->next = billionaireAfter;
        if(billionaireAfter == tail) tail = billionaireToSwap;
        if(billionaireToSwap == head) head = billionaireAfter;
    }
}

int printAllBillionares(bool shortened) {
    printWhitespace(2);

    if(head == NULL) {
        printf("There are no Billionaires in your list!\n");
        printWhitespace(2);
        return -1;
    } else {
        int number = 1;
        current = head;
        printBillionareProperties(current, number, shortened);
        while(current->next != NULL) {
            number++;
            current = current->next;
            printBillionareProperties(current, number, shortened);
        }
        printWhitespaceOnce();
        return number;
    }
}

void printBillionareProperties(struct billionaire_t* billionaire, int number, bool shortened) {
    if(shortened) {
        printf("Billionaire (%d): %s %s\n", number, billionaire->name, billionaire->surname);
    } else {
        printf("================= Billionaire %d =================\n", number);
        printf("First Name: %s\n", billionaire->name);
        printf("Last Name: %s\n", billionaire->surname);
        printf("Net-Worth: $%0.2f Billion Dollars.\n", billionaire->net_worth);
        printf("Selfmade-Score: %d\n", billionaire->selfmade_score);
        printWhitespaceOnce();
    }
}

void printWhitespaceOnce(void) {
    printf("\n");
}

void printWhitespace(int times) {
    for (int i = 0; i < times; ++i) {
        printf("\n");
    }
}