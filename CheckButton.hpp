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

  public:
	CheckButton();
	CheckButton(float width, float height, float xPos, float yPos, Font font);
	void check(float mousePosX, float mousePosY, float screenPosX, float screenPosY, Board mabbleBoard); //this function needs to be more elaborated
	void gen_visuals();
	void gen_text();
	void draw(RenderWindow *window);
	static int compare_right(void *a, void *b);
	static int compare_down(void *a, void *b);
	static int compare_equation(void *a, void *b);

  private:
	Direction is_same_line(LinkedList *placedTiles, BoardTile **table);
	bool is_isolated(Board::TileData *td, BoardTile **table, int width);
	bool are_tiles_contiguous(Direction d, BoardTile **table, LinkedList *placedTiles, int width);
	LinkedList *gen_equation_list(BoardTile **table, int width, LinkedList *placedTiles, LinkedList *knownEquations);
	Position get_equation_begin_pos(Direction d, BoardTile **table, int i, int j);
	Equation *gen_equation(BoardTile **table, int width, Direction d, int i, int j);
	void filter_equation_list(LinkedList *equationList);
	string gen_incorrect_statement_string(LinkedList *equations);
	void set_to_cant_remove(LinkedList *placedTiles, BoardTile **table);
	evalResult_t *evaluate_equations(LinkedList *equations);
	bool are_equations_valid(evalResult_t *resultCodes, int len);
	LinkedList *split_list(LinkedList *equations, evalResult_t *resultCodes);
};
#endif