#ifndef MOVES_HPP
#define MOVES_HPP

#include <stdint.h>

#include "pieces.hpp"

namespace chesscat{

    struct Square
    {
        int row;
        int col;
    };

    namespace internal{
        enum MoveIterationResult
        {
            ContinueMoveIteration,
            BreakMoveIteration
        };
    }
    enum MoveActionType{
        MovePiece, //Moves the piece from square[0] to square[1]
        SetPiece //Sets the piece at square[0] to piece
    };

    struct MoveAction{
        MoveActionType action_type;
        Square square0;
        Square square1;
        Piece piece;
    };

    class Move
    {
        private:
            uint16_t num_actions;
            MoveAction actions[4];
        public:
            static Move emptyMove();
            static Move normalMove(Square from, Square to);
            static Move passantMove(Square from, Square to, Square passanted); //passanted is the pawn to be captured
            static Move promoteMove(Square from, Square to, Piece promoteTo);
            uint16_t getNumActions();
            MoveAction getAction(uint16_t index);
    };
}

#endif
