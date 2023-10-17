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
    printf("%c%d to %c%d\n", getCol[m.getAction(0).square0.row], m.getAction(0).square0.row + 1, getCol[m.getAction(0).square1.row], m.getAction(0).square1.row + 1);
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

    position.playMove(Move::normalMove({1, 4}, {3, 4}));
    PrintPosition(&(position.getBoard()));
    std::cout << "\n";

    position.playMove(Move::normalMove({6, 4}, {4, 4}));
    PrintPosition(&(position.getBoard()));
    std::cout << "\n";

    position.playMove(Move::normalMove({0, 5}, {1, 4}));
    PrintPosition(&(position.getBoard()));
    std::cout << "\n";


    position.playMove(Move::normalMove({7, 5}, {6, 4}));
    PrintPosition(&(position.getBoard()));
    std::cout << "\n";

    position.playMove(Move::normalMove({0, 6}, {2, 5}));
    PrintPosition(&(position.getBoard()));
    std::cout << "\n";

    position.playMove(Move::normalMove({7, 6}, {5, 5}));
    PrintPosition(&(position.getBoard()));
    std::cout << "\n";

    Square from = {.row = 1, .col = 3};
    position.iterateLegalMovesFromSquare(from, [from](Move move) -> chesscat::internal::MoveIterationResult{
        PrintMove(move);
        return chesscat::internal::ContinueMoveIteration;
    });

    return 0;
}
