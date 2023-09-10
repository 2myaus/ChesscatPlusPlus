#include <stdio.h>
#include <string.h>
#include <iostream>
#include <cctype>
#include "../chesscat.hpp"

using namespace chesscat;

char GetPieceChar(Piece piece)
{
    char base;
    switch (piece.type)
    {
    case Pawn:
        base = 'p';
        break;
    case King:
        base = 'k';
        break;
    case Queen:
        base = 'q';
        break;
    case Rook:
        base = 'r';
        break;
    case Knight:
        base = 'n';
        break;
    case Bishop:
        base = 'b';
        break;
    default:
        base = ' ';
        break;
    }
    if (piece.color == White)
    {
        return std::toupper(base);
    }
    return base;
}

void PrintMove(Move m)
{
    char getCol[8] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
    printf("%c%d to %c%d\n", getCol[m.from.col], m.from.row + 1, getCol[m.to.col], m.to.row + 1);
}

void PrintPosition(Board *board)
{
    bool white = true;
    for (int8_t row = board->getNumRows() - 1; row >= 0; row--)
    {
        for (int8_t col = 0; col < board->getNumCols(); col++)
        {
            Square checking = {.row = row, .col = col};
            if (white)
            {
                printf("\e[1;30;107m");
            }
            else
            {
                printf("\e[1;97;40m");
            }
            printf("%c", GetPieceChar(board->getPiece(checking)));
            white = !white;
        }
        printf("\e[m\n");
        white = !white;
    }
}

int main(){

    printf("%d\n", chesscat::White);

    chesscat::Position position;

    PrintPosition(&(position.getBoard()));
    std::cout << "\n";

    position.playMove({.from = {1, 4}, .to = {3, 4}}, chesscat::Queen);
    PrintPosition(&(position.getBoard()));
    std::cout << "\n";

    position.playMove({.from = {6, 4}, .to = {4, 4}}, chesscat::Queen);
    PrintPosition(&(position.getBoard()));
    std::cout << "\n";

    position.playMove({.from = {0, 3}, .to = {4, 7}}, chesscat::Queen);
    PrintPosition(&(position.getBoard()));
    std::cout << "\n";


    position.playMove({.from = {6, 5}, .to = {5, 5}}, chesscat::Queen);
    PrintPosition(&(position.getBoard()));
    std::cout << "\n";

    Square from = {.row = 1, .col = 3};
    position.iterateLegalMovesFromSquare(from, [from](Square square) -> chesscat::internal::MoveIterationResult{
        Move m = {.from = from, .to = square};
        PrintMove(m);
        return chesscat::internal::ContinueMoveIteration;
    });

    return 0;
}
