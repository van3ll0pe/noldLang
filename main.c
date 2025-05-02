#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "lexer.h"


int main(int ac, char** av) {
    if (ac != 2) {
        fprintf(stderr, "[Error] : Wrong argument given\n");
        return 1;
    }

    create_token_array(av[1]);

    return 0;
}