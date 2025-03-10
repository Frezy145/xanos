#ifndef TEXT_H
#define TEXT_H

#include "UnClickable.h"
#include <Arduino.h>
#include <stdint.h>

// class text inherits from unclickable
class Text : public UnClickable {
    public:
        Text(
            int xPos, 
            int yPos, 
            String txt,
            uint16_t txtColor=0xFFFF,
            int txtSize=1,
            int pad=0,

            bool border=false,
            uint16_t borderColor=0xFFFF,
            int borderRadious=0,
            bool fill=false,
            uint16_t backgroundColor=0x0000
        );
        void render() override;
        void update(String text);

    private: 
        String text;
        int textSize;
        uint16_t textColor;
        int x;
        int y;
};

#endif // TEXT_H