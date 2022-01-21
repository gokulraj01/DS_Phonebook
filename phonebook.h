#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define ARR_LEN 256            //  Fixed Length for Arrays
#define CONTACT_DELIMITER '\n' //  Delemiter to split between contacts
#define ITEM_DELIMITER '\t'    //  Delimiter to split items within a contact
#define PHONEBOOK_NAME "phonebook.txt"  //  Location of Phonebook File
#define CREDITS "screens/credits.txt"   //  Location of Credit Screen
#define CREDIT_DURATION 1               //  Duration of Credit Splash Screen
#define clrscr() printf("\e[1;1H\e[2J") //  Macro Function to Clear Screen
#define MENU "screens/menu.txt"         //  Location of Menu Screen

// Structure to hold contact data
struct Contact {
    // Contact Name
    char name[ARR_LEN];
    // Phone Number
    char phone[20];
    // Email ID
    char email[ARR_LEN];
};

// Structure to hold nodes for a doubly linked list
struct Node {
    // Pointer to a Contact Data Structure
    struct Contact *data;
    // Pointer to next node. NULL if end.
    struct Node *next;
    // Pointer to previous node. NULL if beginning.
    struct Node *prev;
};

// Global variable to hold HEAD of parsed ContactList
struct Node *contactList = NULL;
// Global variable to hold END of ContactList for easy concat
struct Node *contactListEnd = NULL;

/** Function to query a string from user
 * @param msg Prompt message to display before query
 * @return Pointer to array holding recieved string
 */
char *input(char *msg) {
    printf("%s: ", msg);
    char *op = malloc(ARR_LEN);
    op[0] = '\n';
    // fix blank input issue
    while (op[0] == '\n')
        fgets(op, ARR_LEN, stdin);
    unsigned int len = 0;
    // remove trailing new line charecter
    while (op[++len] != '\0')
        ;
    op[len - 1] = '\0';
    return op;
}

/** Dumps passed ContactList data formatted as a table to console.
 * @param list HEAD of linked list holding ContactList
 */
void displayAllContacts(struct Node *list) {
    clrscr();
    struct Node *current = list;
    int iter = 0;
    printf("   Name\t\t|\t   Phone\t|\t   Email\n");
    printf("   ----\t\t|\t   -----\t|\t   -----\n");
    while (current != NULL) {
        printf("%s\t|\t%s\t|\t%s\n", current->data->name, current->data->phone,
               current->data->email);
        current = current->next;
        iter++;
    }
    printf("\n");
}

/** Adds new contact to ContactList
 * @param name Name for new contact
 * @param phone Phone Number for new contact
 * @param email Email ID for new contact
 */
void addContact(char *name, char *phone, char *email) {
    struct Node *newNode = malloc(sizeof(struct Node));
    struct Contact *newContact = malloc(sizeof(struct Contact));
    strcpy(newContact->name, name);
    strcpy(newContact->phone, phone);
    strcpy(newContact->email, email);
    newNode->data = newContact;
    // if empty list, add as 1st node
    if (contactListEnd == NULL)
        contactList = newNode;
    // else link to previous node
    else
        contactListEnd->next = newNode;
    // add reverse link
    newNode->prev = contactListEnd;
    newNode->next = NULL;

    contactListEnd = newNode;
}

void deleteContact(struct Node *node) {
    if (node->prev == NULL) { // node is at beginning
        node->next->prev = NULL;
        contactList = node->next;
    } else if (node->next == NULL) { // node is at end
        node->prev->next = NULL;
        contactListEnd = node->prev;
    } else {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }
}

struct Node *searchContact() {
    clrscr();
    int choice;
    printf("Search Modes\n"
           "[1] By Name\t[2] By PhoneNo\t[3] By Email\n"
           "Enter your choice: ");
    scanf("%d", &choice);
    char *key;
    struct Node *result;
    switch (choice) {
    case 1:
        key = input("Enter Name to search: ");
        for(result=contactList; (strcmp(result->data->name, key) != 0 && result != NULL); result=result->next);
        break;
    case 2:
        key = input("Enter PhoneNo to search: ");
        for(result=contactList; strcmp(result->data->phone, key) != 0 && result != NULL; result=result->next);
        break;
    case 3:
        key = input("Enter Email to search: ");
        for(result=contactList; strcmp(result->data->email, key) != 0 && result != NULL; result=result->next);
        break;
    default:
        result = NULL;
    }
    return result;
}

/** Parser to import formatted (CSV/TSV) PhoneBook files to memory as
 * ContactList
 * @param filename Path to Phonebook file
 */
void parsePhonebook(char *filename) {
    contactList = NULL;
    FILE *pb = fopen(filename, "r");
    char buff[3][ARR_LEN];
    int buffInd = 0, buffPos = 0;
    while (!feof(pb)) {
        char c = fgetc(pb);
        if (c != CONTACT_DELIMITER) {
            if (c != ITEM_DELIMITER)
                buff[buffPos][buffInd++] = c;
            else {
                buff[buffPos][buffInd] = '\0';
                buffInd = 0;
                buffPos++;
            }
        } else {
            buff[buffPos][buffInd] = '\0';
            buffPos = 0;
            buffInd = 0;
            addContact(buff[0], buff[1], buff[2]);
        }
    }
    fclose(pb);
}

/** Internal method to display a file content as is to console
 * @param filename Path to file to be displayed
 */
void printFile(char *filename) {
    FILE *f = fopen(filename, "r");
    if (f == NULL) {
        printf("Internal Error: Unable to open Screen File\n");
        return;
    }
    while (!feof(f))
        fputc(fgetc(f), stdout);
    fclose(f);
}

// Displays credits splash screen
void showCredits() {
    clrscr();
    printFile(CREDITS);
    sleep(CREDIT_DURATION);
    clrscr();
}

/** Writes ContactList to a formatted (CSV/TSV) PhoneBook file.
 * This function OVERWRITES the specified PhoneBook file.
 * @param filename Phonebook file to write into
 */
void writePhonebook(char *filename) {
    FILE *pb = fopen(filename, "w");
    for(struct Node *p = contactList; p != NULL; p = p->next){
        fprintf(pb, "%s%c%s%c%s%c", p->data->name, ITEM_DELIMITER, p->data->phone, ITEM_DELIMITER, p->data->email, CONTACT_DELIMITER);
    }
    fclose(pb);
    printf("Phonebook saved to %s", filename);
}

// Writes ContactList to PhoneBook file and exits.
void userExit() {
    clrscr();
    printf("Exitting Phonebook.....\n");
    // writePhonebook(PHONEBOOK_NAME);
    return;
}

// Waits for user interaction before continuing
void waitKey() {
    printf("Enter 'M' for Menu.....");
    char c = '\n';
    while (c == '\n') {
        scanf("%c", &c);
        if (c == 'M') {
            clrscr();
            return;
        }
    }
}

// Takes user input to create a new contact.
// Implements addContact()
void userAddContact() {
    clrscr();
    char *name, *phone, *email;
    printf("Enter details for new contact\n");
    printf("-----------------------------\n");
    name = input("Name");
    phone = input("Phone");
    email = input("Email");
    addContact(name, phone, email);
    printf("Contact added successfully....\n");
}

void userDeleteContact() {
    struct Node *namesrch;
    namesrch = searchContact();
    if (namesrch == NULL) {
        printf("No results..");
        return;
    }
    deleteContact(namesrch);
    printf("Contact deleted successfully....\n");
}

void userModifyContact() {
    // TODO: implement contact modification menu
    // Pending - Gokul PS
}

// Performs an in-place sort by Contact Name on ContactList
void userSortContact() {
    // Implements Selection Sort within Linked List
    for (struct Node *i = contactList; i->next != NULL; i = i->next) {
        struct Node *min = i;
        for (struct Node *j = i->next; j != NULL; j = j->next) {
            if (strcmp(min->data->name, j->data->name) > 0)
                min = j;
        }
        struct Contact *t = i->data;
        i->data = min->data;
        min->data = t;
    }
    printf("Sort Done...\n");
}

void userSearchContact() {
    int exit_choice;
    do {
        struct Node *result;
        result = searchContact();
        if (result == NULL)
            printf("No results..");
        else {
            printf("Result\n");
            printf("Name: %s\n", result->data->name);
            printf("Phone number: %s\n", result->data->phone);
            printf("Email: %s\n", result->data->email);
        }
        printf(
            "[1] Continue Search\t[0] Exit\n");
        printf("Choice: ");
        scanf("%d", &exit_choice);
    } while (exit_choice);
}

// Displays a Interactive Menu to interface with PhoneBook functions
void showMenu() {
    parsePhonebook(PHONEBOOK_NAME);
    while (1) {
        printFile(MENU);
        char choice = -1;
        while (choice == -1) {
            scanf("%c", &choice);
            switch (choice) {
            case 'A':
                userAddContact();
                break;
            case 'D':
                userDeleteContact();
                break;
            case 'M':
                userModifyContact();
                break;
            case 'S':
                userSortContact();
                break;
            case 'Q':
                userSearchContact();
                break;
            case 'L':
                displayAllContacts(contactList);
                break;
            case 'E':
                userExit();
                return;
            default:
                if (choice != '\n')
                    printf("Invalid Choice. Please Retry!\nChoice: ");
                choice = -1;
            }
        }
        choice = -1;
        waitKey();
    }
}
