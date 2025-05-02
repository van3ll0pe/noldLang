#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <ctype.h>
#include <stdbool.h>
#include "lexer.h"
#include "linkedlist.h"


analyzer_t* create_analyzer(char* filename) {
    if (filename == NULL) {
        fprintf(stderr, "[Error] filename given is NULL\n");
        return NULL;
    }

    analyzer_t* analyzer = malloc(sizeof(analyzer_t));
    if (analyzer == NULL)
        return NULL;

    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        free(analyzer);
        return NULL;
    }

    //get size of file
    fseek(file, 0, SEEK_END);
    analyzer->length = ftell(file);
    fseek(file, 0, SEEK_SET);

    //get the name of the file
    analyzer->file = malloc(sizeof(char) * strlen(filename) + 1);
    if (analyzer->file == NULL) {
        fclose(file);
        free(analyzer);
        return NULL;
    }
    strcpy(analyzer->file, filename);

    //get the content of the file
    analyzer->content_file = malloc(sizeof(char) * analyzer->length + 1);
    if (analyzer->content_file == NULL) {
        fclose(file);
        free(analyzer->file);
        free(analyzer);
        return NULL;
    }
    fread(analyzer->content_file, analyzer->length, 1, file);
    analyzer->content_file[analyzer->length] = '\0';

    fclose(file);

    analyzer->pos = 0;
    analyzer->line = 0;
    analyzer->previous_token = TOKEN_NONE;
    
    return analyzer;
}


void destroy_analyzer(analyzer_t** analyzer) {
    if (analyzer == NULL)
        return;
    
    free((*analyzer)->content_file);
    free((*analyzer)->file);
    free(*analyzer);
}

/**
 * @brief check if the word is equal to the tag given.
 * If it's true, true is returned and the pos of the analyzer is set to next word else pos is not changed
 * 
 * @param tag 
 * @param analyzer 
 * @return true 
 * @return false 
 */
static bool is_tag_match(char* tag, analyzer_t* analyzer) {
    if (tag == NULL || analyzer == NULL)
        return false;

    unsigned long pos = analyzer->pos;
    
    if (strlen(tag) + pos >= analyzer->length)
        return false;

    for (int i = 0; tag[i] != '\0'; i++, pos++) {
        if (tag[i] != analyzer->content_file[pos])
            return false;
    }

    //check if the word is an id, if the word continue. example : ifelse
    if (isalnum(analyzer->content_file[pos]) || analyzer->content_file[pos] == '_')
        return false;

    analyzer->pos = pos;
    return true;
}

static void skip_comment(analyzer_t* analyzer) {
    if (analyzer == NULL)
        return;
    
        while (analyzer->pos < analyzer->length && analyzer->content_file[analyzer->pos] != '\n' && analyzer->content_file[analyzer->pos] != '\0')
        analyzer->pos++;
}

static bool is_id(analyzer_t* analyzer, char** id) {
    if (analyzer == NULL || id == NULL)
        return false;
    
    unsigned long pos = analyzer->pos;

    if (pos >= analyzer->length) {
        *id = NULL;
        return false;
    }

    if (!(isalpha(analyzer->content_file[pos]) || analyzer->content_file[pos] == '_')) {
        *id = NULL;
        return false;
    }

    unsigned long start = pos;

    while (pos < analyzer->length) {
        if (!(isalnum(analyzer->content_file[pos]) || analyzer->content_file[pos] == '_')) {
            break;
        }

        pos++;
    }

    unsigned long len_id = pos - start;
    *id = (char*)malloc(sizeof(char) * len_id + 1);
    if (*id == NULL)
        return false;
    
    memcpy(*id, (analyzer->content_file + start), len_id);
    (*id)[len_id] = '\0';

    analyzer->pos = pos;

    return true;
}

static bool is_number(analyzer_t* analyzer, char** nbr) {
    if (analyzer == NULL || nbr == NULL)
        return false;
    
    unsigned long pos = analyzer->pos;

    if (pos >= analyzer->length) {
        *nbr = NULL;
        return false;
    }

    bool has_minus = false;

    if (analyzer->content_file[pos] == '-') {
        has_minus = true;
        pos++;
    }

    if (pos >= analyzer->length || !isdigit(analyzer->content_file[pos])) {
        *nbr = NULL;
        return false;
    }

    unsigned long start = analyzer->pos;

    while (pos < analyzer->length && isdigit(analyzer->content_file[pos])) {
        pos++;
    }

    unsigned long len_nbr = pos - start;
    *nbr = malloc(len_nbr + 1);
    if (*nbr == NULL)
        return false;
    
    memcpy(*nbr, analyzer->content_file + start, len_nbr);
    (*nbr)[len_nbr] = '\0';

    analyzer->pos = pos;
    return true;
}

static bool is_unary_minus(EN_token_t prev) {
    return (
        prev == TOKEN_NONE ||
        prev == TOKEN_ASSIGN ||
        prev == TOKEN_LPAR ||
        prev == TOKEN_COMMA ||
        prev == TOKEN_RETURN ||
        prev == TOKEN_EQ ||
        prev == TOKEN_NEQ ||
        prev == TOKEN_LT ||
        prev == TOKEN_LTE ||
        prev == TOKEN_GT ||
        prev == TOKEN_GTE ||
        prev == TOKEN_MINUS ||
        prev == TOKEN_TIMES ||
        prev == TOKEN_PLUS  ||
        prev == TOKEN_MOD
    );
}

token_t get_next_token(analyzer_t* analyzer) {
    if (analyzer == NULL) {
        fprintf(stderr, "[Error] analyzer is NULL");
        return (token_t){.token = TOKEN_NONE, .value=NULL};
    }

    char* id_value = NULL;

    switch (analyzer->content_file[analyzer->pos]) {
        case '#': {
                    skip_comment(analyzer);
                    return get_next_token(analyzer);
                }
        case ';':   analyzer->pos++;
                    analyzer->previous_token = TOKEN_SEMICOLON;
                    return (token_t){.token=TOKEN_SEMICOLON, .value=NULL};

        case ':':   analyzer->pos++;
                    analyzer->previous_token = TOKEN_COLON;
                    return (token_t){.token=TOKEN_COLON, .value=NULL};
        case ',':   analyzer->pos++;
                    analyzer->previous_token = TOKEN_COMMA;
                    return (token_t){.token=TOKEN_COMMA, .value=NULL};
        case '(':   analyzer->pos++;
                    analyzer->previous_token = TOKEN_LPAR;
                    return (token_t){.token=TOKEN_LPAR, .value=NULL};
        case ')':   analyzer->pos++;
                    analyzer->previous_token = TOKEN_RPAR;
                    return (token_t){.token=TOKEN_RPAR, .value=NULL};
        case '[':   analyzer->pos++;
                    analyzer->previous_token = TOKEN_LCRO;
                    return (token_t){.token=TOKEN_LCRO, .value=NULL};
        case ']':   analyzer->pos++;
                    analyzer->previous_token = TOKEN_RCRO;
                    return (token_t){.token=TOKEN_RCRO, .value=NULL};
        case '{':   analyzer->pos++;
                    analyzer->previous_token = TOKEN_LBRA;
                    return (token_t){.token=TOKEN_LBRA, .value=NULL};
        case '}':   analyzer->pos++;
                    analyzer->previous_token = TOKEN_RBRA;
                    return (token_t){.token=TOKEN_RBRA, .value=NULL};
        case '+':   analyzer->pos++;
                    analyzer->previous_token = TOKEN_PLUS;
                    return (token_t){.token=TOKEN_PLUS, .value=NULL};
        case '-':   {
                        if (is_unary_minus(analyzer->previous_token) && isdigit(analyzer->content_file[analyzer->pos + 1])) {
        
                            if (is_number(analyzer, &id_value)) {
                                analyzer->previous_token = TOKEN_VAL;
                                return (token_t){.token = TOKEN_VAL, .value = id_value};
                            }
                        }

                        analyzer->pos++;
                        analyzer->previous_token = TOKEN_MINUS;
                        return (token_t){.token = TOKEN_MINUS, .value = NULL};
                    }
        case '*':   analyzer->pos++;
                    analyzer->previous_token = TOKEN_TIMES;
                    return (token_t){.token=TOKEN_TIMES, .value=NULL};
        case '%':   analyzer->pos++;
                    analyzer->previous_token = TOKEN_MOD;
                    return (token_t){.token=TOKEN_MOD, .value=NULL};
        case '=':{
                    analyzer->pos++;
                    if (analyzer->content_file[analyzer->pos] == '=') {
                        analyzer->pos++;
                        analyzer->previous_token = TOKEN_EQ;
                        return (token_t){.token=TOKEN_EQ, .value=NULL};
                    }
                    else {
                        analyzer->previous_token = TOKEN_ASSIGN;
                        return (token_t){.token=TOKEN_ASSIGN, .value=NULL};
                    }
                }

        case '>': {
                    analyzer->pos++;
                    if (analyzer->content_file[analyzer->pos] == '=') {
                        analyzer->pos++;
                        analyzer->previous_token = TOKEN_GTE;
                        return (token_t){.token=TOKEN_GTE, .value=NULL};
                    }
                    else {
                        analyzer->previous_token = TOKEN_GT;
                        return (token_t){.token=TOKEN_GT, .value=NULL};
                    }
                }

        case '/': {
                    analyzer->pos++;
                    if (analyzer->content_file[analyzer->pos] == '=') {
                        analyzer->pos++;
                        analyzer->previous_token = TOKEN_NEQ;
                        return (token_t){.token=TOKEN_NEQ, .value=NULL};
                    }
                    else {
                        analyzer->previous_token = TOKEN_DIV;
                        return (token_t){.token=TOKEN_DIV, .value=NULL};
                    }
                }

        case '<': {
                    analyzer->pos++;
                    if (analyzer->content_file[analyzer->pos] == '=') {
                        analyzer->pos++;
                        analyzer->previous_token = TOKEN_LTE;
                        return (token_t){.token=TOKEN_LTE, .value=NULL};
                    }
                    else {
                        analyzer->previous_token = TOKEN_LT;
                        return (token_t){.token=TOKEN_LT, .value=NULL};
                    }
                }

        case '\n': {
                        analyzer->pos++;
                        analyzer->line++;
                        return get_next_token(analyzer);
                }

        case '\0':  analyzer->previous_token = TOKEN_EOF;
                    return (token_t){.token=TOKEN_EOF, .value = NULL};

        default: //ID, VALUE, LOOP, FOR, WHILE, BREAK, MATCH, CASE, DEFAULT, IF, ELSIF, ELSE, VAR, FN, RETURN, u8, i8, u16, i16, u32, i32, u64, i64
                {


                    if (is_tag_match("if", analyzer)) {
                        analyzer->previous_token = TOKEN_IF;
                        return (token_t){.token=TOKEN_IF, .value=NULL};
                    }
                    
                    if (is_tag_match("elsif", analyzer)) {
                        analyzer->previous_token = TOKEN_ELSIF;
                        return (token_t){.token=TOKEN_ELSIF, .value=NULL};
                    }
                    
                    if (is_tag_match("else", analyzer)) {
                        analyzer->previous_token = TOKEN_ELSE;
                        return (token_t){.token=TOKEN_ELSE, .value=NULL};
                    }
                    
                    if (is_tag_match("for", analyzer)) {
                        analyzer->previous_token = TOKEN_FOR;
                        return (token_t){.token=TOKEN_FOR, .value=NULL};
                    }
                    
                    if (is_tag_match("while", analyzer)) {
                        analyzer->previous_token = TOKEN_WHILE;
                        return (token_t){.token=TOKEN_WHILE, .value=NULL};
                    }
                    
                    if (is_tag_match("break", analyzer)) {
                        analyzer->previous_token = TOKEN_BREAK;
                        return (token_t){.token=TOKEN_BREAK, .value=NULL};
                    }
                    
                    if (is_tag_match("loop", analyzer)) {
                        analyzer->previous_token = TOKEN_LOOP;
                        return (token_t){.token=TOKEN_LOOP, .value=NULL};
                    }
                    
                    if (is_tag_match("return", analyzer)) {
                        analyzer->previous_token = TOKEN_RETURN;
                        return (token_t){.token=TOKEN_RETURN, .value=NULL};
                    }
                    
                    if (is_tag_match("match", analyzer)) {
                        analyzer->previous_token = TOKEN_MATCH;
                        return (token_t){.token=TOKEN_MATCH, .value=NULL};
                    }
                    
                    if (is_tag_match("case", analyzer)) {
                        analyzer->previous_token = TOKEN_CASE;
                        return (token_t){.token=TOKEN_CASE, .value=NULL};
                    }
                    
                    if (is_tag_match("default", analyzer)) {
                        analyzer->previous_token = TOKEN_DEFAULT;
                        return (token_t){.token=TOKEN_DEFAULT, .value=NULL};
                    }
                    
                    if (is_tag_match("fun", analyzer)) {
                        analyzer->previous_token = TOKEN_FUN;
                        return (token_t){.token=TOKEN_FUN, .value=NULL};
                    }
                    
                    if (is_tag_match("var", analyzer)) {
                        analyzer->previous_token = TOKEN_VAR;
                        return (token_t){.token=TOKEN_VAR, .value=NULL};
                    }
                    
                    if (is_tag_match("void", analyzer)) {
                        analyzer->previous_token = TOKEN_TYPE_VOID;
                        return (token_t){.token=TOKEN_TYPE_VOID, .value=NULL};
                    }
                    
                    if (is_tag_match("u8", analyzer)) {
                        analyzer->previous_token = TOKEN_TYPE_U8;
                        return (token_t){.token=TOKEN_TYPE_U8, .value=NULL};
                    }

                    if (is_tag_match("i8", analyzer)) {
                        analyzer->previous_token = TOKEN_TYPE_I8;
                        return (token_t){.token=TOKEN_TYPE_I8, .value=NULL};
                    }

                    if (is_tag_match("u16", analyzer)) {
                        analyzer->previous_token = TOKEN_TYPE_U16;
                        return (token_t){.token=TOKEN_TYPE_U16, .value=NULL};
                    }

                    if (is_tag_match("i16", analyzer)) {
                        analyzer->previous_token = TOKEN_TYPE_I16;
                        return (token_t){.token=TOKEN_TYPE_I16, .value=NULL};
                    }

                    if (is_tag_match("u32", analyzer)) {
                        analyzer->previous_token = TOKEN_TYPE_U32;
                        return (token_t){.token=TOKEN_TYPE_U32, .value=NULL};
                    }

                    if (is_tag_match("i32", analyzer)) {
                        analyzer->previous_token = TOKEN_TYPE_I32;
                        return (token_t){.token=TOKEN_TYPE_I32, .value=NULL};
                    }

                    if (is_tag_match("u64", analyzer)) {
                        analyzer->previous_token = TOKEN_TYPE_U64;
                        return (token_t){.token=TOKEN_TYPE_U64, .value=NULL};
                    }

                    if (is_tag_match("i64", analyzer)) {
                        analyzer->previous_token = TOKEN_TYPE_I64;
                        return (token_t){.token=TOKEN_TYPE_I64, .value=NULL};
                    }

                    if (is_tag_match("bool", analyzer)) {
                        analyzer->previous_token = TOKEN_TYPE_BOOL;
                        return (token_t){.token=TOKEN_TYPE_BOOL, .value=NULL};
                    }

                    if (is_tag_match("true", analyzer)) {
                        analyzer->previous_token = TOKEN_TYPE_TRUE;
                        return (token_t){.token=TOKEN_TYPE_TRUE, .value=NULL};
                    }

                    if (is_tag_match("false", analyzer)) {
                        analyzer->previous_token = TOKEN_TYPE_FALSE;
                        return (token_t){.token=TOKEN_TYPE_FALSE, .value=NULL};
                    }

                    if (is_id(analyzer, &id_value)) {
                        analyzer->previous_token = TOKEN_ID;
                        return (token_t){.token=TOKEN_ID, .value=id_value};
                    }

                    if (is_number(analyzer, &id_value)) {
                        analyzer->previous_token = TOKEN_VAL;
                        return (token_t){.token=TOKEN_VAL, .value=id_value};
                    }
                    
                    else {
                        analyzer->pos++;
                        return get_next_token(analyzer);
                    }
                }

    }
        
    return (token_t){.token = TOKEN_NONE, .value=NULL}; //default return
}


void create_token_array(char* filename) {
    analyzer_t* analyzer = create_analyzer(filename);
    Linked_list* list_token = NULL;

    while (analyzer->previous_token != TOKEN_EOF) {
        addElement_end(&list_token, get_next_token(analyzer));
    }
    addElement_end(&list_token, get_next_token(analyzer));
    printElement(&list_token, nbrElement(&list_token)-1);
    printf("\n");
    destroy_analyzer(&analyzer);
}



