#ifndef PIECES_HPP
#define PIECES_HPP

namespace chesscat{
    enum PieceType{
        Empty,
        Pawn,
        Knight,
        Bishop,
        Rook,
        Queen,
        King
    };
    
    #define NUM_COLORS 2
    enum Color{
        White,
        Black
    };

    struct Piece{
        Color color;
        PieceType type;
    };
}

#endif
