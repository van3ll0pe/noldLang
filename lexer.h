#ifndef __LEXER_H__
#define __LEXER_H__

typedef enum EN_token {
    TOKEN_NONE,
    TOKEN_PLUS,         //+
    TOKEN_MINUS,        //-
    TOKEN_TIMES,        //*
    TOKEN_DIV,          // /
    TOKEN_MOD,          //%
    TOKEN_RPAR,         // )
    TOKEN_LPAR,         // (
    TOKEN_RBRA,         // }
    TOKEN_LBRA,         // {
    TOKEN_RCRO,         // ]
    TOKEN_LCRO,         // [
    TOKEN_ASSIGN,       // =
    TOKEN_VAR,          // var
    TOKEN_FUN,          // fn
    TOKEN_EQ,           // ==
    TOKEN_NEQ,          // /=
    TOKEN_GT,           // >
    TOKEN_GTE,          // >=
    TOKEN_LT,           // <
    TOKEN_LTE,          // <=
    TOKEN_IF,           // if
    TOKEN_ELSE,         // else
    TOKEN_ELSIF,        // elsif
    TOKEN_WHILE,        // while
    TOKEN_FOR,          // for
    TOKEN_BREAK,        // break
    TOKEN_LOOP,         // loop (alias of continue)
    TOKEN_RETURN,       // return
    TOKEN_MATCH,        // match
    TOKEN_CASE,         // case
    TOKEN_DEFAULT,      // default
    TOKEN_COMMA,        // ,
    TOKEN_SEMICOLON,    // ;
    TOKEN_COLON,        // :
    TOKEN_ID,           // ID of Variable or Function
    TOKEN_VAL,          // NUMBER VALUE or CHAR VALUE
    TOKEN_TYPE_VOID,    //void
    TOKEN_TYPE_U8,
    TOKEN_TYPE_I8,
    TOKEN_TYPE_U16,
    TOKEN_TYPE_I16,
    TOKEN_TYPE_U32,
    TOKEN_TYPE_I32,
    TOKEN_TYPE_U64,
    TOKEN_TYPE_I64,
    TOKEN_TYPE_BOOL,
    TOKEN_TYPE_TRUE,
    TOKEN_TYPE_FALSE,
    TOKEN_EOF
}EN_token_t;

typedef struct token_t {
    EN_token_t token;
    char* value;
} token_t;

typedef struct analyzer_t {
    unsigned long pos;
    char* file;
    char* content_file;
    unsigned long length;
    unsigned long line;
    EN_token_t previous_token;
} analyzer_t;


void create_token_array(char* filename);

#endif
