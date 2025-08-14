#include "cs225/HSLAPixel.h"
#include "../Point.h"

#include "ColorPicker.h"
#include "MyColorPicker.h"
#include <cstdlib> 
using namespace cs225;

/**
 * Picks the color for pixel (x, y).
 * Using your own algorithm
 */
HSLAPixel MyColorPicker::getColor(unsigned x, unsigned y) {
  /* @todo [Part 3] */

  //Illini picker
  double hue;
  if(rand() % 2 == 0){
    hue = 11;
  }else{
    hue = 216;
  }
  HSLAPixel pixel(hue, 1, 0.5);
  return pixel;
}
