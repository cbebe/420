#include <stdio.h>

#define RESTORE "\033[0m"
#define RED "\033[01;31m"
#define GREEN "\033[01;32m"
#define YELLOW "\033[01;33m"
#define BLUE "\033[01;34m"
#define MAGENTA "\033[00;35m"
#define PURPLE "\033[01;35m"

#define log(str, colour) printf("%s%s%s", colour, str, RESTORE)

int main() {
    log("Hello ", RED);
    log("world\n", GREEN);
}