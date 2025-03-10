#include "Clickable.h"
#include <MCUFRIEND_kbv.h>
#include <Arduino.h>
#include <stdint.h>

extern MCUFRIEND_kbv tft;

Clickable::Clickable(
    int xPos,
    int yPos,
    int w,
    int h,
    bool border,
    uint16_t borderColor,
    int borderRadious,
    bool fill,
    uint16_t backgroundColor,
    bool enabled,
    Callback cb
) : x(xPos), y(yPos), width(w), height(h), border(border), borderColor(borderColor), borderRadious(borderRadious), fill(fill), backgroundColor(backgroundColor), enabled(enabled), callback(cb) {}

void Clickable::render() {
    if (border) {
        tft.drawRoundRect(x, y, width, height, borderRadious, borderColor);
    }
    if (fill && borderRadious == 0) {
        tft.fillRect(x+1, y+1, width-2, height-2, backgroundColor);
    }else if (fill && borderRadious > 0) {
        tft.fillRoundRect(x+1, y+1, width-2, height-2, borderRadious, backgroundColor);
    }
}

void Clickable::update() {
    render();
}

void Clickable::setBackgroundColor(uint16_t backgroundColor) {
    this->backgroundColor = backgroundColor;
}

void Clickable::setBorderColor(uint16_t borderColor) {
    this->borderColor = borderColor;
}

void Clickable::setBorder(bool border) {
    this->border = border;
}

void Clickable::setEnabled(bool enabled) {
    this->enabled = enabled;
}

void Clickable::setOnClick(Callback cb) {
    this->callback = cb;
}

void Clickable::setX(int x) {
    this->x = x;
}

void Clickable::setY(int y) {
    this->y = y;
}

void Clickable::click() {
    if (enabled && callback) {
        callback();
    }
}

bool Clickable::contains(int x, int y) {
    return (x >= this->x && x <= this->x + width && y >= this->y && y <= this->y + height);
}
