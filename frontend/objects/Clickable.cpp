#include "Clickable.h"

Clickable::Clickable(int xPos, int yPos, int w, int h, uint16_t col) 
  : x(xPos), y(yPos), width(w), height(h), color(col) {}

bool Clickable::isClicked(int touchX, int touchY) {
  return (touchX >= x && touchX <= (x + width) && 
          touchY >= y && touchY <= (y + height));
}

void Clickable::onClick( 
  void (*toBack)(std::string *agrs),
  void (*toFront)(std::string *args)
) {

    if (toFront != nullptr) {
        toFront(&frontAction);
    }

    if (toBack != nullptr) {
        toBack(&backAction);
    }
}
