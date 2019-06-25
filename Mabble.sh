#!/bin/bash

#Run the game

g++ Main.cpp Eval.cpp RoundedRectangle.cpp TileBag.cpp Player.cpp Board.cpp BoardTile.cpp CheckButton.cpp Tile.cpp TileRack.cpp LinkedList.cpp -lsfml-graphics -lsfml-window -lsfml-system -o Mabble;
#./Mabble