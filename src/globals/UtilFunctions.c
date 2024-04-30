#include "UtilFunctions.h"
#include <time.h>

int randIntInRange(int low, int high) {
    int random = rand();
    return intWrap(random, low, high);
}

int intWrap(int input, int low, int high) {
    return (input % (high - low + 1)) + low;
}

void seedRandomInt(int seed) {
    srand(seed);
}

void seedRandomTime() {
    srand((unsigned int)time(NULL));
}
