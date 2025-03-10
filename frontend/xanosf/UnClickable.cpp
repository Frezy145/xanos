#include "UnClickable.h"
#include <MCUFRIEND_kbv.h>

#include <Arduino.h>
#include <stdint.h>

extern MCUFRIEND_kbv tft;

UnClickable::UnClickable(
    int xPos, 
    int yPos, 
    int w, 
    int h,
    bool border,
    uint16_t borderColor,
    int borderRadious,
    bool fill,
    uint16_t backgroundColor
) 
  : x(xPos), y(yPos), width(w), height(h), border(border), borderColor(borderColor), borderRadious(borderRadious), fill(fill), backgroundColor(backgroundColor) {}

void UnClickable::render() {
    if (border) {
        tft.drawRoundRect(x, y, width, height, borderRadious, borderColor);
    }
    if (fill && borderRadious == 0) {
        tft.fillRect(x+1, y+1, width-2, height-2, backgroundColor);
    }else if (fill && borderRadious > 0) {
        tft.fillRoundRect(x+1, y+1, width-2, height-2, borderRadious, backgroundColor);
    }
}

void UnClickable::update() {
    render();
}

void UnClickable::setColor(uint16_t color) {
    backgroundColor = color;
}

void UnClickable::setX(int xPos) {
    x = xPos;
}

void UnClickable::setY(int yPos) {
    y = yPos;
}

void UnClickable::setWidth(int w) {
    width = w;
}

void UnClickable::setHeight(int h) {
    height = h;
}

void UnClickable::setDimensions(int xPos, int yPos, int w, int h) {
    x = xPos;
    y = yPos;
    width = w;
    height = h;
}
