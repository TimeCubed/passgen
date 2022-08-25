#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

long conv;
int errorcode = 0;
char* end;
int str2int(char* string) {
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
    if (errorcode == 1) {
        return 1;
    } else {
        return 0;
    }
}