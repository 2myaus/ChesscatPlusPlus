#include "chesscat.hpp"

namespace chesscat{

    const Piece EmptyPiece = {.color = White, .type = Empty};
    const Square EmptySquare = {.row = -1, .col = -1};
    const Move EmptyMove = {.from = EmptySquare, .to = EmptySquare};

    Board::Board(unsigned short cols, unsigned short rows) : num_cols(0), num_rows(0)
    {
        resize(cols, rows);
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

    Position::Position() : board(8, 8), to_move(White), last_move(EmptyMove) {}
    Position::~Position() {}

    bool Position::colorCanCapturePiece(Color color, Piece captured){
        if(captured.type == Empty){
            return true;
        }
        if(captured.color == color){
            return false;
        }
        return true;
    }
    void Position::iteratePossibleMovesFromSquare(Square square, std::function<void(const Square)> func){
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

            if (board.squareInBounds(down_left)) func(down_left);
            if (board.squareInBounds(down)) func(down);
            if (board.squareInBounds(down_right)) func(down_right);
            if (board.squareInBounds(left)) func(left);
            if (board.squareInBounds(right)) func(right);
            if (board.squareInBounds(up_left)) func(up_left);
            if (board.squareInBounds(up)) func(up);
            if (board.squareInBounds(up_right)) func(up_right);
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

            if (board.squareInBounds(up_left)) func(up_left);
            if (board.squareInBounds(up_right)) func(up_right);

            if (board.squareInBounds(right_up)) func(right_up);
            if (board.squareInBounds(right_down)) func(right_down);

            if (board.squareInBounds(down_right)) func(down_right);
            if (board.squareInBounds(down_left)) func(down_left);

            if (board.squareInBounds(left_down)) func(left_down);
            if (board.squareInBounds(left_up)) func(left_up);
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

                        func(current); //Hit a piece that can be captured, add move then break
                        break;
                    }
                    func(current); //Didn't hit a piece, continue
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

                        func(current); //Hit a piece that can be captured, add move then break
                        break;
                    }
                    func(current); //Didn't hit a piece, continue
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
                func(advance_square);
                if(board.squareInBounds(double_advance_square) && board.getPiece(double_advance_square).type == Empty) func(double_advance_square);
            }
            if(
                board.squareInBounds(take_left_square) &&
                board.getPiece(take_left_square).type != Empty &&
                colorCanCapturePiece(piece.color, board.getPiece(take_left_square))
                ) func(take_left_square);
            if(
                board.squareInBounds(take_right_square) &&
                board.getPiece(take_right_square).type != Empty &&
                colorCanCapturePiece(piece.color, board.getPiece(take_right_square))
                ) func(take_right_square);
        }
    }
    Piece Position::getPiece(Square square){
        return board.getPiece(square);
    }
}
