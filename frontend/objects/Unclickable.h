#ifndef UNCLICKABLE_H
#define UNCLICKABLE_H

#include <cstdint>

class Unclickable {
    
    public:
        Unclickable(int x, int y, int width, int height, uint16_t color);
        void render();
        
    private:
        int x;
        int y;
        int width;
        int height;
        uint16_t color;

    inline Unclickable::Unclickable(int x, int y, int width, int height, uint16_t color){
        this->x = x;
        this->y = y;
        this->width = width;
        this->height = height;
        this->color = color;
    }

    void Unclickable::render(){
            // Code to draw the unclickable object on the screen
            // For example: tft.fillRect(x, y, width, height, color);
        }

    void Unclickable::update() {
        // Code to update the state of the unclickable object
        // This could include refreshing the display or changing properties
    }

    void Unclickable::setColor(uint16_t col) {
        color = col;
    }

    void Unclickable::setX(int xPos) {
        x = xPos;
    }

    void Unclickable::setY(int yPos) {
        y = yPos;
    }

    void Unclickable::setWidth(int w) {
        width = w;
    }

    void Unclickable::setHeight(int h) {
        height = h;
    }

    void Unclickable::setDimensions(int xPos, int yPos, int w, int h) {
        x = xPos;
        y = yPos;
        width = w;
        height = h;
    }

};

#endif // UNCLICKABLE_H