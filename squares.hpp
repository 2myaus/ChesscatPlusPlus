#ifndef SQUARES_HPP
#define SQUARES_HPP

namespace chesscat{
    struct Square
    {
        int row;
        int col;
    };

    struct Move
    {
        Square from;
        Square to;
    };
}

#endif
