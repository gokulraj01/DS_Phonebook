<!-- Compiled by Gokul Raj on 23 Jan 2022 -->
# Algorithms for Phonebook
1. Declare structure Contact with name, phone, email
2. Declare structure Node with data, next, previous for Doubly Linked List.
3. contactList = NULL, contactListEnd = NULL

-  ## `strfind(str, key, mode)`
    1. i = 0
    2. foreach(char c in str):
        1. if(c == key[i])
            - i++
        2. else if(mode)
            - i = 0
        3. if(i == length of key)
            - return 1
    3. return 0

-  ## `printFile(filename)`
    1. DISPLAY content of file at filename

-  ## `displayAllContacts(list)`
    1. p = list
    1. while(p != NULL):
        - DISPLAY name, phone, email from p
        - p = p->next

-  ## `addContact(name, phone, email)`
    1. Create new Contact with name, phone, email - newContact
    2. Create new Node with newContact as data - newNode
    3. if(contactListEnd == NULL):
        - contactList = newNode
    4. else:
        - contactListEnd->next = newNode
    5. newNode->prev = contactListEnd;
    6. newNode->next = NULL;
    7. contactListEnd = newNode;

-  ## `deleteContact(node)`
    1. if (node->prev == NULL):
        1. node->next->prev = NULL;
        2. contactList = node->next;
    2. else if (node->next == NULL):
        1. node->prev->next = NULL;
        2. contactListEnd = node->prev;
    3. else:
        1. node->prev->next = node->next;
        2. node->next->prev = node->prev;
    4. Delete node->data and node

-  ## `searchContact()`
    1. DISPLAY search menu with choice of search as name, phone, email
    2. INPUT choice
    3. DO UNTIL result_count <= 1:
        1. INPUT query
        2. p = contactList
        3. while(p != NULL):
            1. Set str as per choice:
                - If name: str = p->data->name
                - If phone: str = p->data->phone
                - If email: str = p->data-email
            2. Call strfind with str, key
            3. if strfind returns 1:
                1. result_count += 1
                2. result = p
    4. if(result_count == 1)
        - return result
    5. else
        - return NULL


-  ## `parsePhonebook(file)`
    1. contactList = NULL
    2. Declare buffer with 3 areas
    3. OPEN file to read
    4. foreach(char c in file until EOF):
        1. if(c is CONTACT_DELIMITER)
            - Call addContact with all 3 buffer contents
        2. if(c is ITEM_DELIMITER)
            - Switch to next buffer area
        3. Copy c into current buffer
    5. CLOSE file

-  ## `writePhonebook(file)`
    1. OPEN file to write
    2. p = contactList
    3. while(p != NULL):
        1. WRITE p->data->name, ITEM_DELIMITER, p->data->phone, ITEM_DELIMITER, p->data->email, CONTACT_DELIMITER in order
        2. p = p->next
    4. CLOSE file

-  ## `userAddContact()`
    1. INPUT name, phone, email
    2. Call addContact with name, phone, email

-  ## `userDeleteContact()`
    1. Call searchContact, store returned node as result.
    2. Call deleteContact with result

-  ## `userModifyContact()`
    1. Call searchContact, store returned node as result.
    2. INPUT choice of edit, from name, phone, email
    3. INPUT new data - newData
    4. Set corresponding entry in result = newData

-  ## `userSortContact()`
    1. i = contactList
    2. while(i->next != NULL):
        1. j = i->next
        2. min = i;
        3. while(j != NULL):
            - if(name in min > name in j):
                - min = j
        4. SWAP min with i

-  ## `userSearchContact()`
    1. Call searchContact, store returned node as result.
    2. DISPLAY name, phone, email from result

-  ## `userExit()`
    1. Call writePhonebook with destination phonebook file
    2. EXIT program

-  ## `showMenu()`
    1. DO UNTIL exit:
        1. DISPLAY menu with choices to add, delete, modify, sort, search, display, and exit.
        2. Call corresponding function from userAddContact, userDeleteContact, userModifyContact, userSortContact, userSearchContact, displayAllContacts, userExit

-  ## `main()`
    1. Call parsePhonebook with location of phonebook file as parameter.
    1. Call showMenu