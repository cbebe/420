#include "common.h"
#include "operate.h"

void init() {}

void readArr(char *dest, int index, char **strArray) {
    getContent(dest, index, strArray);
}
void writeArr(char *src, int index, char **strArray) {
    setContent(src, index, strArray);
}
