#include "linkedlist.h"


void addElement_top(Linked_list **linked_list, token_t value) { //add a new element of the 
    
    Linked_list *new_element = malloc(sizeof(Linked_list) * 1);
    new_element->i = value;

    new_element->next = (*linked_list);
    (*linked_list) = new_element;
}

void removeElement_top(Linked_list **linked_list) { //remove the first element of the linked list
    if ((*linked_list) != NULL) {
        Linked_list *tmp = (*linked_list);

        (*linked_list) = (*linked_list)->next;
        free(tmp);
    }
}

int nbrElement(Linked_list **linked_list) { //function to give the number of element of the linked list
    int nbr = 0;

    if ((*linked_list) != NULL) {
        Linked_list *element = (*linked_list);

        while (element->next != NULL) {
            nbr++;
            element = element->next;
        }
        nbr++;
    }
    return nbr;
}

void removeElement_end(Linked_list **linked_list) {//function to remove the last element of the linked last
        if (*linked_list != NULL) {
            if (nbrElement(linked_list) == 1) {
                free((*linked_list));
                (*linked_list) = NULL;
            } else {
                Linked_list *element = (*linked_list);
                Linked_list *tmp = (*linked_list);
                while (element->next != NULL) {
                    element = element->next;
                }

                while (tmp->next != element) {
                    tmp = tmp->next;
                }

                tmp->next = element->next;
                free(element);
            }
            
        }
}

void addElement_end(Linked_list **linked_list, token_t value) { //function to add new element at the end of the linked list
    Linked_list *element = malloc(sizeof(Linked_list) * 1);
    element->i = value;

    if (*linked_list == NULL) {
        element->next = (*linked_list);
        (*linked_list) = element;
    } else {
        
        Linked_list *tmp = (*linked_list);

        while (tmp->next != NULL) {
            tmp = tmp->next;
        }

        element->next = tmp->next;
        tmp->next = element;
    }
}

void printElement(Linked_list **linked_list, int nPosition) {
    if (nPosition < 0 || nPosition >= nbrElement(linked_list)) {
        printf("No element\n");
    } else {
        Linked_list *element = (*linked_list);

        for (int i = 0; i < nPosition; i++) {
            switch (element->i.token) {
                case TOKEN_NONE:    printf("TOKEN_NONE");
                                    break;
                case TOKEN_PLUS :   printf("TOKEN_PLUS");
                                    break;
                case TOKEN_MINUS :  printf("TOKEN_MINUS");
                                    break;
                case TOKEN_TIMES :  printf("TOKEN_TIMES");
                                    break;
                case TOKEN_DIV :    printf("TOKEN_DIV");
                                    break;
                case TOKEN_MOD :    printf("TOKEN_MOD");
                                    break;
                case TOKEN_RPAR :   printf("TOKEN_RPAR");
                                    break;
                case TOKEN_LPAR :   printf("TOKEN_LPAR");
                                    break;
                case TOKEN_RBRA :   printf("TOKEN_RBRA");
                                    break;
                case TOKEN_LBRA :   printf("TOKEN_LBRA");
                                    break;
                case TOKEN_RCRO :   printf("TOKEN_RCRO");
                                    break;
                case TOKEN_LCRO :   printf("TOKEN_LCRO");
                                    break;
                case TOKEN_ASSIGN : printf("TOKEN_ASSIGN");
                                    break;
                case TOKEN_VAR :    printf("TOKEN_VAR");
                                    break;
                case TOKEN_FUN :    printf("TOKEN_FUN");
                                    break;
                case TOKEN_EQ :     printf("TOKEN_EQ");
                                    break;
                case TOKEN_NEQ :    printf("TOKEN_NEQ");
                                    break;
                case TOKEN_GT :     printf("TOKEN_GT");
                                    break;
                case TOKEN_GTE :    printf("TOKEN_GTE");
                                    break;
                case TOKEN_LT :     printf("TOKEN_LT");
                                    break;
                case TOKEN_LTE :    printf("TOKEN_LTE");
                                    break;
                case TOKEN_IF :     printf("TOKEN_IF");
                                    break;
                case TOKEN_ELSE :   printf("TOKEN_ELSE");
                                    break;
                case TOKEN_ELSIF :  printf("TOKEN_ELSIF");
                                    break;
                case TOKEN_WHILE :  printf("TOKEN_WHILE");
                                    break;
                case TOKEN_FOR :    printf("TOKEN_FOR");
                                    break;
                case TOKEN_BREAK :  printf("TOKEN_BREAK");
                                    break;
                case TOKEN_LOOP :   printf("TOKEN_LOOP");
                                    break;
                case TOKEN_RETURN : printf("TOKEN_RETURN");
                                    break;
                case TOKEN_MATCH :  printf("TOKEN_MATCH");
                                    break;
                case TOKEN_CASE :   printf("TOKEN_CASE");
                                    break;
                case TOKEN_DEFAULT :printf("TOKEN_DEFAULT");
                                    break;
                case TOKEN_COMMA :  printf("TOKEN_COMMA");
                                    break;
                case TOKEN_SEMICOLON :printf("TOKEN_SEMICOLON");
                                    break;
                case TOKEN_COLON :  printf("TOKEN_COLON");
                                    break;
                case TOKEN_ID :     printf("TOKEN_ID \"%s\"", element->i.value);
    
                                    break;
                case TOKEN_VAL :    printf("TOKEN_VAL \"%s\"", element->i.value);
                                    break;
                case TOKEN_TYPE_VOID :printf("TOKEN_TYPE_VOID");
                                    break;
                case TOKEN_TYPE_U8 :printf("TOKEN_TYPE_U8");
                                    break;
                case TOKEN_TYPE_I8 :printf("TOKEN_TYPE_I8");
                                    break;
                case TOKEN_TYPE_U16 :printf("TOKEN_TYPE_U16");
                                    break;
                case TOKEN_TYPE_I16 :printf("TOKEN_TYPE_I16");
                                    break;
                case TOKEN_TYPE_U32 :printf("TOKEN_TYPE_U32");
                                    break;
                case TOKEN_TYPE_I32 :printf("TOKEN_TYPE_I32");
                                    break;
                case TOKEN_TYPE_U64 :printf("TOKEN_TYPE_U64");
                                    break;
                case TOKEN_TYPE_I64 :printf("TOKEN_TYPE_I64");
                                    break;
                case TOKEN_TYPE_BOOL :printf("TOKEN_TYPE_BOOL");
                                    break;
                case TOKEN_TYPE_TRUE :printf("TOKEN_TRUE");
                                    break;
                case TOKEN_TYPE_FALSE :printf("TOKEN_FALSE");
                                    break;
                case TOKEN_EOF :    printf("TOKEN_EOF");
                                    break;
            }
            printf(",");
            element = element->next;
        }
    }
}

void addElement_nPosition(Linked_list **linked_list, token_t value, int nPosition) {
    if (nPosition < 0 || nPosition > nbrElement(linked_list)) {
        printf("no position valid\n");
    } else {
        Linked_list *element = malloc(sizeof(Linked_list) * 1);
        element->i = value;

        if (*linked_list == NULL && nPosition == 0)
        {
            element->next = NULL;
            (*linked_list) = element;

        }
        else if (*linked_list != NULL && nPosition == 0) {
            element->next = (*linked_list);
            (*linked_list) = element;
        }
        else {
            Linked_list *tmp = (*linked_list);
            for (int i = 1; i < nPosition; i++) {
                tmp = tmp->next;
            }

            element->next = tmp->next;
            tmp->next = element;
        } 
    }
}

void removeElement_nPosition(Linked_list **linked_list, int nPosition) {
    if (nPosition < 0 || nPosition >= nbrElement(linked_list)) {
        printf("no position valid\n");
    } else {
        if (nPosition != 0 && (*linked_list) != NULL) {
            Linked_list *tmp = (*linked_list);
            Linked_list *tmp_before = tmp;
            for (int i = 1; i < nPosition; i++) {
                tmp_before = tmp;
                tmp = tmp->next;
            }
            tmp_before->next = tmp->next;
            free(tmp);
        }
        else if (nPosition == 0 && (*linked_list) != NULL){
            Linked_list *tmp = (*linked_list);
            (*linked_list) = (*linked_list)->next;
            free(tmp);
        }
        else {
            return ;
        }
    }
}