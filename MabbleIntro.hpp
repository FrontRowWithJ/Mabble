#ifndef MABBLEINTRO_H
#define MABBLE_INTRO_H
#include "Util.hpp"
#include "RoundedRectangle.hpp"

#ifndef OFFSET_DIVISOR
#define OFFSET_DIVISOR 10000
#endif
#ifndef OFFSET
#define OFFSET (2 * M_PI / OFFSET_DIVISOR)
#endif

#define LOWEST ((M_PI + M_PI_2) / OFFSET)
#define HIGHEST (M_PI / OFFSET)
class MabbleIntro
{
private:
  typedef enum
  {
    NEITHER,
    FADE_IN,
    FADE_OUT
  } Fade;

  typedef enum
  {
    NONE,
    SINE,
    UP,
    DOWN
  } Movement;

private:
  const Color softRed = Color(237, 94, 104);
  float yOffset;
  RoundedRectangle *icons;
  int numberOfIcons;
  string logo;
  Text *iconText;
  float xPos;
  float yPos;
  float iconWidth;
  float iconHeight;
  float iconRadius;
  float gap;
  float *baseY;
  Color bgColor;
  Color fgColor;
  Color textColor;
  Font font;
  float seconds;
  bool isFading;
  Fade f;
  Movement movement;
  float amplitude;
  bool isWave;
  float alpha;
  bool *canMoveStraight;
  int *cycle;
  RoundedRectangle *startButton;
  Text *startButtonText;
  float sbXPos;
  float sbYPos;

public:
  MabbleIntro(float xPos, float yPos, float gap, float iconWidth, float iconHeight, float iconRadius, Color bgColor, Color textColor, Font font);
  void draw(RenderWindow *window);
  void fade(bool isFadingIn);
  void set_opacity(byte_t alpha);
  void set_movement_to_wave();
  void set_startButtonPosition(float xPos, float yPos);
  void on_mouse_over(float mouseX, float mouseY, float screenX, float screenY);
  void activate_logo(float mouseX, float mouseY, float screenX, float screenY);
  void gen_startButton(float xPos, float yPos);
  static Vector2f translate_to_screen(float mouseX, float mouseY, float screenX, float screenY);

private:
  void gen_icon_box();
  void gen_icon_text();
  void move_as_wave();
  void move_straight();
  void fade(Fade fade);
  void revert_startButton();
  void change_startButton();
  void set_text_position(Text *text, RoundedRectangle *rect);
  void set_movement_to_straight(Movement direction);
};
#endif
