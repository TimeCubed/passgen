    #include "str2int.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define CAPITALS "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
#define SMALL "abcdefghijklmonpqrstuvwxyz"
#define ALPHABET CAPITALS SMALL
#define NUMBERS "1234567890"
#define SPECIALS "!#$@&"
#define ALLCHARS ALPHABET NUMBERS SPECIALS

int passlength, errcode, bytes;
char* characters;
int numinclude = 0, specialinclude = 0, alphainclude = 0, capitalinclude = 0, smallinclude = 0;

int main(int argc, char* argv[]) {
    characters = (char*) malloc(1);
    srand(time(NULL));
    if (argc > 1) {
        passlength = str2int(argv[1]);
        errcode = errorCheck();
        if (errcode != 0) {
            printf("passgen %s\n", argv[1]);
            printf("        ^ Here\n");
            printf("Invalid input for integer");
            return 0;
        }
    } else {
        printf("Usage: passgen <passlength> [add-all] [include-numbers] [include-specials] [include-alphabet] [include-capitals] [include-small]");
        printf("\n[] = Optional, <> = Required\n");
        printf("Options:\n");
        printf("    add-all: Includes all characters. Default option if no flags are provided.\n");
        printf("    include-numbers: Adds numbers to the list of usable characters.\n");
        printf("    include-specials: Adds special characters (!#$@&) to the list of usable characters.\n");
        printf("    include-alphabet: Adds the entire alphabet (including capital and small letters) to the list of usable characters.\n");
        printf("    include-capitals: Adds the capital alphabet to the list of usable characters.\n");
        printf("    include-small: Adds the small alphabet to the list of usable characters.\n");
        return 0;
    }
    struct  {
        char *dict, *text;
        int used;
    } data[] = {
        {"add-all", ALLCHARS, 0},
        {"include-numbers", NUMBERS, 0},
        {"include-specials", SPECIALS, 0},
        {"include-alphabet", ALPHABET, 0},
        {"include-capitals", CAPITALS, 0},
        {"include-small", SMALL, 0}
    };
    size_t dicts = sizeof data / sizeof data[0];
    size_t total_len = 0;

    if (argc > 2) {
        for (int i = 2; i < argc; i++) {
            for (size_t j = 0; j < dicts; j++) {
                if ((data[j].used == 0) && (strcmp(argv[i], data[j].dict) == 0)) {
                    size_t len = strlen(data[j].text);
                    char *temp = realloc(characters, total_len + len + 1);

                    if (temp == NULL)
                    {
                        perror("realloc");
                        exit(EXIT_FAILURE);
                    }
                    characters = temp;
                    memcpy(characters + total_len, data[j].text, len);
                    total_len += len;
                    characters[total_len] = '\0';
                    data[j].used = 1;
                    break;
                }
            }
        }
        goto generate;
    }
    characters = (char*) realloc(characters, 68);
    characters = ALLCHARS;
    generate:
    printf("Generating password with length %d\n", passlength);
    for (int x = 0; x < passlength; x++){
        printf("%c", characters[rand() % ((int) strlen(characters))]);
    }
}