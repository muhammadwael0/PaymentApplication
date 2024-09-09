#ifndef LIST_H
#define LIST_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../libs/std_types.h"

struct accountData
{
    uint8 cardHolderName[25];
    uint8 primaryAccountNumber[20];
    uint8 cardExpirationDate[6];
    float balance;
    uint8 state[8];
};

struct Node{
    struct accountData NodeData;
    struct Node *NodeLink;
};

//extern struct Node *ListHead;

void find_node(struct Node *List, uint8 *cardPan, struct accountData *accountData);

void update_node(struct Node *List, struct accountData *accountData);

void push_front(struct Node **List, struct accountData accountData);

void push_back(struct Node **List, struct accountData accountData);

void insert_after(struct Node *List);

void pop_front(struct Node **List);

void remove_element(struct Node *List);

void display_all(struct Node *List);

uint32 length(struct Node *List);

void free_memory(struct Node *List);


#endif