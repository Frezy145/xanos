
#include "Text.h"
#include <MCUFRIEND_kbv.h>
#include <Arduino.h>
#include <stdint.h>

extern MCUFRIEND_kbv tft;

Text::Text(
    int xPos, 
    int yPos, 
    String txt,
    uint16_t txtColor,
    int txtSize,
    int pad,

    bool border,
    uint16_t borderColor,
    int borderRadious,
    bool fill,
    uint16_t backgroundColor
) 
  : UnClickable(xPos, yPos, txt.length()*txtSize*6+pad*2, txtSize*10+pad*2, border, borderColor, borderRadious, fill, backgroundColor), 
  text(txt), textSize(txtSize), textColor(txtColor), x(xPos+pad+txtSize), y(yPos+pad+txtSize) {}

void Text::render() {
    UnClickable::render();
    tft.setCursor(x, y);
    tft.setTextColor(textColor);
    tft.setTextSize(textSize);
    tft.print(text);
}

void Text::update(String newText) {
    text = newText;
    UnClickable::update();
    render();
}
