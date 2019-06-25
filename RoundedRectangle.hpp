#ifndef ROUNDEDRECTANGLESHAPE_H
#define ROUNDEDRECTANGLESHAPE_H

#include "Util.hpp"
using namespace vector_op;

//This is a class that will define the behaviour of a rectangle with rounded edges
/*            a  
        /‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾\    
        |           |
      b |           | d
        |           |
        \___________/
              c    
*/

class RoundedRectangle : public ConvexShape
{
private:
  float width;
  float height;
  float originalWidth;
  float originalHeight;
  float radiusA;
  float radiusB;
  float radiusC;
  float radiusD;
  bool isRadiusAZero;
  bool isRadiusBZero;
  bool isRadiusCZero;
  bool isRadiusDZero;
  Color fillColor;
  Color outlineColor;
  int pointCount; //This only applies to the curved part of the rectangle
  ConvexShape shadow;
  bool isShadowPresent;
  float shadowWidth;
  Vector2f pos;

public:
  using ConvexShape::ConvexShape;
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
  void set_radiusA_to_zero();
  void set_radiusB_to_zero();
  void set_radiusC_to_zero();
  void set_radiusD_to_zero();
  float set_position(float xPos, float yPos);
  void gen_shadow(float width);
  void set_size(float width, float height);
  void set_thickness(float thickness);
  float get_width();
  float get_height();
  Vector2f get_size();

private:
  void gen_shape();
  Vector2f *gen_curve(Vector2f centrePos, double curveStart, double radius);
  void set_shadow_color();
  void set_radius(Vector2f centrePos, int quadrantPos, float radius);
};
#endif