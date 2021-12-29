#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define ARR_LEN 256
#define CONTACT_DELIMITER '\n'
#define ITEM_DELIMITER '\t'
#define PHONEBOOK_NAME "phonebook.txt"
#define CREDITS "screens/credits.txt"
#define CREDIT_DURATION 1
#define clrscr() printf("\e[1;1H\e[2J")
#define MENU "screens/menu.txt"

struct Contact{
    char name[ARR_LEN];
    char phone[20];
    char email[ARR_LEN];
};

struct Node{
    struct Contact* data;
    struct Node *next;
    struct Node *prev;
};

struct Node* CONTACT_LIST = NULL;
struct Node* CONTACT_LIST_END = NULL;

char* input(char* msg){
    printf("%s: ", msg);
    char* op = malloc(ARR_LEN);
    op[0] = '\n';
    while(op[0] == '\n')
        fgets(op, ARR_LEN, stdin);
    unsigned int len = 0;
    while(op[++len] != '\0');
    op[len-1] = '\0';
    return op;
}

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

void addContact(char* name, char* phone, char* email){
    struct Node* newNode = malloc(sizeof(struct Node));
    struct Contact* newContact = malloc(sizeof(struct Contact));
    strcpy(newContact->name, name);
    strcpy(newContact->phone, phone);
    strcpy(newContact->email, email);
    newNode->data = newContact;

    if(CONTACT_LIST_END == NULL)
        CONTACT_LIST = newNode;
    else
        CONTACT_LIST_END->next = newNode;

    newNode->prev = CONTACT_LIST_END;
    newNode->next = NULL;

    CONTACT_LIST_END = newNode;
}

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

void showCredits(){
    clrscr();
    printFile(CREDITS);
    sleep(CREDIT_DURATION);
    clrscr();
}

void writePhonebook(){
    // write out phonebook data from memory to file (filename is value of PHONEBOOK_NAME)
    printf("Phonebook saved to %s", PHONEBOOK_NAME);
}

void userExit(){
    clrscr();
    printf("Exitting Phonebook.....\n");
    writePhonebook();
    return;
}

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
    // implement Delete Contact for Menu option 2
}

void userModifyContact(){
    // implement contact modification menu for Menu option 3
}

void userSortContact(){
    // implement Sort functionality for Menu option 4
}

void userSearchContact(){
    // implement Search functionality for Menu option 5 and 6
}

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