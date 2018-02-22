#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "config.h"

/**
 * Boolean Value declaration
 */
typedef enum { false, true } bool;

/**
 * Billionaire Struct to hold information about one Billionaire.
 */
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

/**
 * Billionaire Management Struct to manage head and tail.
 */
typedef struct billionaire_management {
    struct billionaire_t* head;
    struct billionaire_t* tail;
} BillionaireManagement;

struct billionaire_t* balloc();
struct billionaire_t* fillBillonaire(char name[], char surname[], float net_worth, int selfmade_score);
struct billionaire_t* getBillionaireByIndex(int index, BillionaireManagement *bm);

void addBillionaireToLinkedList(struct billionaire_t *billionaire, BillionaireManagement *bm);
void createBillionaire(char name[], char surname[], float net_worth, int selfmade_score, BillionaireManagement *bm);
void deleteBillionaireFromList(int index, bool printDeletion, BillionaireManagement *bm);
void deleteAllBillionairesFromLinkedList(BillionaireManagement *bm);
void editBillionaireFromList(int index, BillionaireManagement *bm);
void swapBillionaireWithNextBillionaire(int index, BillionaireManagement *bm);
void sortBillionairesByCategory(int category, BillionaireManagement *bm);
void loadBillionairesFromFile(char file_name[], BillionaireManagement *bm);
bool billionaireComesBefore(int category, struct billionaire_t* first, struct billionaire_t* second);
bool searchForProperty(int property, struct billionaire_t* current, char searchFor[]);

int getLengthOfLinkedList(BillionaireManagement *bm);

void printGreeting(void);
void printMenu(void);
void printAddBillionaireMenu(BillionaireManagement *bm);
void printShowBillionairesMenu(BillionaireManagement *bm);
void printDeleteBillionairesMenu(BillionaireManagement *bm);
void printSortBillionairesMenu(BillionaireManagement *bm);
void printSaveInFileMenu(BillionaireManagement *bm);
void printLoadFromFileMenu(BillionaireManagement *bm);
void printSearchForBillionairesMenu(BillionaireManagement *bm);
void getMemorySizeAllocated(BillionaireManagement *bm);
void printEditBillionairesMenu(BillionaireManagement *bm);

void printWhitespace(int times);
void printWhitespaceOnce(void);

int printAllBillionares(bool shortened, BillionaireManagement *bm);
void printBillionareProperties(struct billionaire_t* billionaire, int number, bool shortened);

void handleInput(BillionaireManagement *bm);
void handleExit(BillionaireManagement *bm);
void handleAddBillionaire(char name[], char surname[], float net_worth, int selfmade_score, BillionaireManagement *bm);
void handleSaveBillionairesToFile(char file_name[], BillionaireManagement *bm);

int getInput(int min, int max);

const char* getfield(char* line, int num);

/**
 * Inserts sample data
 * @param bm BillionaireManagement Pointer
 */
void insertSampleData(BillionaireManagement *bm) {
    createBillionaire("Bill", "Gates", 91.7, 8, bm);
    createBillionaire("Jeff", "Bezos", 120.8, 8, bm);
    createBillionaire("Warren", "Buffet", 87.5, 8, bm);
    createBillionaire("Berta", "Berta", 200, 10, bm);
    createBillionaire("Alpha", "Centaury", 201, 10, bm);
}

/**
 * Main method
 */
int main(int argc, const char* argv[]) {
    BillionaireManagement bm;
    bm.head = NULL;
    bm.tail = NULL;

    if(argc == 2) {
        char file_name[128+1];
        strcpy(file_name, argv[1]);
        loadBillionairesFromFile(file_name, &bm);
    }

    printGreeting();
    while(true) {
        printMenu();
        handleInput(&bm);
    }
}

/**
 * Allocates memory for a Billionaire and gives back to pointer to the memory space.
 * @return struct billionaire_t*
 */
struct billionaire_t* balloc(void) {
    return (struct billionaire_t*) malloc(sizeof(struct billionaire_t));;
}

/**
 * Fills a Billionaire struct with supplied data.
 * @param name First Name of Billionaire
 * @param surname Last Name of Billionaire
 * @param net_worth Net-Worth of Billionaire
 * @param selfmade_score Selfmade-Score of Billionaire
 * @return struct billionaire_t*
 */
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

/**
 * Gets Billionaire by supplied index. If index is greater than the length of the list , NULL will be returned.
 * @param index Index from Billionaire
 * @param bm BillionaireManagement Pointer
 * @return struct billionaire_t*
 */
struct billionaire_t* getBillionaireByIndex(int index, BillionaireManagement *bm) {
    if(index == 0) {
        return bm->head;
    } else {
        int i = 0;
        struct billionaire_t* billionaireToReturn = bm->head;
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

/**
 * Adds a supplied billionaire to the linked list from BillionaireManagement struct.
 * @param billionaire Billionaire to be added to linked list.
 * @param bm BillionaireManagement Pointer
 */
void addBillionaireToLinkedList(struct billionaire_t *billionaire, BillionaireManagement *bm) {
    if(bm->head == NULL)
        bm->head = billionaire;

    if(bm->tail == NULL) {
        bm->tail = billionaire;
    } else {
        bm->tail->next = billionaire;
        billionaire->prev = bm->tail;
        bm->tail = billionaire;
    }
}

/**
 * Creates a billionaire and adds them to the linked list.
 * @param name First Name of Billionaire
 * @param surname Last Name of Billionaire
 * @param net_worth Net-Worth of Billionaire
 * @param selfmade_score Selfmade-Score of Billionaire
 * @param bm
 */
void createBillionaire(char name[], char surname[], float net_worth, int selfmade_score, BillionaireManagement *bm) {
    struct billionaire_t* tmp = fillBillonaire(name, surname, net_worth, selfmade_score);
    addBillionaireToLinkedList(tmp, bm);
}

/**
 * Deletes a Billionaire from the linked list by supplied index. If there is no Billionaire at this index, an error is printed.
 * @param index Index of Billionaire to be deleted.
 * @param printDeletion Should the method print deletion to the console
 * @param bm BillionaireManagement Pointer
 */
void deleteBillionaireFromList(int index, bool printDeletion, BillionaireManagement *bm) {
    struct billionaire_t* toDelete = getBillionaireByIndex(index, bm);
    char name[128+1];
    char surname[128+1];

    if(toDelete == NULL) {
        printf("Error, there is no Billionaire with index %d\n", index);
        return;
    } else {
        strcpy(name, toDelete->name);
        strcpy(surname, toDelete->surname);

        if (toDelete == bm->head) {
            if(toDelete->next != NULL) {
                toDelete->next->prev = NULL;
                bm->head = toDelete->next;
            } else {
                bm->head = NULL;
            }
        } else if (toDelete == bm->tail) {
            toDelete->prev->next = NULL;
            bm->tail = toDelete->prev;
        } else {
            toDelete->prev->next = toDelete->next;
            toDelete->next->prev = toDelete->prev;
        }
        free(toDelete);
        if(printDeletion)
            printf("Deleted Billionaire %s %s\n", name, surname);
    }
}

/**
 * Gets the allocated memory from the linked list.
 * @param bm BillionaireManagement Pointer
 */
void getMemorySizeAllocated(BillionaireManagement *bm) {
    printf("%lu Bytes allocated\n", getLengthOfLinkedList(bm) * sizeof(struct billionaire_t));
}

/**
 * Gets length of linked list.
 * @param bm BillionaireManagement Pointer
 * @return int length
 */
int getLengthOfLinkedList(BillionaireManagement *bm) {
    struct billionaire_t* current = bm->head;
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


/**
 * Gets Input from User, if input is not between min and max user is prompted again, as lang as input is invalid.
 * @param min Minimum Input
 * @param max Maximum Intput
 * @return Int
 */
int getInput(int min, int max) {
    int input = -1;

    do {
        printf("Selection: ");
        scanf("%d", &input);
    } while(input < min || input > max);

    return input;
}

/**
 * Gets input and handles input accordingly.
 * @param bm BillionaireManagement Pointer
 */
void handleInput(BillionaireManagement *bm) {
    int selection = getInput(0, 9);

    switch (selection) {
        case 1:
            printAddBillionaireMenu(bm);
            break;
        case 2:
            printShowBillionairesMenu(bm);
            break;
        case 3:
            printDeleteBillionairesMenu(bm);
            break;
        case 4:
            printSortBillionairesMenu(bm);
            break;
        case 5:
            printSaveInFileMenu(bm);
            break;
        case 6:
            printLoadFromFileMenu(bm);
            break;
        case 7:
            printSearchForBillionairesMenu(bm);
            break;
        case 8:
            getMemorySizeAllocated(bm);
            break;
        case 9:
            printEditBillionairesMenu(bm);
            break;
        case 0:
            handleExit(bm);
        default:
            break;
    }
}

/**
 * Exit Routines
 * Deletes all Billionaires from list and frees the allocated memory, then handles exits.
 * @param bm BillionaireManagement Pointer
 */
void handleExit(BillionaireManagement *bm) {
    deleteAllBillionairesFromLinkedList(bm);
    exit(0);
}

/**
 * Prints greetings message to the screen.
 */
void printGreeting(void) {
    printf("==================================================\n");
    printf("          Welcome Forbes Billionaires List        \n");
    printf("                   Version: 0.0.1                 \n");
}

/**
 * Prints menu to the screen.
 */
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

/**
 * Prints the menu for adding a Billionaire to the linked list. And asks the user for input.
 * @param bm BillionaireManagement Pointer
 */
void printAddBillionaireMenu(BillionaireManagement *bm) {
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

    handleAddBillionaire(name, surname, net_worth, selfmade_score, bm);
}

/**
 * Handles the creation and adding from a billionaire to the linked list, after the add billionaire menu is executed. Later asks the user if he wants to add another billionaire.
 * @param name First Name of Billionaire
 * @param surname Last Name of Billionaire
 * @param net_worth Net-Worth of Billionaire
 * @param selfmade_score Selfmade-Score of Billionaire
 * @param bm BillionaireManagement Pointer
 */
void handleAddBillionaire(char name[], char surname[], float net_worth, int selfmade_score, BillionaireManagement *bm) {
    createBillionaire(name, surname, net_worth, selfmade_score, bm);

    printWhitespaceOnce();
    printf("%s %s was added to the list of Billionaires!\n", name, surname);
    printf("Do you want to add another Billionaire ? y/n: ");

    char selection;
    scanf(" %c", &selection);
    getchar();

    if(selection == 'y'|| selection == 'Y') {
        printWhitespaceOnce();
        printAddBillionaireMenu(bm);
    }

    printWhitespaceOnce();
}

/**
 * Prints all Billionaires in the linked list to the console.
 * @param bm BillionaireManagement Pointer
 */
void printShowBillionairesMenu(BillionaireManagement *bm) {
    printf("==================================================\n");
    printf("                WORLDS BILLIONAIRES               \n");
    printf("==================================================\n");

    printAllBillionares(false, bm);
}

/**
 * Prints the delete Billionaire menu and prompts the user which Billionaire should ne deleted. After that calls the appropretiate function to delete the selected Billionaire.
 * @param bm BillionaireManagement Pointer
 */
void printDeleteBillionairesMenu(BillionaireManagement *bm) {
    printf("==================================================\n");
    printf("                DELETE BILLIONAIRE                \n");
    printf("==================================================\n");

    int number = printAllBillionares(true, bm);
    printWhitespaceOnce();
    if(number != -1) {
        int input = getInput(1, number) - 1;
        deleteBillionaireFromList(input, true, bm);
    }
}

/**
 * Prints the edit Billionaire menu and prompts the user for which property he/she wants to edit. After that calls the appropriate function to edit the supplied property.
 * @param bm BillionaireManagement Pointer
 */
void printEditBillionairesMenu(BillionaireManagement *bm) {
    printf("==================================================\n");
    printf("                 EDIT BILLIONAIRE                 \n");
    printf("==================================================\n");

    int number = printAllBillionares(true, bm);
    printWhitespaceOnce();
    if(number != -1) {
        int index = getInput(1, number) - 1;
        editBillionaireFromList(index, bm);
    }
}

/**
 * Prints the sort Billionaire menu and prompts the user for which property the list should be sorted. After that calls the appropriate function to sort the linked list.
 * @param bm
 */
void printSortBillionairesMenu(BillionaireManagement *bm) {
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

    sortBillionairesByCategory(input, bm);
}

/**
 * Prints the search for Billionaire menu and prompts the user for which property to search for.
 * @param bm BillionaireManagement Pointer
 */
void printSearchForBillionairesMenu(BillionaireManagement *bm) {
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

    for(int i = 0; i < getLengthOfLinkedList(bm); i++) {
        struct billionaire_t* current = getBillionaireByIndex(i, bm);
        if(searchForProperty(input, current, searchString)) {
            printBillionareProperties(current, i+1, false);
            printedOnce = true;
        }
    }

    if(!printedOnce) {
        printf("There are no matching Billionaires!\n");
    }
}

/**
 * Prints the menu for saving the linked list the file. Prompts the user for input and calls the appropriate function for saving the data.
 * @param bm BillionaireManagement Pointer
 */
void printSaveInFileMenu(BillionaireManagement *bm) {
    printf("==================================================\n");
    printf("                SAVE BILLIONAIRES                 \n");
    printf("==================================================\n");
    printf("Which file do you want to save too: ");

    char file_name[128+1];
    scanf("%s", file_name);
    sprintf(file_name, "%s.csv", file_name);
    handleSaveBillionairesToFile(file_name, bm);
    printWhitespace(3);
}

/**
 * Handles the saving from the linked list to file
 * @param file_name File name of the file which linked list should be saved to
 * @param bm BillionaireMangement Pointer
 */
void handleSaveBillionairesToFile(char file_name[], BillionaireManagement *bm) {
    FILE *fileToSaveTo = fopen(file_name, "w");
    if(fileToSaveTo == NULL) {
        printf("Fatal error trying to open file!");
        return;
    }

    struct billionaire_t* current;

    for(int i = 0; i < getLengthOfLinkedList(bm); i++) {
        current = getBillionaireByIndex(i, bm);
        char net_worth[64];
        sprintf(net_worth, "%f", current->net_worth);

        char selfmade_score[8];
        sprintf(selfmade_score, "%d", current->selfmade_score);

        // Saves Billionaire accordingly to csv
        fprintf(fileToSaveTo, "%s;%s;%s;%s\n", current->name, current->surname, net_worth, selfmade_score);
    }

    fclose(fileToSaveTo);
    printWhitespaceOnce();
    printf("Successfully saved to file: %s\n", file_name);
}


/**
 * Gets a field from the supplied line which is in csv format.
 * @param line Line to read data from
 * @param num Index of the field to be loaded
 * @return String
 */
const char* getfield(char* line, int num)
{
    const char* tok;
    for (tok = strtok(line, ";");
         tok && *tok;
         tok = strtok(NULL, ";\n"))
    {
        if (!--num)
            return tok;
    }
    return NULL;
}

/**
 * Delets all Billionaires from the linked list
 * @param bm BillionaireManagement Pointer
 */
void deleteAllBillionairesFromLinkedList(BillionaireManagement *bm) {
    for (int i = getLengthOfLinkedList(bm) - 1; i >= 0; i--) {
        deleteBillionaireFromList(i, false, bm);
    }
}

/**
 * Prints the load billionaires from file menu.
 * @param bm BillionaireManagement Pointer
 */
void printLoadFromFileMenu(BillionaireManagement *bm) {
    printf("==================================================\n");
    printf("                LOAD BILLIONAIRES                 \n");
    printf("==================================================\n");
    printf("From which file do you want to load: ");

    char file_name[128+1];
    scanf("%s", file_name);
    sprintf(file_name, "%s.csv", file_name);
    printWhitespaceOnce();

    loadBillionairesFromFile(file_name, bm);
    printf("Successfully loaded from file: %s\n", file_name);
    printWhitespace(3);
}

/**
 * Loads Billionares from supplied file name and inserts them into the linked list.
 * @param file_name File name from which Billionaires should ne loaded from.
 * @param bm BillionaireManagement Pointer
 */
void loadBillionairesFromFile(char file_name[], BillionaireManagement *bm) {
    FILE *fileToOpen = fopen(file_name, "r");
    if(fileToOpen == NULL) {
        printf("There is no file with name: %s\n", file_name);
        return;
    }

    deleteAllBillionairesFromLinkedList(bm);

    char line[1024];
    while(fgets(line, 1024, fileToOpen)) {
        char* tmp = strdup(line);
        char name[128+1];
        char surname[128+1];
        float net_worth;
        int selfmade_score;

        strcpy(name, getfield(tmp, 1));
        tmp = strdup(line);
        strcpy(surname, getfield(tmp, 2));
        tmp = strdup(line);
        net_worth = atof(getfield(tmp, 3));
        tmp = strdup(line);
        selfmade_score = atoi(getfield(tmp, 4));

        createBillionaire(name, surname, net_worth, selfmade_score, bm);

        free(tmp);
    }

}


/**
 * Search if the supplied searchFor string matches the supplied category from supplied Billionaire.
 * @param property Property to be checked for
 * @param current Billionaire to be checked for
 * @param searchFor String which Billionaire should contain in supplied category
 * @return bool
 */
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

/**
 * Edits the supplied property of the supplied Billionaire.
 * @param index Index of Billionaire to be edited
 * @param bm BillionaireManagement Pointer
 */
void editBillionaireFromList(int index, BillionaireManagement *bm) {
    struct billionaire_t* billionaireToEdit = getBillionaireByIndex(index, bm);
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

/**
 * Sorts the linked list by the supplied category
 * @param category  Category to be checked (1) for Fist Name (2) for Second name (3) for Net-Worth and (4) for Selfmade-Score
 * @param bm BillionaireManagement Pointer
 */
void sortBillionairesByCategory(int category, BillionaireManagement *bm) {
    for(int i = getLengthOfLinkedList(bm); i > 1; i--) {
        for(int n = 0; n < i -1; n++) {
            struct billionaire_t* current = getBillionaireByIndex(n, bm);
            if(!billionaireComesBefore(category, current, current->next)) {
                swapBillionaireWithNextBillionaire(n, bm);
            }
        }
    }
}

/**
 * Checks of the supplied category data from the first Billionare comes before the second.
 * @param category Category to be checked (1) for Fist Name (2) for Second name (3) for Net-Worth and (4) for Selfmade-Score
 * @param first First Billionaire -> to be checked
 * @param second Second Billionaire -> to be compared to
 * @return bool
 */
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

/**
 * Swaps a Billionaire with the one after it
 * @param index Index of Billionaire to be swapped
 * @param bm BillionaireManagement Pointer
 */
void swapBillionaireWithNextBillionaire(int index, BillionaireManagement *bm) {
    // Billionaire to be swapped.
    struct billionaire_t* billionaireToSwap = getBillionaireByIndex(index, bm);
    // Billionare after the element to be swapped. (Will be swapped with the element toswap)
    struct billionaire_t* billionaireAfter = billionaireToSwap->next;

    // If there is no element after the one to be swapped. The element can't be swapped.
    // So we need to check if there is an element, after the eleent to be swapped.
    if(billionaireAfter) {
        // Before [billionaireToSwap] <--> [billionaireAfter]
        // First switch the the elements themselves.
        billionaireToSwap->next = billionaireAfter->next;
        billionaireAfter->prev = billionaireToSwap->prev;
        billionaireAfter->next = billionaireToSwap;
        billionaireToSwap->prev = billionaireAfter;


        // Now [billionaireAfter] <--> [billionaireToSwap]
        // Checks if the next element of toswap exists (previously the next elemtn of after),
        // if so set its prev to swap.
        if(billionaireToSwap->next) billionaireToSwap->next->prev = billionaireToSwap;
        // Checks the previous element of after exists (prevously the prev elemtn of toswap),
        // if so sets its next to after.
        if(billionaireAfter->prev) billionaireAfter->prev->next = billionaireAfter;
        // If the old after element was the tail element, now after the swap the new tail must be toswap.
        if(billionaireAfter == bm->tail) bm->tail = billionaireToSwap;
        // The the old swap element was the head element, now aftehr the swap the new head must be after.
        if(billionaireToSwap == bm->head) bm->head = billionaireAfter;
    }
    // If there is no element after the one we want to swap, we do nothing.
}

int printAllBillionares(bool shortened, BillionaireManagement *bm) {
    struct billionaire_t* current = bm->head;
    printWhitespace(2);

    if(current == NULL) {
        printf("There are no Billionaires in your list!\n");
        printWhitespace(2);
        return -1;
    } else {
        int number = 1;
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