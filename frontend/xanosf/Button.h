#ifndef BUTTON_H
#define BUTTON_H

#include "Clickable.h"
#include <Arduino.h>
#include <stdint.h>


class Button : public Clickable {
    public:

        typedef void (*Callback)();

        Button(
            int xPos,
            int yPos,
            String text,
            uint16_t textColor=0xFFF,
            int textSize=2,
            int padding=2,
            bool border=true,
            uint16_t borderColor=0xFFF,
            int borderRadious=2,
            bool fill=false,
            uint16_t backgroundColor=0x000,
            bool enabled=true,
            Callback cb=nullptr
        );

        void render() override;
        void update(String text);

    private:
        int x;
        int y;
        String text;
        uint16_t textColor;
        int textSize;
};


#endif // BUTTON_H