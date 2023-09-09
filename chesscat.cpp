#include "chesscat.hpp"
#include "pieces.hpp"
#include "squares.hpp"
#include <cstdio>

namespace chesscat{
    using namespace internal;

    const Piece EmptyPiece = {.color = White, .type = Empty};
    const Square EmptySquare = {.row = -1, .col = -1};
    const Move EmptyMove = {.from = EmptySquare, .to = EmptySquare};

    bool operator==(const Square& lhs, const Square& rhs) {
        return lhs.row == rhs.row && lhs.col == rhs.col;
    }
    bool operator==(const Move& lhs, const Move& rhs) {
        return lhs.to == rhs.to && lhs.from == rhs.from;
    }

    Board::Board(unsigned short cols, unsigned short rows) : num_cols(0), num_rows(0){
        resize(cols, rows);
    }
    Board::Board() : Board(8, 8){
        Piece wPawn = {.color = White, .type = Pawn};
        Piece wKing = {.color = White, .type = King};
        Piece wQueen = {.color = White, .type = Queen};
        Piece wRook = {.color = White, .type = Rook};
        Piece wKnight = {.color = White, .type = Knight};
        Piece wBishop = {.color = White, .type = Bishop};

        Piece bPawn = {.color = Black, .type = Pawn};
        Piece bKing = {.color = Black, .type = King};
        Piece bQueen = {.color = Black, .type = Queen};
        Piece bRook = {.color = Black, .type = Rook};
        Piece bKnight = {.color = Black, .type = Knight};
        Piece bBishop = {.color = Black, .type = Bishop};

        for (unsigned short col = 0; col <= 7; col++)
        {
            setPiece({.row = 1, .col = col}, wPawn);
            setPiece({.row = 2, .col = col}, EmptyPiece);
            setPiece({.row = 3, .col = col}, EmptyPiece);
            setPiece({.row = 4, .col = col}, EmptyPiece);
            setPiece({.row = 5, .col = col}, EmptyPiece);
            setPiece({.row = 6, .col = col}, bPawn);
        }

        setPiece({.row = 0, .col = 0}, wRook);

        setPiece({.row = 0, .col = 0}, wRook);
        setPiece({.row = 0, .col = 1}, wKnight);
        setPiece({.row = 0, .col = 2}, wBishop);
        setPiece({.row = 0, .col = 3}, wQueen);
        setPiece({.row = 0, .col = 4}, wKing);
        setPiece({.row = 0, .col = 5}, wBishop);
        setPiece({.row = 0, .col = 6}, wKnight);
        setPiece({.row = 0, .col = 7}, wRook);

        setPiece({.row = 7, .col = 0}, bRook);
        setPiece({.row = 7, .col = 1}, bKnight);
        setPiece({.row = 7, .col = 2}, bBishop);
        setPiece({.row = 7, .col = 3}, bQueen);
        setPiece({.row = 7, .col = 4}, bKing);
        setPiece({.row = 7, .col = 5}, bBishop);
        setPiece({.row = 7, .col = 6}, bKnight);
        setPiece({.row = 7, .col = 7}, bRook);
    }
    Board::Board(const Board &copyfrom) : Board(copyfrom.num_cols, copyfrom.num_rows){
        for(unsigned int idx = 0; idx < num_cols * num_rows; idx++){
            board_array[idx] = copyfrom.board_array[idx];
        }
    }
    unsigned short Board::getNumCols(){
        return num_cols;
    }
    unsigned short Board::getNumRows(){
        return num_rows;
    }

    void Board::resize(unsigned short new_cols, unsigned short new_rows){
            std::unique_ptr<Piece[]> new_board = std::make_unique<Piece[]>(new_cols * new_rows);

            for(unsigned short idx = 0; idx < new_cols * new_rows; idx++){
                new_board[idx] = {.color = White, .type = Empty};
            }
            Square current_square;
            for(current_square.col = 0; current_square.col < num_cols; current_square.col++){
                for(current_square.row = 0; current_square.row < num_rows; current_square.row++){
                    new_board[current_square.row * new_cols + current_square.col] = getPiece(current_square);
                }
            }

            num_cols = new_cols;
            num_rows = new_rows;

            board_array = std::move(new_board);
        }
    void Board::setPiece(Square square, Piece piece){
        if(square.col < 0 || square.col >= num_cols || square.row < 0 || square.row >= num_rows){
            throw "Cannot set piece outside of board!";
        }
        board_array[square.row * num_cols + square.col] = piece;
        return;
    }
    Piece Board::getPiece(Square square){
        if(square.col < 0 || square.col >= num_cols || square.row < 0 || square.row >= num_rows){
            return EmptyPiece;
        }
        return board_array[square.row * num_cols + square.col];
    }
    void Board::shift(int vertical, int horizontal){ //Shift all pieces on the board
            if(horizontal > 0){
                for(int col = num_cols - horizontal; col >= 0; col--){
                    for(int row = 0; row < num_rows; row++){
                        Square original = {.row = row, .col = col};
                        Square new_square = {.row = row, .col = col + horizontal};
                        setPiece(new_square, getPiece(original));
                    }
                }
            }
            else if(horizontal < 0){
                for(int col = -horizontal; col < num_cols; col++){
                    for(int row = 0; row < num_rows; row++){
                        Square original = {.row = row, .col = col};
                        Square new_square = {.row = row, .col = col + horizontal};
                        setPiece(new_square, getPiece(original));
                    }
                }
            }

            if(vertical > 0){
                for(int col = 0; col < num_cols; col++){
                    for(int row = num_rows - vertical; row >= 0; row--){
                        Square original = {.row = row, .col = col};
                        Square new_square = {.row = row + vertical, .col = col};
                        setPiece(new_square, getPiece(original));
                    }
                }
            }
            else if(vertical < 0){
                for(int col = 0; col < num_cols; col++){
                    for(int row = -vertical; row < num_rows; row++){
                        Square original = {.row = row, .col = col};
                        Square new_square = {.row = row + vertical, .col = col};
                        setPiece(new_square, getPiece(original));
                    }
                }
            }
        }
    bool Board::squareInBounds(Square square){
        return (square.col >= 0 && square.row >= 0 && square.col < num_cols && square.row < num_rows);
    }



    Position::Position(Board board) : board(board), to_move(White), last_move(EmptyMove) {}
    Position::Position() : Position(*new Board()) {}
    Position::~Position() {}
    Position::Position(const Position &copyfrom) : Position(copyfrom.board) {}

    Board& Position::getBoard(){
        return board;
    }
    bool Position::colorCanCapturePiece(Color color, Piece captured){
        if(captured.type == Empty){
            return true;
        }
        if(captured.color == color){
            return false;
        }
        return true;
    }
    void Position::iteratePossibleMovesFromSquare(Square square, const std::function<MoveIterationResult(const Square)> func){ //Stop iteration if func returns to stop
        Piece piece = board.getPiece(square);
        if(piece.color != to_move || piece.type == Empty){
            return;
        }
        if(piece.type == King){
            Square down_left = {.row = square.row - 1, .col = square.col - 1};
            Square down = {.row = square.row - 1, .col = square.col};
            Square down_right = {.row = square.row - 1, .col = square.col + 1};
            Square left = {.row = square.row, .col = square.col - 1};
            Square right = {.row = square.row, .col = square.col + 1};
            Square up_left = {.row = square.row + 1, .col = square.col - 1};
            Square up = {.row = square.row + 1, .col = square.col};
            Square up_right = {.row = square.row + 1, .col = square.col + 1};

            //TODO: Add castle

            if (board.squareInBounds(down_left) && colorCanCapturePiece(to_move, board.getPiece(down_left))){
                if(func(down_left) == BreakMoveIteration) return;
            }
            if (board.squareInBounds(down) && colorCanCapturePiece(to_move, board.getPiece(down))){
                if(func(down) == BreakMoveIteration) return;
            }

            if (board.squareInBounds(down_right) && colorCanCapturePiece(to_move, board.getPiece(down_right))){
                if(func(down_right) == BreakMoveIteration) return;
            }
            if (board.squareInBounds(left) && colorCanCapturePiece(to_move, board.getPiece(left))){
                if(func(left) == BreakMoveIteration) return;
            }

            if (board.squareInBounds(right) && colorCanCapturePiece(to_move, board.getPiece(right))){
                if(func(right) == BreakMoveIteration) return;
            }
            if (board.squareInBounds(up_left) && colorCanCapturePiece(to_move, board.getPiece(up_left))){
                if(func(up_left) == BreakMoveIteration) return;
            }

            if (board.squareInBounds(up) && colorCanCapturePiece(to_move, board.getPiece(up))){
                if(func(up) == BreakMoveIteration) return;
            }
            if (board.squareInBounds(up_right) && colorCanCapturePiece(to_move, board.getPiece(up_right))){
                if(func(up_right) == BreakMoveIteration) return;
            }
        }
        if(piece.type == Knight){
            Square up_left = {.row = square.row + 2, .col = square.col - 1};
            Square up_right = {.row = square.row + 2, .col = square.col + 1};

            Square right_up = {.row = square.row + 1, .col = square.col + 2};
            Square right_down = {.row = square.row - 1, .col = square.col + 2};

            Square down_right = {.row = square.row - 2, .col = square.col + 1};
            Square down_left = {.row = square.row - 2, .col = square.col - 1};

            Square left_down = {.row = square.row - 1, .col = square.col - 2};
            Square left_up = {.row = square.row + 1, .col = square.col - 2};

            if (board.squareInBounds(up_left) && colorCanCapturePiece(to_move, board.getPiece(up_left))){
                if(func(up_left) == BreakMoveIteration) return;
            }
            if (board.squareInBounds(up_right) && colorCanCapturePiece(to_move, board.getPiece(up_right))){
                if(func(up_right) == BreakMoveIteration) return;
            }

            if (board.squareInBounds(right_up) && colorCanCapturePiece(to_move, board.getPiece(right_up))){
                if(func(right_up) == BreakMoveIteration) return;
            }
            if (board.squareInBounds(right_down) && colorCanCapturePiece(to_move, board.getPiece(right_down))){
                if(func(right_down) == BreakMoveIteration) return;
            }

            if (board.squareInBounds(down_right) && colorCanCapturePiece(to_move, board.getPiece(down_right))){
                if(func(down_right) == BreakMoveIteration) return;
            }
            if (board.squareInBounds(down_left) && colorCanCapturePiece(to_move, board.getPiece(down_left))){
                if(func(down_left) == BreakMoveIteration) return;
            }

            if (board.squareInBounds(left_down) && colorCanCapturePiece(to_move, board.getPiece(left_down))){
                if(func(left_down) == BreakMoveIteration) return;
            }
            if (board.squareInBounds(left_up) && colorCanCapturePiece(to_move, board.getPiece(left_up))){
                if(func(left_up) == BreakMoveIteration) return;
            }
        }
        if(piece.type == Bishop || piece.type == Queen){
            for(unsigned short dir = 0; dir < 4; dir++){
                short dx;
                short dy;
                switch (dir)
                {
                case 0:
                    dx = 1;
                    dy = 1;
                    break;
                case 1:
                    dx = 1;
                    dy = -1;
                    break;
                case 2:
                    dx = -1;
                    dy = -1;
                    break;
                case 3:
                    dx = -1;
                    dy = 1;
                    break;
                }
                Square current = {.row = square.row + dy, .col = square.col + dx};
                while(true){
                    if(!board.squareInBounds(current)) break;
                    Piece hitPiece = board.getPiece(current);
                    if(hitPiece.type != Empty){
                        if(!colorCanCapturePiece(piece.color, hitPiece)) break; //Hit a piece that cannot be captured, break

                        if(func(current) == BreakMoveIteration) return; //Hit a piece that can be captured, add move then break
                        break;
                    }
                    if(func(current) == BreakMoveIteration) return; //Didn't hit a piece, continue
                    current.col += dx;
                    current.row += dy;
                }
            }
        }
        if(piece.type == Rook || piece.type == Queen){
            for(unsigned short dir = 0; dir < 4; dir++){
                short dx;
                short dy;
                switch (dir)
                {
                case 0:
                    dx = 1;
                    dy = 0;
                    break;
                case 1:
                    dx = 0;
                    dy = -1;
                    break;
                case 2:
                    dx = -1;
                    dy = 0;
                    break;
                case 3:
                    dx = 0;
                    dy = 1;
                    break;
                }
                Square current = {.row = square.row + dy, .col = square.col + dx};
                while(true){
                    if(!board.squareInBounds(current)) break;
                    Piece hitPiece = board.getPiece(current);
                    if(hitPiece.type != Empty){
                        if(!colorCanCapturePiece(piece.color, hitPiece)) break; //Hit a piece that cannot be captured, break

                        if(func(current) == BreakMoveIteration) return; //Hit a piece that can be captured, add move then break
                        break;
                    }
                    if(func(current) == BreakMoveIteration) return; //Didn't hit a piece, continue
                    current.col += dx;
                    current.row += dy;
                }
            }
        }
        if(piece.type == Pawn){
            Square advance_square;
            Square double_advance_square;
            Square take_left_square;
            Square take_right_square;
            switch (piece.color)
            {
            case White:
                advance_square = {.row = square.row + 1, .col = square.col};
                double_advance_square = {.row = square.row + 2, .col = square.col};
                take_left_square = {.row = square.row + 1, .col = square.col - 1};
                take_right_square = {.row = square.row + 1, .col = square.col + 1};
                break;
            case Black:
                advance_square = {.row = square.row - 1, .col = square.col};
                double_advance_square = {.row = square.row - 2, .col = square.col};
                take_left_square = {.row = square.row - 1, .col = square.col - 1};
                take_right_square = {.row = square.row - 1, .col = square.col + 1};
                break;
            }

            if(board.squareInBounds(advance_square) && board.getPiece(advance_square).type == Empty){
                if(func(advance_square) == BreakMoveIteration) return;
                if(board.squareInBounds(double_advance_square) && board.getPiece(double_advance_square).type == Empty){
                    if(func(double_advance_square) == BreakMoveIteration) return;
                }
            }
            //TODO: Add en passant
            if(
                board.squareInBounds(take_left_square) &&
                board.getPiece(take_left_square).type != Empty &&
                colorCanCapturePiece(piece.color, board.getPiece(take_left_square))
                ){
                    if(func(take_left_square) == BreakMoveIteration) return;
                }
            if(
                board.squareInBounds(take_right_square) &&
                board.getPiece(take_right_square).type != Empty &&
                colorCanCapturePiece(piece.color, board.getPiece(take_right_square))
                ){
                    if(func(take_right_square) == BreakMoveIteration) return;
                }
        }
    }
    void Position::iterateAllPossibleMoves(const std::function<MoveIterationResult(const Move)> func){
        for(unsigned short row = 0; row < board.getNumRows(); row++){
            for(unsigned short col = 0; col < board.getNumCols(); col++){
                Square square = {.row = row, .col = col};
                iteratePossibleMovesFromSquare(square, [&func, &square](const Square s2) -> MoveIterationResult{
                    Move move = {.from = square, .to = s2};
                    return func(move);
                });
            }
        }
    }
    void Position::setNextToMove(){
        if(to_move == White){
            to_move = Black;
            return;
        }
        to_move = White;
    }
    bool Position::squareIsOnPromotionRank(Square square){
        if(to_move == White){
            return square.row == 7;
        }
        return square.row == 0;
    }
    void Position::playMoveNoConfirm(Move move, PieceType pawn_promotion){
        Piece piece = board.getPiece(move.from);
        board.setPiece(move.to, piece);
        board.setPiece(move.from, EmptyPiece);
        if(piece.type == Pawn && squareIsOnPromotionRank(move.to)){
            piece.type = pawn_promotion;
            board.setPiece(move.to, piece);
        }
        setNextToMove();
    }
    bool Position::isCheck(){
        Position pos_copy(*this);
        pos_copy.setNextToMove();
        bool foundKingCapture = false;
        pos_copy.iterateAllPossibleMoves([&pos_copy, &foundKingCapture](const Move move) -> MoveIterationResult{
            if(pos_copy.getBoard().getPiece(move.to).type == King){
                foundKingCapture = true;
                return BreakMoveIteration;
            }
            return ContinueMoveIteration;
        });
        return foundKingCapture;
    }
    bool Position::movesIntoCheck(Move move){
        Position pos_copy(*this);
        pos_copy.playMoveNoConfirm(move, Queen); //Promotion piece is irrelevant here
        bool foundKingCapture = false;
        pos_copy.iterateAllPossibleMoves([&pos_copy, &foundKingCapture](const Move move) -> MoveIterationResult{
            if(pos_copy.getBoard().getPiece(move.to).type == King){
                foundKingCapture = true;
                return BreakMoveIteration;
            }
            return ContinueMoveIteration;
        });
        return foundKingCapture;
    }
    Square Position::findKing(Color color){
        for(unsigned short row = 0; row < board.getNumRows(); row++){
            for(unsigned short col = 0; col < board.getNumCols(); col++){
                Square square = {.row = row, .col = col};
                Piece piece = board.getPiece(square);
                if(piece.type == King && piece.color == color){
                    return square;
                }
            }
        }
        return EmptySquare;
    }

    bool Position::isMoveLegal(Move move){
        bool isMovePossible = false;
        iteratePossibleMovesFromSquare(move.from, [&move, &isMovePossible](const Square to) -> MoveIterationResult{
            if(to == move.to){
                isMovePossible = true;
                return BreakMoveIteration;
            }
            return ContinueMoveIteration;
        });
        return (!movesIntoCheck(move)) && isMovePossible;
    }
    void Position::iterateLegalMovesFromSquare(Square square, const std::function<MoveIterationResult(const Square)> func){
        iteratePossibleMovesFromSquare(square, [this, &square, &func](const Square s2) -> MoveIterationResult{
            Move move = {.from = square, .to = s2};
            if(isMoveLegal(move)){
                return func(s2);
            }
            return internal::ContinueMoveIteration;
        });
    }
    void Position::iterateAllLegalMoves(const std::function<internal::MoveIterationResult(const Move)> func){
        for(unsigned short row = 0; row < board.getNumRows(); row++){
            for(unsigned short col = 0; col < board.getNumCols(); col++){
                Square square = {.row = row, .col = col};
                iterateLegalMovesFromSquare(square, [&func, &square](const Square s2) -> MoveIterationResult{
                    Move move = {.from = square, .to = s2};
                    return func(move);
                });
            }
        }
    }
    void Position::playMove(Move move, PieceType pawn_promotion){
        if(!isMoveLegal(move)){
            throw "Illegal move!";
        }
        playMoveNoConfirm(move, pawn_promotion);
        last_move = move;
    }
    PositionState Position::getState(){
        unsigned int num_moves = 0;
        iterateAllLegalMoves([&num_moves](const Move move __attribute__((unused))) -> MoveIterationResult{
            num_moves++;
            return ContinueMoveIteration;
        });
        bool check = isCheck();
        if((check && num_moves == 0) || (findKing(to_move) == EmptySquare)){
            return Checkmate;
        }
        if(check){
            return Check;
        }
        if(num_moves == 0){
            return Stalemate;
        }
        return Normal;
    }
}
