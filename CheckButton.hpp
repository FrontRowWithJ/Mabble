#ifndef CHECKBUTTON_H
#define CHECKBUTTON_H

#include "Util.hpp"
#include "Board.hpp"
#include "Eval.hpp"
#include "Player.hpp"
#include "RoundedRectangle.hpp"
#include "LinkedList.hpp"
#define MAX_NUMBER_OF_TURNS 10
#define GET_ORIGIN(X) \
	lb.left - X->get_xPos() - (X->get_width() - lb.width) / 2, lb.top - X->get_yPos() - (X->get_height() - lb.height) / 2

class CheckButton
{
  public:
	typedef enum
	{
		DOWN,
		RIGHT,
		NEITHER,
		UNKOWN, //? This is the case when only one piece is positioned.
				//? The only thing we need to check is if the piece isn't isolated
	} Direction;

	typedef struct
	{
		int i;
		int j;
	} Position;

	typedef struct MathEquation
	{
		int startI;
		int startJ;
		Direction dir;
		string value;
		bool operator==(struct MathEquation e);
	} Equation;

  private:
	float width;
	float height;
	float xPos;
	float yPos;
	int turnsPassed;
	Color bgColor = Color::White;
	Color fgColor = Color::Black;
	Font font;
	Text text;
	Color textColor = Color::White;
	int numOfVisuals;
	RectangleShape *visuals;
	LinkedList<Equation> *knownEquations;
	RoundedRectangle *turnLable;
	Text turnText;
	bool isWinnerKnown;
	RoundedRectangle *winnerBoard;
	Text winnerText;

  public:
	CheckButton();
	CheckButton(float width, float height, float xPos, float yPos, Font font, float turnXPos, float turnYPos);
	void check(float mousePosX, float mousePosY, float screenPosX, float screenPosY, Board mabbleBoard, LinkedList<TileData> *placedTiles, Player *playerOne, Player *playerTwo, bool *isPlayerOne, float screenWidth, float screenHeight); //this function needs to be more elaborated
	void gen_visuals(float turnXPos, float turnYPos);
	void gen_text(float turnXPos, float turnYPos);
	void draw(RenderWindow *window);
	void move_turnLable(float xPos, float yPos);
	static int compare_right(TileData left, TileData right);
	static int compare_down(TileData left, TileData right);
	static int compare_equation(void *a, void *b);
	static char *to_string(void *a);
	
  private:
	Direction is_same_line(LinkedList<TileData> *placedTiles, BoardTile ***table);
	bool is_isolated(TileData *td, BoardTile ***table, int width);
	bool are_tiles_contiguous(Direction d, BoardTile ***table, LinkedList<TileData> *placedTiles, int width);
	LinkedList<CheckButton::Equation> *gen_equation_list(BoardTile ***table, int width, LinkedList<TileData> *placedTiles);
	Position get_equation_begin_pos(Direction d, BoardTile ***table, int i, int j);
	Equation *gen_equation(BoardTile ***table, int width, Direction d, int i, int j);
	void filter_equation_list(LinkedList<Equation> *equationList);
	string gen_incorrect_statement_string(LinkedList<Equation> *equations);
	void set_to_cant_remove(LinkedList<TileData> *placedTiles, BoardTile ***table);
	evalResult_t *check_structure(LinkedList<Equation> *equations, int *len);
	bool are_equation_structure_valid(evalResult_t *resultCodes, int len);
	LinkedList<CheckButton::Equation> *split_list(LinkedList<Equation> *equations, evalResult_t *resultCodes, evalResult_t code);				   //? I dont know full if this works with many equaions
	evalResult_t *evaluate_equations(LinkedList<Equation> *equations, long *totalScore, int *len);
	bool are_equations_balanced(evalResult_t *resultCodes, int len);
	void check_player(LinkedList<TileData> *placedTiles, Board *board, Player *player1, Player *player2, bool *isPlayerOne); //!
	//? Checks the player's attempt
	//? Should take a Player object as an argument.
	//? Unsure of the return type
	bool are_tiles_connected(LinkedList<TileData> *placedTiles, BoardTile ***table, int width);
	bool is_tile_positioned_correctly(TileData *td, BoardTile ***table, int width);
	void add_to_known_equations(LinkedList<CheckButton::Equation> *equations);
	void pass_turn();
	bool is_game_over();
	void show_winner(Player *p1, Player *p2, float screenWidth, float screenHeight);
};
#endif