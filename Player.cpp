#include "Player.hpp"

Player::Player()
{
}

Player::Player(float xPos, float yPos, float width, float height, float fgScale, string playerName, const char *fontName, bool isTurn)
{
    this->xPos = xPos;
    this->yPos = yPos;
    this->width = width;
    this->height = height;
    this->fgScale = fgScale;
    this->playerName = playerName;
    this->isTurn = isTurn;
    this->numOfTurns = 0;
    this->score = 0;
    auto _time = chrono::steady_clock::now();
    tileBag = new TileBag(TOTAL_PIECES, chrono::duration_cast<chrono::nanoseconds>(_time.time_since_epoch()).count());
    tileRack = new TileRack(xPos, yPos, width, height, fgScale);
    sb = new Player::ScoreBoard(xPos + width - height, yPos, height, height, fontName);
    char *tiles = new char[NUM_OF_TILES + 1]();
    int i = 0;
    for (; i < NUM_OF_TILES - 5; i++)
        tiles[i] = tileBag->get_tile();
    strcat(tiles, "+-*/=");
    tileRack->gen_visuals();
    tileRack->gen_tiles(tiles, fontName);
}

void Player::update_tileRack()
{
    tileRack->reset_TileRack_Position();
    for (int i = 0; i < NUM_OF_TILES; i++)
        tileRack->update_tile(i, tileBag->get_tile(), tileBag->is_empty());
}

void Player::update_score(long points)
{
    score += points;
    sb->update_score_board(points);
}

void Player::draw(RenderWindow *window, Vector2f mousePos, Vector2f screenPos)
{
    //? more things are gonna need to be drawn over time
    tileRack->draw(window, mousePos, screenPos);
    sb->draw(window);
}

TileRack *Player::get_tile_rack()
{
    return tileRack;
}

Player::ScoreBoard::ScoreBoard(float xPos, float yPos, float width, float height, const char *fontName)
{
    this->xPos = xPos;
    this->yPos = yPos;
    this->width = width;
    this->height = height;
    this->score = 0;
    this->bgColor = Color::Black;
    this->textColor = Color::White;
    this->numOfVisuals = 0;
    this->font.loadFromFile(fontName);
    gen_visuals();
    gen_text(fontName);
}

void Player::ScoreBoard::gen_visuals()
{
    numOfVisuals++;
    RectangleShape bg = RectangleShape(Vector2f(width, height));
    bg.setFillColor(bgColor);
    bg.setPosition(Vector2f(xPos, yPos));
    visuals = new RectangleShape[numOfVisuals];
    visuals[0] = bg;
}

void Player::ScoreBoard::gen_text(const char *fontName)
{
    scoreText = Text("0", font, width);
    scoreText.setFillColor(textColor);
    FloatRect lb = scoreText.getLocalBounds();
    scoreText.setOrigin(lb.left - xPos - (width - lb.width) / 2.f, lb.top - yPos - (height - lb.height) / 2.f);
}

void Player::ScoreBoard::draw(RenderWindow *window)
{
    for (int i = 0; i < numOfVisuals; i++)
        window->draw(visuals[i]);
    window->draw(scoreText);
}

void Player::ScoreBoard::update_score_board(long score)
{
    this->score += score;
    char *scoreInAscii = ltoa(this->score);
    scoreText.setString(scoreInAscii);
    FloatRect lb = scoreText.getLocalBounds();
    scoreText.setOrigin(lb.left - xPos - (width - lb.width) / 2.f, lb.top - yPos - (width - lb.height) / 2.f);
}

char *Player::ScoreBoard::ltoa(long num)
{
    if (num == 0)
        return new char[2]{'0', '\0'};
    int n = 0;
    int len = 0;
    while (num != 0)
    {
        len++;
        n *= 10;
        n += num % 10;
        num /= 10;
    }
    char *result = new char[len + 1]();
    for (int i = 0; i < len; i++)
    {
        result[i] = (n % 10) + CHARACTER_OFFSET;
        n /= 10;
    }
    return result;
}

void Player::switch_turn()
{
    isTurn = !isTurn;
}

Tile *Player::select_tile(Vector2f mousePos, Vector2f screenPos)
{
    if (isTurn)
        return tileRack->select_tile(mousePos, screenPos);
    return NULL;
}

float Player::get_xPos()
{
    return xPos;
}

float Player::get_yPos()
{
    return yPos;
}

float Player::get_width()
{
    return width;
}

float Player::get_height()
{
    return height;
}

long Player::get_score()
{
    return score;
}

string Player::get_playerName()
{
    return playerName;
}

void Player::snap_tile_to_board(Board *gameBoard, LinkedList<TileData> *placedTiles)
{
    if (isTurn)
        tileRack->snap_to_board(gameBoard, placedTiles);
}