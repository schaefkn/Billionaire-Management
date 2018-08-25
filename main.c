#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"
#include "config.h"

/**
 * Inserts Sample Data into Linked List Management
 * @param llm LinkedListManagement Pointer
 */
void insertSampleData(LinkedListManagement *llm) {
    createBillionaire("Bill", "Gates", 91.7, 8, llm);
    createBillionaire("Berta", "Berta", 200, 10, llm);
    createBillionaire("Warren", "Buffet", 87.5, 8, llm);
    createBillionaire("Jeff", "Bezos", 120.9, 8, llm);
    createBillionaire("Alpha", "Centaury", 13.5, 10, llm);
    createBillionaire("Kevin", "Alpha", 123.8, 10, llm);
}



/**
 * Main method
 */
int main(int argc, const char* argv[]) {
    LinkedListManagement* llm = createLinkedListManagement();

    handleArguments(argc, argv, llm);
    printGreeting();
    while(true) {
        printMenu();
        handleInput(llm);
    }
}

/**
 * Creates a new instance of the Linked List Management
 * @return linked_list_management*
 */
struct linked_list_management* createLinkedListManagement(void) {
    struct linked_list_management* llm = malloc(sizeof(struct linked_list_management));
    llm->head = NULL;
    llm->tail = NULL;
    llm->size = 0;

    return llm;
}

/**
 * Fills a Billionaire struct with supplied data.
 * @param name First Name of Billionaire
 * @param surname Last Name of Billionaire
 * @param net_worth Net-Worth of Billionaire
 * @param selfmade_score Selfmade-Score of Billionaire
 * @return struct billionaire_t*
 */
struct billionaire_t* fillBillionaire(char name[], char surname[], float net_worth, int selfmade_score) {
    struct billionaire_t* tmp = malloc(sizeof(struct billionaire_t));
    strcpy(tmp->name, name);
    strcpy(tmp->surname, surname);
    tmp->net_worth = net_worth;
    tmp->selfmade_score = selfmade_score;

    return tmp;
}

/**
 * Inserts Billionaire into the the structure of Linked List.
 * @billionaire Billionaire to be added to Linked List.
 */
struct linked_item_t* insertBillionaireToNewlyCreatedLinkedItem(struct billionaire_t* billionaire) {
    struct linked_item_t* tmp = malloc(sizeof(struct linked_item_t));
    tmp->data = (int*) billionaire;
    tmp->next = NULL;
    tmp->prev = NULL;

    return tmp;
}

/**
 * Creates a billionaire and adds them to the linked list.
 * @param name First Name of Billionaire
 * @param surname Last Name of Billionaire
 * @param net_worth Net-Worth of Billionaire
 * @param selfmade_score Selfmade-Score of Billionaire
 * @param llm LinkedListManagement Pointer
 */
void createBillionaire(char name[], char surname[], float net_worth, int selfmade_score, LinkedListManagement *llm) {
    struct billionaire_t* tmp = fillBillionaire(name, surname, net_worth, selfmade_score);
    struct linked_item_t* linked_billionaire = insertBillionaireToNewlyCreatedLinkedItem(tmp);

    addItemToLinkedList(linked_billionaire, llm);
}

/**
 * Deletes a Linked List Item from the linked.
 * @param toDelete Linked List Item to be deleted from the linked list.
 * @param llm LinkedListManagement Pointer
 */
bool deleteItemFromLinkedList(struct linked_item_t* toDelete, LinkedListManagement* llm) {
    if(toDelete == NULL) {
        return false;
    } else {
        if(toDelete == llm->head) {
            if(toDelete->next) {
                toDelete->next->prev = NULL;
                llm->head = toDelete->next;
            } else {
                llm->head = NULL;
            }
        } else if (toDelete == llm->tail) {
            toDelete->prev->next = NULL;
            llm->tail = toDelete->prev;
        } else {
            toDelete->prev->next = toDelete->next;
            toDelete->next->prev = toDelete->prev;
        }
        free(toDelete);
        llm->size--;
        return true;
    }
}

/**
 * Deletes a Billionaire from the Linked List by supplied index. If there is no Billionaire at this index, an error is printed.
 * @param index Index of Billionaire to be deleted.
 * @param printDeletion Should the method print deletion to the console.
 * @param llm LinkedListManagement Pointer
 */
void deleteBillionaireFromLinkedList(int index, bool printDeletion, LinkedListManagement* llm) {
    struct linked_item_t* toDelete = getLinkedListItemByIndex(index, llm);
    
    char name[128+1];
    char surname[128+1];

    if(toDelete == NULL) {
        printf("Error, there is no Billionaire with index %d\n", index);
    } else {
        struct billionaire_t* billionaireToDelete = (struct billionaire_t*) toDelete->data;
        
        if(deleteItemFromLinkedList(toDelete, llm)) {
            if(printDeletion) {
                strcpy(name, billionaireToDelete->name);
                strcpy(surname, billionaireToDelete->surname);
                printf("Deleted Billionaire %s %s\n", name, surname);
            }
            free(billionaireToDelete);
        } else {
            printf("Error while trying to delete connected Linked List Item.\n");
            return;
        }
    }
}

/**
 * Deletes all Billionaires from the Linked List.
 * @param llm LinkedListManagement Pointer
 */
void deleteAllBillionairesFromLinkedList(LinkedListManagement* llm) {
    for(int i = llm->size - 1; i >= 0; i--) {
        deleteBillionaireFromLinkedList(i, false, llm);
    }
}

/**
 * Gets input and handles input accordingly.
 * @param llm LinkedListManagement Pointer
 */
void handleInput(LinkedListManagement* llm) {
    int selection = getInput(0, 9);

    switch (selection) {
        case 1:
            printAddBillionaireMenu(llm);
            break;
        case 2:
            printShowBillionairesMenu(llm);
            break;
        case 3:
            printDeleteBillionairesMenu(llm);
            break;
        case 4:
            printSortBillionairesMenu(llm);
            break;
        case 5:
            printSaveInFileMenu(llm);
            break;
        case 6:
            printLoadFromFileMenu(llm);
            break;
        case 7:
            printSearchForBillionairesMenu(llm);
            break;
        case 8:
            handleMemorySizeAllocated(llm);
            break;
        case 9:
            printEditBillionairesMenu(llm);
            break;
        case 0:
            handleExit(llm);
        case 42:
            handleSecretEasterEgg();
        default:
            break;
    }
}

/**
 * Handler for arguments at the start of the program.
 */
void handleArguments(int argc, const char* argv[], LinkedListManagement* llm) {
    if(argc == 2) {
        char file_name[128+1];
        strcpy(file_name, argv[1]);
        loadBillionairesFromFile(file_name, llm);
    } else if(argc > 2) {
        fprintf(stderr, "Usage: %s <file name> (optional)\n", argv[0]);
        exit(1);
    }
}

/**
 * Exit Routine
 * Deletes the complete Linked List and frees the allocated memory, then handles exit.
 * @param llm LinkedListManagement Pointer
 */
void handleExit(LinkedListManagement *llm) {
    deleteAllBillionairesFromLinkedList(llm);
    exit(0);
}

/**
 * Adds a supplied Linked List Item to the Linked List.
 * @param item Linked List Item to be added to linked list.
 * @param llm LinkedListManagement Pointer
 */
void addItemToLinkedList(struct linked_item_t* item, LinkedListManagement *llm) {
    if(item) {
        if(llm->head == NULL)
            llm->head = item;

        if(llm->tail == NULL) {
            llm->tail = item;
        } else {
            llm->tail->next = item;
            item->prev = llm->tail;
            llm->tail = item;
        }

        llm->size++;
    } else {
        return;
    }
}

/**
 * Calculates the allocated Memory Size
 * @param llm LinkedListManagement Pointer
 * @return size_t Size of the allocated memory.
 */
size_t getMemorySizeAllocated(LinkedListManagement* llm) {
     return llm->size * (sizeof(struct billionaire_t) + sizeof(struct linked_item_t)) + sizeof(struct linked_list_management);
}

/**
 * Cleans the stdin from input.
 * @return int length
 */
int clean_stdin() {
    while (getchar() != '\n');
    return 1;
}

/**
 * Gets Input from User, if input is not between min and max user is prompted again, as lang as input is invalid.
 * @param min Minimum Input
 * @param max Maximum Intput
 * @return Int
 */
int getInput(int min, int max) {
    int input = -1;
    char c;

    do {
        printf("Selection: ");
    } while (((scanf("%d%c", &input, &c) !=2 || c!='\n') && clean_stdin()) || ((input < min || input > max) && input != 42));

    return input;
}

/**
 * Prints greetings message to the screen.
 */
void printGreeting(void) {
    printf("==================================================\n");
    printf("          Welcome Forbes Billionaires List        \n");
    printf("                   Version: 1.1.0                 \n");
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
    printLineBreakOnce();
}

/**
 * Prints the menu for adding a Billionaire to the linked list. And asks the user for input.
 * @param llm LinkedListManagement Pointer
 */
void printAddBillionaireMenu(LinkedListManagement* llm) {
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

    handleAddBillionaire(name, surname, net_worth, selfmade_score, llm);
}

/**
 * Handles the output of the memory size allocated
 * 
 */
void handleMemorySizeAllocated(LinkedListManagement* llm) {
    size_t size = getMemorySizeAllocated(llm);
    
    printLineBreakOnce();
    printf("%zu Bytes allocated.\n", size);
    printLineBreakOnce();
}

/**
 * Handles the creation and adding from a billionaire to the linked list, after the add billionaire menu is executed. Later asks the user if he wants to add another billionaire.
 * @param name First Name of Billionaire
 * @param surname Last Name of Billionaire
 * @param net_worth Net-Worth of Billionaire
 * @param selfmade_score Selfmade-Score of Billionaire
 * @param llm LinkedListManagement Pointer
 */
void handleAddBillionaire(char name[], char surname[], float net_worth, int selfmade_score, LinkedListManagement* llm) {
    createBillionaire(name, surname, net_worth, selfmade_score, llm);

    printLineBreakOnce();
    printf("%s %s was added to the list of Billionaires!\n", name, surname);
    printf("Do you want to add another Billionaire ? y/n: ");

    char selection;
    scanf(" %c", &selection);
    getchar();

    if(selection == 'y'|| selection == 'Y') {
        printLineBreakOnce();
        printAddBillionaireMenu(llm);
    }

    printLineBreakOnce();
}

/**
 * Prints all Billionaires in the linked list to the console.
 * @param llm LinkedListManagement Pointer
 */
void printShowBillionairesMenu(LinkedListManagement *llm) {
    printf("==================================================\n");
    printf("                WORLDS BILLIONAIRES               \n");
    printf("==================================================\n");

    printAllBillionaires(false, llm);
}

/**
 * Prints the delete Billionaire menu and prompts the user which Billionaire should ne deleted. After that calls the appropretiate function to delete the selected Billionaire.
 * @param llm LinkedListManagement Pointer
 */
void printDeleteBillionairesMenu(LinkedListManagement* llm) {
    printf("==================================================\n");
    printf("                DELETE BILLIONAIRE                \n");
    printf("==================================================\n");

    int number = printAllBillionaires(true, llm);
    printLineBreakOnce();
    if(number != -1) {
        int input = getInput(1, number) - 1;
        deleteBillionaireFromLinkedList(input, true, llm);
    }
}

/**
 * Prints the edit Billionaire menu and prompts the user for which property he/she wants to edit. After that calls the appropriate function to edit the supplied property.
 * @param llm LinkedListManagement Pointer
 */
void printEditBillionairesMenu(LinkedListManagement* llm) {
    printf("==================================================\n");
    printf("                 EDIT BILLIONAIRE                 \n");
    printf("==================================================\n");

    int number = printAllBillionaires(true, llm);
    printLineBreakOnce();
    if(number != -1) {
        int index = getInput(1, number) - 1;
        editBillionaireFromList(index, llm);
    }
}

/**
 * Prints the sort Billionaire menu and prompts the user for which property the list should be sorted. After that calls the appropriate function to sort the linked list.
 * @param llm
 */
void printSortBillionairesMenu(LinkedListManagement* llm) {
    printf("==================================================\n");
    printf("                 SORT BILLIONAIRE                 \n");
    printf("==================================================\n");
    printf("On which property do you want to sort ?\n");
    printf("(1) First Name\n");
    printf("(2) Last Name\n");
    printf("(3) Net-Worth\n");
    printf("(4) Selfmade-Score\n");

    printLineBreakOnce();
    int input = getInput(1, 4);

    sortBillionairesByCategory(input, llm);
}

/**
 * Prints the search for Billionaire menu and prompts the user for which property to search for.
 * @param llm LinkedListManagement Pointer
 */
void printSearchForBillionairesMenu(LinkedListManagement* llm) {
    printf("==================================================\n");
    printf("                SEARCH BILLIONAIRE                \n");
    printf("==================================================\n");
    printf("On which property do you want to search ?\n");
    printf("(1) First Name\n");
    printf("(2) Last Name\n");
    printf("(3) Net-Worth\n");
    printf("(4) Selfmade-Score\n");

    printLineBreakOnce();
    int input = getInput(1, 4);

    char searchString[128+1];
    printf("Search For: ");
    scanf("%s", searchString);

    printLineBreak(2);

    bool printedOnce = false;

    for(int i = 0; i < llm->size ; i++) {
        struct linked_item_t* itemToEdit = getLinkedListItemByIndex(i, llm);
        struct billionaire_t* current = (struct billionaire_t*) itemToEdit->data;
        if(searchForProperty(input, current, searchString)) {
            printBillionaireProperties(current, i+1, false);
            printedOnce = true;
        }
    }

    if(!printedOnce) {
        printf("There are no matching Billionaires!\n");
    }
}

/**
 * Prints the menu for saving the linked list the file. Prompts the user for input and calls the appropriate function for saving the data.
 * @param llm LinkedListManagement Pointer
 */
void printSaveInFileMenu(LinkedListManagement* llm) {
    printf("==================================================\n");
    printf("                SAVE BILLIONAIRES                 \n");
    printf("==================================================\n");
    printf("Which file do you want to save too: ");

    char file_name[128+1];
    scanf("%s", file_name);
    sprintf(file_name, "%s.csv", file_name);
    handleSaveBillionairesToFile(file_name, llm);
    printLineBreak(3);
}

/**
 * Prints the load billionaires from file menu.
 * @param llm LinkedListManagement Pointer
 */
void printLoadFromFileMenu(LinkedListManagement* llm) {
    printf("==================================================\n");
    printf("                LOAD BILLIONAIRES                 \n");
    printf("==================================================\n");
    printf("From which file do you want to load: ");

    char file_name[128+1];
    scanf("%s", file_name);
    sprintf(file_name, "%s.csv", file_name);
    printLineBreakOnce();

    if(loadBillionairesFromFile(file_name, llm)) {
        printf("Successfully loaded from file: %s\n", file_name);
    }
    printLineBreak(3);
}

/**
 * Loads Billionares from supplied file name, deletes the linked list and inserts them into the new linked list.
 * @param file_name File name from which Billionaires should ne loaded from.
 * @param llm LinkedListManagement Pointer
 */
bool loadBillionairesFromFile(char file_name[], LinkedListManagement* llm) {
    FILE *fileToOpen = fopen(file_name, "r");
    if(fileToOpen == NULL) {
        printf("There is no file with name: %s\n", file_name);
        return false;
    }

    deleteAllBillionairesFromLinkedList(llm);

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

        createBillionaire(name, surname, net_worth, selfmade_score, llm);

        free(tmp);
    }

    return true;
}

/**
 * Handles the saving from the linked list to file
 * @param file_name File name of the file which linked list should be saved to
 * @param llm LinkedListManagement Pointer
 */
void handleSaveBillionairesToFile(char file_name[], LinkedListManagement* llm) {
    FILE *fileToSaveTo = fopen(file_name, "w");
    if(fileToSaveTo == NULL) {
        printf("Fatal error trying to open file!");
        return;
    }

    struct linked_item_t* item;
    struct billionaire_t* current;

    for(int i = 0; i < llm->size; i++) {
        item = getLinkedListItemByIndex(i, llm);
        current = (struct billionaire_t*) item->data;
        char net_worth[64];
        sprintf(net_worth, "%f", current->net_worth);

        char selfmade_score[8];
        sprintf(selfmade_score, "%d", current->selfmade_score);

        // Saves Billionaire accordingly to csv
        fprintf(fileToSaveTo, "%s;%s;%s;%s\n", current->name, current->surname, net_worth, selfmade_score);
    }

    fclose(fileToSaveTo);
    printLineBreakOnce();
    printf("Successfully saved to file: %s\n", file_name);
}

/**
 * Edits the supplied property of the supplied Billionaire.
 * @param index Index of Billionaire to be edited
 * @param llm LinkedListManagement Pointer
 */
void editBillionaireFromList(int index, LinkedListManagement* llm) {
    struct linked_item_t* itemToEdit = getLinkedListItemByIndex(index, llm);
    struct billionaire_t* billionaireToEdit = (struct billionaire_t*) itemToEdit->data;
    printBillionaireProperties(billionaireToEdit, 0, false);
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
            printf("New Net-Worth: ");
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
 * Gets Linked List Item by supplied index. If index is greater than the lenght of the list, NULL will be returned.
 * @param index Index for Linked List Item
 * @param llm LinkedListManagement Pointer
 * @return struct linked_item_t*
 */
struct linked_item_t* getLinkedListItemByIndex(int index, LinkedListManagement *llm) {
    if(index == 0) {
        return llm->head;
    } else if (index > llm->size) {
        return NULL;
    } else if (index == llm->size) {
        return llm->tail;
    } else {
        int i = 0;
        struct linked_item_t* itemToReturn = llm->head;

        while(i < index) {
            if(itemToReturn->next) {
                i++;
                itemToReturn = itemToReturn->next;
            } else {
                return NULL;
            }
        }

        return itemToReturn;
    }
}

/**
 * Sorts the linked list by the supplied category by using bubble sort.
 * @param category  Category to be checked (1) for Fist Name (2) for Second name (3) for Net-Worth and (4) for Selfmade-Score
 * @param llm LinkedListManagement Pointer
 */
void sortBillionairesByCategory(int category, LinkedListManagement* llm) {
    for(int i = llm->size; i > 1; i--) {
        struct linked_item_t* current = llm->head;
        while(current->next) {
            struct billionaire_t* currentBillionaire = (struct billionaire_t*) current->data;
            struct billionaire_t* nextBillionaire = (struct billionaire_t*) current->next->data;

            if(!billionareComesBefore(category, currentBillionaire, nextBillionaire)) {
                swapLinkedListItemWithSuccessor(current);
            }

            current = current->next;
        }
    }
}

/**
 * Search if the supplied searchFor String matches the supplied category from supplied Billionaire.
 * @param property Property to be checked for
 * @param curernt Billionaire to be checked for
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
            return strstr(current->name, searchFor) ? true : false;
        case 2:
            return strstr(current->surname, searchFor) ? true : false;
        case 3:
            return strcmp(net_worth, searchFor) == 0 ? true : false;
        case 4:
            return strcmp(selfmade_score, searchFor) == 0 ? true : false;
        default:
            return false;
    }
}

/**
 * Checks of the supplied category data from the first Billionare comes before the second.
 * @param category Category to be checked (1) for Fist Name, (2) for Second name, (3) for Net-Worth and (4) for Selfmade-Score
 * @param first First Billionaire -> to be checked
 * @param second Second Billionaire -> to be compared to
 * @return bool
 */
bool billionareComesBefore(int category, struct billionaire_t* first, struct billionaire_t* second) {
    if(first == NULL || second == NULL)
        return false;

    switch(category) {
        case 1:
            return strcmp(first->name, second->name) < 0;
        case 2:
            return strcmp(first->surname, second->surname) < 0;
        case 3:
            return first->net_worth >= second->net_worth;
        case 4:
            return first->selfmade_score >= second->selfmade_score;
        default:
            return false;
    }
}

/**
 * Swaps a Linked List Item with the one after it.
 * This is achieved by simply switching the associated data from the items with oneanother.
 * @param index Index of Billionaire to be swapped
 * @param llm BillionaireManagement Pointer
 */
int swapLinkedListItemWithSuccessor(struct linked_item_t* itemToSwap) {
    if(itemToSwap->next) {
        int* tmp = itemToSwap->data;

        itemToSwap->data = itemToSwap->next->data;
        itemToSwap->next->data = tmp;

        return 0;
    }
    return -1;
}

/**
 * Brints all Billionaires to the console.
 * @param shortened Should the ouput the shortened
 * @param llm LinkedListManagement Pointer
 * @return
 */
int printAllBillionaires(bool shortened, LinkedListManagement *llm) {
    struct linked_item_t* current = llm->head;

    if(current == NULL) {
        printf("There are no Billionaires in your list!\n");
        printLineBreak(2);
        return -1;
    } else {
        int number = 1;
        struct billionaire_t* billionaireToPrint = (struct billionaire_t*) current->data;
        printBillionaireProperties(billionaireToPrint, number, shortened);
        while(current->next) {
            number++;
            current = current->next;
            billionaireToPrint = (struct billionaire_t*) current->data;
            printBillionaireProperties(billionaireToPrint, number, shortened);
        }
        printLineBreakOnce();
        return number;
    }
}

/**
 * Prints the properties of one Billionaire
 * @param billionaire Billionaire to print properties from
 * @param number Number of the Billionaire in the list
 * @param shortened Should the ouput be shortened
 */
void printBillionaireProperties(struct billionaire_t* billionaire, int number, bool shortened) {
    if(shortened) {
        printf("Billionaire (%d): %s %s\n", number, billionaire->name, billionaire->surname);
    } else {
        printf("================= Billionaire %d =================\n", number);
        printf("First Name: %s\n", billionaire->name);
        printf("Last Name: %s\n", billionaire->surname);
        printf("Net-Worth: $%0.2f Billion Dollars.\n", billionaire->net_worth);
        printf("Selfmade-Score: %d\n", billionaire->selfmade_score);
        printLineBreakOnce();
    }
}

/**
 * Gets a field from the supplied line which is in csv format.
 * @param line Line to read data from
 * @param num Index of the field to be loaded
 * @return String
 */
const char* getfield(char* line, int num) {
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
 * Prints linebreak once
 */
void printLineBreakOnce(void) {
    printf("\n");
}

/**
 * Prints linebreak multiple times
 * @param times How often should a linebreak be printed
 */
void printLineBreak(int times) {
    for (int i = 0; i < times; ++i) {
        printf("\n");
    }
}

/**
 * Handles Secret Easter Egg.
 */
void handleSecretEasterEgg(void) {
    printLineBreak(6);

    printf("                                .do-\"\"\"\"\"'-o..                         \n"
                   "                             .o\"\"            \"\"..                       \n"
                   "                           ,,''                 ``b.                   \n"
                   "                          d'                      ``b                   \n"
                   "                         d`d:                       `b.                 \n"
                   "                        ,,dP                         `Y.               \n"
                   "                       d`88                           `8.               \n"
                   " ooooooooooooooooood888`88'                            `88888888888bo, \n"
                   "d\"\"\"    `\"\"\"\"\"\"\"\"\"\"\"\"Y:d8P                              8,          `b \n"
                   "8                    P,88b                             ,`8           8 \n"
                   "8                   ::d888,                           ,8:8.          8 \n"
                   ":                   dY88888                           `' ::          8 \n"
                   ":                   8:8888                               `b          8 \n"
                   ":                   Pd88P',...                     ,d888o.8          8 \n"
                   ":                   :88'dd888888o.                d8888`88:          8 \n"
                   ":                  ,:Y:d8888888888b             ,d88888:88:          8 \n"
                   ":                  :::b88d888888888b.          ,d888888bY8b          8 \n"
                   "                    b:P8;888888888888.        ,88888888888P          8 \n"
                   "                    8:b88888888888888:        888888888888'          8 \n"
                   "                    8:8.8888888888888:        Y8888888888P           8 \n"
                   ",                   YP88d8888888888P'          \"\"888888\"Y            8 \n"
                   ":                   :bY8888P\"\"\"\"\"''                     :            8 \n"
                   ":                    8'8888'                            d            8 \n"
                   ":                    :bY888,                           ,P            8 \n"
                   ":                     Y,8888           d.  ,-         ,8'            8 \n"
                   ":                     `8)888:           '            ,P'             8 \n"
                   ":                      `88888.          ,...        ,P               8 \n"
                   ":                       `Y8888,       ,888888o     ,P                8 \n"
                   ":                         Y888b      ,88888888    ,P'                8 \n"
                   ":                          `888b    ,888888888   ,,'                 8 \n"
                   ":                           `Y88b  dPY888888OP   :'                  8 \n"
                   ":                             :88.,'.   `' `8P-\"b.                   8 \n"
                   ":.                             )8P,   ,b '  -   ``b                  8 \n"
                   "::                            :':   d,'d`b, .  - ,db                 8 \n"
                   "::                            `b. dP' d8':      d88'                 8 \n"
                   "::                             '8P\" d8P' 8 -  d88P'                  8 \n"
                   "::                            d,' ,d8'  ''  dd88'                    8 \n"
                   "::                           d'   8P'  d' dd88'8                     8 \n"
                   " :                          ,:   `'   d:ddO8P' `b.                   8 \n"
                   " :                  ,dooood88: ,    ,d8888\"\"    ```b.                8 \n"
                   " :               .o8\"'\"\"\"\"\"\"Y8.b    8 `\"''    .o'  `\"\"\"ob.           8 \n"
                   " :              dP'         `8:     K       dP''        \"`Yo.        8 \n"
                   " :             dP            88     8b.   ,d'              ``b       8 \n"
                   " :             8.            8P     8\"\"'  `\"                 :.      8 \n"
                   " :            :8:           :8'    ,:                        ::      8 \n"
                   " :            :8:           d:    d'                         ::      8 \n"
                   " :            :8:          dP   ,,'                          ::      8 \n"
                   " :            `8:     :b  dP   ,,                            ::      8 \n"
                   " :            ,8b     :8 dP   ,,                             d       8 \n"
                   " :            :8P     :8dP    d'                       d     8       8 \n"
                   " :            :8:     d8P    d'                      d88    :P       8 \n"
                   " :            d8'    ,88'   ,P                     ,d888    d'       8 \n"
                   " :            88     dP'   ,P                      d8888b   8        8 \n"
                   " '           ,8:   ,dP'    8.                     d8''88'  :8        8 \n"
                   "             :8   d8P'    d88b                   d\"'  88   :8        8 \n"
                   "             d: ,d8P'    ,8P\"\"\".                      88   :P        8 \n"
                   "             8 ,88P'     d'                           88   ::        8 \n"
                   "            ,8 d8P       8                            88   ::        8 \n"
                   "            d: 8P       ,:  -hrr-                    :88   ::        8 \n"
                   "            8',8:,d     d'                           :8:   ::        8 \n"
                   "           ,8,8P'8'    ,8                            :8'   ::        8 \n"
                   "           :8`' d'     d'                            :8    ::        8 \n"
                   "           `8  ,P     :8                             :8:   ::        8 \n"
                   "            8, `      d8.                            :8:   8:        8 \n"
                   "            :8       d88:                            d8:   8         8 \n"
                   " ,          `8,     d8888                            88b   8         8 \n"
                   " :           88   ,d::888                            888   Y:        8 \n"
                   " :           YK,oo8P :888                            888.  `b        8 \n"
                   " :           `8888P  :888:                          ,888:   Y,       8 \n"
                   " :            ``'\"   `888b                          :888:   `b       8 \n"
                   " :                    8888                           888:    ::      8 \n"
                   " :                    8888:                          888b     Y.     8, \n"
                   " :                    8888b                          :888     `b     8: \n"
                   " :                    88888.                         `888,     Y     8: \n"
                   " ``ob...............--\"\"\"\"\"'----------------------`\"\"\"\"\"\"\"\"'\"\"\"`'\"\"\"\"\"\n");

    printLineBreak(6);
}