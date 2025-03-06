#ifndef CLICKABLE_H
#define CLICKABLE_H

#include <cstdint>
#include <string>

class Clickable {
  private:
    int x; // X position
    int y; // Y position
    int width; // Width of the clickable area
    int height; // Height of the clickable area
    uint16_t color; // Color of the clickable object
    std::string backAction;
    std::string frontAction;



  public:
    Clickable(int xPos, int yPos, int w, int h, uint16_t col) 
      : x(xPos), y(yPos), width(w), height(h), color(col) {}

    // Method to check if a point is within the clickable area
    bool isClicked(int touchX, int touchY) {
      return (touchX >= x && touchX <= (x + width) && 
              touchY >= y && touchY <= (y + height));
    }

    // Method to render the clickable object
    void render() {
      // Code to draw the clickable object on the screen
      // For example: tft.fillRect(x, y, width, height, color);
    }

    // Method to handle click events
    virtual void onClick( 
      // Function pointers (take arguments) to handle the back and front 

      void (*toBack)(std::string *agrs) = nullptr,
      void (*toFront)(std::string *args) = nullptr
    ) {
    }

    # define contains(x, y) isClicked(x, y)

    void setColor(uint16_t col) {
      color = col;
    }

};

#endif // CLICKABLE_H