#include "Button.h"
#include <Arduino.h>
#include <stdint.h>
#include <MCUFRIEND_kbv.h>

extern MCUFRIEND_kbv tft;

Button::Button(
    int xPos,
    int yPos,
    String text,
    uint16_t textColor,
    int textSize,
    int padding,
    bool border,
    uint16_t borderColor,
    int borderRadious,
    bool fill,
    uint16_t backgroundColor,
    bool enabled,
    Callback cb
) : Clickable(
    xPos,
    yPos,
    text.length()*textSize*6+padding*2,
    textSize*10+padding*2,
    border,
    borderColor,
    borderRadious,
    fill,
    backgroundColor,
    enabled,
    cb
), x(xPos+padding+textSize), y(yPos+padding+textSize), text(text), textSize(textSize), textColor(textColor) {}

void Button::render(){
    Clickable::render();
    tft.setCursor(x, y);
    tft.setTextColor(textColor);
    tft.setTextSize(textSize);
    tft.print(text);
}

void Button::update(String text){
    text = text;
    render();
    Clickable::update();
}