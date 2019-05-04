#ifndef PLAYER_H
#define PLAYER_H

#include "Util.hpp"
#include "Board.hpp"
#include "TileRack.hpp"
#include "TileBag.hpp"

#define PIECE_COUNT 10
#define TOTAL_PIECES 40

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

class Player
{
private:
	class ScoreBoard
	{
	private:
		float xPos;
		float yPos;
		float width;
		float height;
		long score;
		Text scoreText;
		Font font;
		RectangleShape *visuals;
		Color bgColor;
		Color textColor;
		int numOfVisuals;

	public:
		ScoreBoard(float xPos, float yPos, float width, float height, Font font);
		void update_score_board(long score);
		void draw(RenderWindow *window);
		static char *ltoa(long num);

	private:
		void gen_visuals();
		void gen_text();
	};

private:
	float xPos;
	float yPos;
	float width;
	float height;
	float fgScale;
	bool isTurn;
	int numOfTurns;
	long score;
	TileBag *tileBag;
	TileRack *tileRack;
	string playerName;
	Font font;
	Text nameText;
	Text scoreText;
	ScoreBoard *sb;

public:
	Player();
	Player(float xPos, float yPos, float width, float height, float fgScale, string playerName, Font font, bool isTurn);
	void draw(RenderWindow *window);
	void update_tileRack();
	void update_score(long points);
	TileRack *get_tile_rack();
	void switch_turn();
	Tile *select_tile(float mouseX, float mouseY, float screenX, float screenY);
	bool deselect_tile(float mouseX, float mouseY, float screenX, float screenY);
	float get_xPos();
	float get_yPos();
	float get_width();
	float get_height();
};
#endif