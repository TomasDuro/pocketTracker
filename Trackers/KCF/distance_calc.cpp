#include "distance_calc.hpp"

float horizontal_displacement = 0;
float current_dist = 2;
float init_vert_dist = 0;//meters

void distance_calc(int Ha)
{
  static int FirstTime = 1;
  float pi = 3.1415926535897932384626433832795028841971693993751058209749;
  float init_horiz_dist = 2;//meters
  float fov = 50;
  float horiz_pixels = 640;
  static float pixel_step;
  float current_half_angle;//deg
  //SO CHAMAR NA PRIMEIRA VEZ
  if (FirstTime)
  {
    pixel_step = fov/horiz_pixels;
    float box_angle_vert_half = pixel_step * Ha / 2;
    init_vert_dist = 2 * init_horiz_dist * tan (box_angle_vert_half * pi / 180);
    FirstTime = 0;
  }
  //O QUE E CHAMADO EM LOOP
  current_half_angle = (((float)Ha) / 2) * pixel_step;
  current_dist = (init_vert_dist / 2) / tanf(current_half_angle * pi / 180);
  horizontal_displacement = current_dist - init_horiz_dist;
return;
}
