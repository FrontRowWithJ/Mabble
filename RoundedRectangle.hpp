#ifndef ROUNDEDRECTANGLESHAPE_H
#define ROUNDEDRECTANGLESHAPE_H

#include "Util.hpp"

//This is a class that will define the behaviour of a rectangle with rounded edges
/*            a  
        /‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾\    
        |           |
      b |           | d
        |           |
        \___________/
              c    
*/

static Vector2f operator+(Vector2f a, float offset)
{
  return Vector2f(a.x + offset, a.y + offset);
}

class RoundedRectangle
{
private:
  float xPos;
  float yPos;
  float width;
  float height;
  float originalWidth;
  float originalHeight;
  float radiusA;
  float radiusB;
  float radiusC;
  float radiusD;
  ConvexShape roundedRect;
  Color fillColor;
  Color outlineColor;
  int pointCount; //This only applies to the curved part of the rectangle
  ConvexShape shadow;
  bool isShadowPresent;
  float shadowWidth;

public:
  RoundedRectangle();
  RoundedRectangle(float xPos, float yPos, float width, float height, float radiusA, float radiusB, float radiusC, float radiusD, int pointCount);
  RoundedRectangle(float xPos, float yPos, float width, float height, float radius, int pointCount);
  RoundedRectangle(float xPos, float yPos, float width, float height, float radiusA, float radiusB, int pointCount);
  void draw(RenderWindow *window);
  void set_fill_color(Color fillColor);
  Color get_fill_color();
  void set_outline_color(Color outlineColor);
  Color get_outline_color();
  int get_point_count();
  void set_radiusA(float radiusA);
  void set_radiusB(float radiusB);
  void set_radiusC(float radiusC);
  void set_radiusD(float radiusD);
  float get_xPos();
  float get_yPos();
  float get_width();
  float get_height();
  float set_position(float xPos, float yPos);
  void gen_shadow(float width);
  void set_size(float width, float height);
  void set_thickness(float thickness);

private:
  void gen_shape();
  Vector2f *gen_curve(double centreX, double centreY, double curveStart, double radius);
  void set_shadow_color();
  void set_radius(float centreX, float centreY, int quadrantPos, float radius);
};
#endif