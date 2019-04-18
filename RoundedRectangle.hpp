#ifndef ROUNDEDRECTANGLESHAPE_H
#define ROUNDEDRECTANGLESHAPE_H

#ifndef UTIL_H
#include "Util.hpp"
#endif

//This is a class that will define the behaviour of a rectangle with rounded edges
/*            a  
        /-----------\    
        |           |
      b |           | d
        |           |
        \___________/
              c    
*/

class RoundedRectangle
{
private:
  float xPos;
  float yPos;
  float width;
  float height;
  float radius;
  Color fillColor;
  Color outlineColor;
  int pointCount; //This only applies to the curved part of the rectangle
  int numOfCoords;
  //? These coordinates relate to the beginning and end points of the straight parts of the rectangle
  Vertex aStart;
  Vertex aEnd;
  Vertex bStart;
  Vertex bEnd;
  Vertex cStart;
  Vertex cEnd;
  Vertex dStart;
  Vertex dEnd;
  vector<Vertex> roundedRect;
  RectangleShape r1;
  RectangleShape r2;
  CircleShape *circles = new CircleShape[4];

public:
  RoundedRectangle();
  RoundedRectangle(float xPos, float yPos, float width, float height, float radius, int pointCount);
  void draw(RenderWindow *window);
  void set_fill_color(Color fillColor);
  Color get_fill_color();
  void set_outline_color(Color outlineColor);
  Color get_outline_color();
  int get_point_count();

private:
  void gen_shape();
  Vertex *gen_curve(double centreX, double centreY, double curveStart);
  void copy_to_shape(Vertex *vertices);
};
#endif