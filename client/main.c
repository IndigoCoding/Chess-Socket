#include <stdio.h>
#include "defs.h"

int main() {

    initAll();

    U64 playBitBoard = 0ULL;

    playBitBoard |= (1ULL << SQ64(D2));
    playBitBoard |= (1ULL << SQ64(D3));
    playBitBoard |= (1ULL << SQ64(D4));

    printBitBoard(playBitBoard);

    int count = COUNT(playBitBoard);

    printf("Count:%d\n", count);

    int index = POP(&playBitBoard);
    printf("Index: %d\n", index);
    printBitBoard(playBitBoard);

    count = COUNT(playBitBoard);
    printf("Count:%d\n", count);

    return 0;
}