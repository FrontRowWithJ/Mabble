#include "Player.hpp"


//properties of player:
// ? indicates if this property isn't certain
// ? boolean isTurn
// ? number of turns
// ? number of pieces left
//current set of pieces (operands and operators)
//score
//successful equations

//note: If the player's turn is verified to be successful then we need to make sure that we don't
//give the user additional points for valid equations that were adjacent to the equation that the user has created
// and already existed.

LinkedList Player::getPlacedPieces()
{
    LinkedList result = LinkedList();
    for (int i = 0; i < PIECE_COUNT; i++)
        if (currentPieces[i].isPlaced)
            result.insert((void *)&currentPieces[i]);
    return result;
}