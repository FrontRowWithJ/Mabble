#include "PointChecker.h"
//compare 2 lists of "Lines"
// in the new list, compare them to an established list of positions
// this established list contains all the start positions and their corresponding direction for all Lines
// If a Line in the new List has the same position in the established list then wh check if it has the same length
// if the lengths are the same then that means no changes has been made to the string
// If the lengths different then that could be a potentially new string
// I then check if the Line is valid
// If the line is valid then the player gets a number equal after the equal sign
// otherwise, the user is prompted to correct his/her mistakes
//

void scorePoints(Line *boardLines, size_t boardLineLen, Line *playerLines, size_t playerLineLen, double *player_score)
{
    for (int i = 0; i < playerLineLen; i++)
    {
        for (int j = 0; j < boardLineLen; j++)
        {
            if (IS_BOARD_POS_EQUAL(playerLines[i], boardLines[j]))
            {
                if (playerLines[i].len != boardLines[j].len)
                {
                    byte_t code;
                    long result; //store the result of evaluate in here if the value is correct
                    evaluate(playerLines[i].value, &code);
                    if (code == EVAL_SUCCESS)
                    {
                        // *player_score += points;
                    } else {
                        //tell player where he/she may have oofed!

                        
                    }
                }
                break;
            }
        }
    }
}