#ifndef UNCLICKABLE_H
#define UNCLICKABLE_H

#include <Arduino.h>
#include <stdint.h>

class UnClickable {
    
    public:
        UnClickable(
            int xPos, 
            int yPos, 
            int w, 
            int h,
            bool border=false,
            uint16_t borderColor=0xFFFF,
            int borderRadious=0,
            bool fill=false,
            uint16_t backgroundColor=0x0000
        );

        virtual void render();
        virtual void update();
        void setColor(uint16_t);
        void setX(int xPos);
        void setY(int yPos);
        void setWidth(int w);
        void setHeight(int h);
        void setDimensions(int xPos, int yPos, int w, int h);
        
    private:
        int x;
        int y;
        int width;
        int height;
        bool border;
        uint16_t borderColor;
        int borderRadious;
        bool fill;
        uint16_t backgroundColor;
};

#endif // UNCLICKABLE_H