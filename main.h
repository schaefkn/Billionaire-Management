typedef enum {false, true} bool;

struct billionaire_t {
    char name[128+1];
    char surname[128+1];
    float net_worth;
    int selfmade_score;
};

struct linked_item_t {
    int* data;

    struct linked_item_t* next;
    struct linked_item_t* prev;
};

typedef struct linked_list_management {
    size_t size;

    struct linked_item_t* head;
    struct linked_item_t* tail;
} LinkedListManagement;


size_t getMemorySizeAllocated(LinkedListManagement *llm);
struct linked_list_management* createLinkedListManagement(void);

struct linked_item_t* insertBillionaireToNewlyCreatedLinkedItem(struct billionaire_t* billionaire);
struct linked_item_t* getLinkedListItemByIndex(int index, LinkedListManagement *llm);
struct billionaire_t* fillBillionaire(char name[], char surname[], float net_worth, int selfmade_score);
void addItemToLinkedList(struct linked_item_t* item, LinkedListManagement *llm);
bool deleteItemFromLinkedList(struct linked_item_t* toDelete, LinkedListManagement* llm);
int swapLinkedListItemWithSuccessor(struct linked_item_t* itemToSwap);

void createBillionaire(char name[], char surname[], float net_worth, int selfmade_score, LinkedListManagement *llm);
void sortBillionairesByCategory(int category, LinkedListManagement* llm);
void editBillionaireFromList(int index, LinkedListManagement* llm);
bool loadBillionairesFromFile(char file_name[], LinkedListManagement* llm);
bool searchForProperty(int property, struct billionaire_t* current, char searchFor[]);
bool billionareComesBefore(int category, struct billionaire_t* first, struct billionaire_t* second);

void printGreeting(void);
void printMenu(void);
void printBillionaireProperties(struct billionaire_t* billionaire, int number, bool shortened);
void printAddBillionaireMenu(LinkedListManagement* llm);
void printShowBillionairesMenu(LinkedListManagement *llm);
void printDeleteBillionairesMenu(LinkedListManagement* llm);
void printEditBillionairesMenu(LinkedListManagement* llm);
void printSortBillionairesMenu(LinkedListManagement* llm);
void printLoadFromFileMenu(LinkedListManagement* llm);
void printSaveInFileMenu(LinkedListManagement* llm);
void printSearchForBillionairesMenu(LinkedListManagement* llm);
void printLineBreakOnce(void);
void printLineBreak(int times);
int printAllBillionaires(bool shortened, LinkedListManagement *llm);

void handleInput(LinkedListManagement* llm);
void handleMemorySizeAllocated(LinkedListManagement* llm);
void handleAddBillionaire(char name[], char surname[], float net_worth, int selfmade_score, LinkedListManagement* llm);
void handleSaveBillionairesToFile(char file_name[], LinkedListManagement* llm);
void handleExit(LinkedListManagement *llm);
void handleSecretEasterEgg(void);
void handleArguments(int argc, const char* argv[], LinkedListManagement* llm);

const char* getfield(char* line, int num);
int getInput(int min, int max);

