#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "lexer.h"

typedef struct Linked_list {
    token_t i;
    struct Linked_list *next;
}Linked_list;

void addElement_end(Linked_list **linked_list, token_t value);
void removeElement_end(Linked_list **linked_list);
int nbrElement(Linked_list **linked_list);
void removeElement_top(Linked_list **linked_list);
void addElement_top(Linked_list **linked_list, token_t value);
void printElement(Linked_list **linked_list, int nPosition);
void addElement_nPosition(Linked_list **linked_list, token_t value, int nPosition);
void removeElement_nPosition(Linked_list **linked_list, int nPosition);

#endif