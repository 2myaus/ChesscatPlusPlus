#ifndef CHESSCAT_HPP
#define CHESSCAT_HPP

#include <vector>
#include <memory>
#include <functional>

#include "pieces.hpp"
#include "squares.hpp"

namespace chesscat {

    class Board {
    private:
        unsigned short num_cols;
        unsigned short num_rows;
        std::unique_ptr<Piece[]> board_array;
    public:
        Board(unsigned short cols, unsigned short rows);
        void resize(unsigned short new_cols, unsigned short new_rows);
        void setPiece(Square square, Piece piece);
        Piece getPiece(Square square);
        void shift(int vertical, int horizontal);
        bool squareInBounds(Square square);
    };

    class Position {
    private:
        Board board;
        Color to_move;
        Move last_move;

        bool colorCanCapturePiece(Color color, Piece captured);
        void iteratePossibleMovesFromSquare(Square square, std::function<bool(const Square)> func);
    public:
        Position();
        ~Position();
        Piece getPiece(Square square);
        bool isMoveLegal(Move move);
    };

}

#endif
