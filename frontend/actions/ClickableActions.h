#ifndef CLICKABLEACTIONS_H
#define CLICKABLEACTIONS_H

#include "Clickable.h"

#define MAGENTA 0xF81F
#define YELLOW 0xFFE0
#define WHITE 0xFFFF

class ClickableActions {
public:
    static void onClick(Clickable& clickable) {
        // Define the action to be taken when a clickable object is clicked
        // For example, change color or navigate to a different screen
        clickable.setColor(MAGENTA); // Example action: change color to MAGENTA
    }

    static void onHover(Clickable& clickable) {
        // Define the action to be taken when a clickable object is hovered over
        // For example, change appearance or show a tooltip
        clickable.setColor(YELLOW); // Example action: change color to YELLOW
    }

    static void onRelease(Clickable& clickable) {
        // Define the action to be taken when a clickable object is released
        // For example, revert color or finalize an action
        clickable.setColor(WHITE); // Example action: change color back to WHITE
    }
};

#endif // CLICKABLEACTIONS_H