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
        Board& operator=(const Board& rhs);
        unsigned short getNumCols();
        unsigned short getNumRows();
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

        bool colorCanCapturePiece(Color color, Piece captured); //Check if a color is allowed to capture a piece
        void iteratePossibleMovesFromSquare(Square square, std::function<internal::MoveIterationResult(const Square)> func);
        void iterateAllPossibleMoves(std::function<internal::MoveIterationResult(const Move)> func);
        void setNextToMove();
        bool squareIsOnPromotionRank(Square square);
        void playMoveNoConfirm(Move move, PieceType pawn_promotion); //Play a move without confirming its legality
        bool movesIntoCheck(Move move); //Check if a move moves into check
    public:
        Position();
        ~Position();
        Position& operator=(const Position& rhs);
        Piece getPiece(Square square);
        bool isMoveLegal(Move move);
        void iterateLegalMovesFromSquare(Square square, std::function<internal::MoveIterationResult(const Square)> func);
        void PlayMove(Move move, PieceType pawn_promotion);
    };

}

#endif
