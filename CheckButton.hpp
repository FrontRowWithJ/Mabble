#ifndef CHECKBUTTON_H
#define CHECKBUTTON_H

#ifndef UTIL_H
#include "Util.hpp"
#endif

#ifndef BOARD_H
#include "Board.hpp"
#endif

#ifndef EVAL_H
#include "Eval.hpp"
#endif

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

	typedef struct
	{
		int startI;
		int startJ;
		Direction dir;
		string value;
	} Equation;

  private:
	float width;
	float height;
	float xPos;
	float yPos;
	Color bgColor = Color::White;
	Color fgColor = Color::Black;
	Font font;
	Text text;
	Color textColor = Color::White;
	int numOfVisuals;
	RectangleShape *visuals;
	LinkedList *knownEquations;

  public:
	CheckButton();
	CheckButton(float width, float height, float xPos, float yPos, Font font);
	void check(float mousePosX, float mousePosY, float screenPosX, float screenPosY, Board mabbleBoard, LinkedList *placedTiles); //this function needs to be more elaborated
	void gen_visuals();
	void gen_text();
	void draw(RenderWindow *window);
	static int compare_right(void *a, void *b);
	static int compare_down(void *a, void *b);
	static int compare_equation(void *a, void *b);
	static char *to_string(void *a);

  private:
	Direction is_same_line(LinkedList *placedTiles, BoardTile ***table);
	bool is_isolated(TileData *td, BoardTile ***table, int width);
	bool are_tiles_contiguous(Direction d, BoardTile ***table, LinkedList *placedTiles, int width);
	LinkedList *gen_equation_list(BoardTile ***table, int width, LinkedList *placedTiles);
	Position get_equation_begin_pos(Direction d, BoardTile ***table, int i, int j);
	Equation *gen_equation(BoardTile ***table, int width, Direction d, int i, int j);
	void filter_equation_list(LinkedList *equationList); //!
	string gen_incorrect_statement_string(LinkedList *equations);
	void set_to_cant_remove(LinkedList *placedTiles, BoardTile ***table);
	evalResult_t *check_structure(LinkedList *equations, int *len);
	bool are_equation_structure_valid(evalResult_t *resultCodes, int len);
	evalResult_t *evaluate_equations(LinkedList *equations, long *totalScore, int *len);
	bool are_equations_balanced(evalResult_t *resultCodes, int len);
	LinkedList *split_list(LinkedList *equations, evalResult_t *resultCodes, evalResult_t code); //? I dont know full if this works with many equaions
	void check_player(LinkedList *placedTiles, Board *board);		 //!
	//? Checks the player's attempt
	//? Should take a Player object as an argument.
	//? Unsure of the return type
	bool are_tiles_connected(LinkedList *placedTiles, BoardTile ***table, int width);
	bool is_tile_positioned_correctly(TileData *td, BoardTile ***table, int width);
	void add_to_known_equations(LinkedList *equations);
};
#endif