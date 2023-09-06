#include <stdio.h>
#include "../chesscat.hpp"

int main(){

    printf("%d\n", chesscat::White);

    chesscat::Position position;

    printf("%d\n", position.getPiece({.row = 0, .col = 0}).type);

    return 0;
}
