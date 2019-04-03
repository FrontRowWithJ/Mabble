#include "PointChecker.hpp"
//compare 2 lists of "Lines"
// in the new list, compare them to an established list of positions
// this established list contains all the start positions and their corresponding direction for all Lines
// If a Equation in the new List has the same position in the established list then wh check if it has the same length
// if the lengths are the same then that means no changes has been made to the string
// If the lengths different then that could be a potentially new string
// I then check if the Equation is valid
// If the line is valid then the player gets a number equal after the equal sign
// otherwise, the user is prompted to correct his/her mistakes
//

void PointChecker::score_points(Board::Equation *boardLines, size_t boardLineLen, Board::Equation *playerLines, size_t playerLineLen, long *player_score)
{
    for (int i = 0; i < playerLineLen; i++)
    {
        for (int j = 0; j < boardLineLen; j++)
        {
            if (IS_BOARD_POS_EQUAL(playerLines[i], boardLines[j]))
            {
                if (playerLines[i].value.length() != boardLines[j].value.length())
                {
                    evalResult_t code;
                    long points = evaluate(playerLines[i].value, &code);
                    if (code == EVAL_SUCCESS)
                    {
                        *player_score += points;
                        printf("Good Job!");
                    }
                    else
                    {
                        
                        //tell player where he/she may have oofed!
                    }
                }
                break;
            }
        }
    }
}