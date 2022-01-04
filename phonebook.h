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
#define clrscr() printf("\e[1;1H\e[2J")     //  Macro Function to Clear Screen
#define MENU "screens/menu.txt"             //  Location of Menu Screen

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
struct Node* contactList = NULL;
// Global variable to hold END of ContactList for easy concat
struct Node* contactListEnd = NULL;


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
    printf("Name\t\t\tPhone\t\tEmail\n");
    while(current != NULL){
        printf("%s\t\t%s\t%s\n", current->data->name, current->data->phone, current->data->email);
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
    if(contactListEnd == NULL)
        contactList = newNode;
    // else link to previous node
    else
        contactListEnd->next = newNode;
    // add reverse link
    newNode->prev = contactListEnd;
    newNode->next = NULL;

    contactListEnd = newNode;
}

/** Parser to import formatted (CSV/TSV) PhoneBook files to memory as ContactList
 * @param filename Path to Phonebook file
 */
void parsePhonebook(char* filename){
    contactList = NULL;
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
    // TODO: implement Delete Contact
    // Pending - Gokul PS
}

void userModifyContact(){
    // TODO: implement contact modification menu
    // Pending - Gokul PS
}

// Performs an in-place sort by Contact Name on ContactList
void userSortContact(){
    // Implements Selection Sort within Linked List
    for(struct Node* i = contactList; i->next != NULL; i = i->next){
        struct Node *min = i;
        for(struct Node* j = i->next; j != NULL; j = j->next){
            if(strcmp(min->data->name, j->data->name) > 0)
                min = j;
        }
        struct Contact* t = i->data;
        i->data = min->data;
        min->data = t;
    }
    printf("Sort Done...\n");
}

//Function to search by name
struct Node* nameSearch(char *key, struct Node* list){
    struct Node* current = list;    
        while(current != NULL){
            if(strcmp(current->data->name,key) == 0 )
            return current;
            current = current->next;
        }return NULL;
 }

//Function to search by phone number
struct Node* phnoSearch(char *key, struct Node* list){
    struct Node* current = list;   
    while(current != NULL){
        if(strcmp(current->data->phone,key) == 0 ) //strcmp returns 0 if strings are same
         return current;
        current = current->next;
    } return NULL;
 }

void userSearchContact(){
  int choice; char key[ARR_LEN];int exit_choice;
  do {
    printf("To search by name press 1\nTo search by phone number press 2\nEnter your choice: ");
    scanf("%d", &choice);
    struct Node *namesrch;
    char *key;
    switch (choice){
        case 1:
            key = input("Enter the name to be searched");
            namesrch = nameSearch(key, contactList);
            break;
        case 2:
            key = input("Enter the phone number to be searched");
            namesrch = phnoSearch(key, contactList);
            break;
    }
    if(namesrch == NULL)
        printf("No results..");
    else{
        printf("Details of searched employee\n");
        printf("Name: %s\n", namesrch->data->name);
        printf("Phone number: %s\n", namesrch->data->phone);
        printf("Email: %s\n", namesrch->data->email);
    }
    printf("Press 1 to continue searching. Press any other number to exit\n");
    printf("Enter your choice: ");
    scanf("%d", &exit_choice);
  } while (exit_choice == 1);
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
                    displayAllContacts(contactList);
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
