#ifndef POINTCHECKER_H
#define POINTCHECKER_H

#ifndef UTIL_H
#include "Util.hpp"
#endif

#ifndef BOARD_H
#include "Board.hpp"
#endif

#ifndef EVAL_H
#include "Eval.hpp"
#endif

class PointChecker
{
  public:
    void score_points(Board::Equation *boardLines, size_t boardLineLen, Board::Equation *playerLines, size_t playerLineLen, long *player_score);
};

#endif