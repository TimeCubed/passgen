#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

long conv;
int errorcode;
char* end;
int strtoi(char* string) {
    conv = strtol(string, &end, 10);
    if (errno != 0 || conv > INT_MAX || conv < INT_MIN || *end != '\0') {
        errorcode = 1;
        return 0;
    } else {
        errorcode = 0;
        return((int) conv);
    }
}
int errorCheck() {
    return errorcode;
}