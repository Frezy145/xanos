#ifndef CLICKABLE_H
#define CLICKABLE_H

#include <Arduino.h>
#include <stdint.h>

class Clickable {

    public:
        typedef void (*Callback)();

        Clickable(
            int xPos,
            int yPos,
            int w,
            int h,
            bool border=true,
            uint16_t borderColor=0xFFF,
            int borderRadious=0,
            bool fill=false,
            uint16_t backgroundColor=0x000,
            bool enabled=true,
            Callback cb = nullptr
        );

        virtual void  render();
        virtual void update();
        void setBackgroundColor(uint16_t backgroundColor);
        void setBorderColor(uint16_t borderColor);
        void setBorder(bool border);
        void setEnabled(bool enabled);
        void setOnClick(Callback cb);
        void setX(int x);
        void setY(int y);
        void click();
        bool contains(int x, int y);

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
        bool enabled;
        Callback callback;
};

#endif // CLICKABLE_H