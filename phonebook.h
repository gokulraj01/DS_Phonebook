#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define ARR_LEN 256                         //  Fixed Length for Arrays 
#define CONTACT_DELIMITER '\n'              //  Delemiter to split between contacts
#define ITEM_DELIMITER '\t'                 //  Delimiter to split items within a contact
#define PHONEBOOK_NAME "phonebook.txt"      //  Location of Phonebook File
#define CREDITS "screens/credits.txt"       //  Location of Credit Screen
#define CREDIT_DURATION 1                   //  Duration of Credit Splash Screen
#define clrscr() printf("\e[1;1H\e[2J")     //  Location of Menu Screen
#define MENU "screens/menu.txt"

// Structure to hold contact data
struct Contact{
    // Contact Name
    char name[ARR_LEN];
    // Phone Number
    char phone[20];
    // Email ID
    char email[ARR_LEN];
};

// Structure to hold nodes for a doubly linked list
struct Node{
    // Pointer to a Contact Data Structure
    struct Contact* data;
    // Pointer to next node. NULL if end.
    struct Node *next;
    // Pointer to previous node. NULL if beginning.
    struct Node *prev;
};

// Global variable to hold HEAD of parsed ContactList
struct Node* CONTACT_LIST = NULL;
// Global variable to hold END of ContactList for easy concat
struct Node* CONTACT_LIST_END = NULL;


/** Function to query a string from user
 * @param msg Prompt message to display before query
 * @return Pointer to array holding recieved string
 */
char* input(char* msg){
    printf("%s: ", msg);
    char* op = malloc(ARR_LEN);
    op[0] = '\n';
    // fix blank input issue
    while(op[0] == '\n')
        fgets(op, ARR_LEN, stdin);
    unsigned int len = 0;
    // remove trailing new line charecter
    while(op[++len] != '\0');
    op[len-1] = '\0';
    return op;
}

/** Dumps passed ContactList data formatted as a table to console.
 * @param list HEAD of linked list holding ContactList
 */
void displayAllContacts(struct Node* list){
    struct Node* current = list;
    int iter = 0;
    printf("Name\t\tPhone\t\tEmail\n");
    while(current != NULL){
        printf("%s\t%s\t%s\n", current->data->name, current->data->phone, current->data->email);
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
void addContact(char* name, char* phone, char* email){
    struct Node* newNode = malloc(sizeof(struct Node));
    struct Contact* newContact = malloc(sizeof(struct Contact));
    strcpy(newContact->name, name);
    strcpy(newContact->phone, phone);
    strcpy(newContact->email, email);
    newNode->data = newContact;
    // if empty list, add as 1st node
    if(CONTACT_LIST_END == NULL)
        CONTACT_LIST = newNode;
    // else link to previous node
    else
        CONTACT_LIST_END->next = newNode;
    // add reverse link
    newNode->prev = CONTACT_LIST_END;
    newNode->next = NULL;

    CONTACT_LIST_END = newNode;
}

/** Parser to import formatted (CSV/TSV) PhoneBook files to memory as ContactList
 * @param filename Path to Phonebook file
 */
void parsePhonebook(char* filename){
    CONTACT_LIST = NULL;
    FILE* pb = fopen(filename, "r");
    char buff[3][ARR_LEN];
    int buffInd = 0, buffPos = 0;
    while(!feof(pb)){
        char c = fgetc(pb);
        if(c != CONTACT_DELIMITER){
            if(c != ITEM_DELIMITER)
                buff[buffPos][buffInd++] = c;
            else{
                buff[buffPos][buffInd] = '\0';
                buffInd = 0;
                buffPos++;
            }
        }
        else{
            buff[buffPos][buffInd] = '\0';
            buffPos = 0; buffInd = 0;
            addContact(buff[0],buff[1],buff[2]);
        }
    }
    fclose(pb);
}

/** Internal method to display a file content as is to console
 * @param filename Path to file to be displayed
 */
void printFile(char* filename){
    FILE* f = fopen(filename, "r");
    if(f == NULL){
        printf("Internal Error: Unable to open Screen File\n");
        return;
    }
    while(!feof(f))
        fputc(fgetc(f), stdout);
    fclose(f);
}

// Displays credits splash screen
void showCredits(){
    clrscr();
    printFile(CREDITS);
    sleep(CREDIT_DURATION);
    clrscr();
}

void writePhonebook(){
    // TODO: write out phonebook data from memory to file (filename is value of PHONEBOOK_NAME)
    // Pending - Greeshma
    printf("Phonebook saved to %s", PHONEBOOK_NAME);
}

// Writes ContactList to PhoneBook file and exits.
void userExit(){
    clrscr();
    printf("Exitting Phonebook.....\n");
    writePhonebook();
    return;
}

// Waits for user interaction before continuing
void waitKey(){
    printf("Enter 'M' for Menu.....");
    char c = '\n';
    while(c == '\n'){
        scanf("%c", &c);
        if(c == 'M'){
            clrscr();
            return;
        }
    }
}

// Takes user input to create a new contact.
// Implements addContact()
void userAddContact(){
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

void userDeleteContact(){
    // TODO: implement Delete Contact for Menu option 2
    // Pending - Gokul PS
}

void userModifyContact(){
    // TODO: implement contact modification menu for Menu option 3
    // Pending - Gokul PS
}

void userSortContact(){
    // TODO: implement Sort functionality for Menu option 4
    // Pending - Gokul Raj
}

void userSearchContact(){
    // TODO: implement Search functionality
    // Pending - George
}

// Displays a Interactive Menu to interface with PhoneBook functions
void showMenu(){
    parsePhonebook(PHONEBOOK_NAME);
    while(1){
        printFile(MENU);
        char choice = -1;
        while(choice == -1){
            scanf("%c", &choice);
            switch(choice){
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
                    displayAllContacts(CONTACT_LIST);
                    break;
                case 'E':
                    userExit();
                    return;
                default:
                    if(choice != '\n')
                        printf("Invalid Choice. Please Retry!\nChoice: ");
                    choice = -1;
            }
        }
        choice = -1;
        waitKey();
    }
}