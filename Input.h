#ifndef INPUT_H
#define INPUT_H

#include "Button.h"

class Input {
public:
    // Constructor
    Input();

    // Destructor
    ~Input();

    void updateState();

    Button getButton(char id);

    Button b(char id);

    void addButton(char id, Button button);

private:
    // Private members
    Button* buttons; //this should be initialized to nullptr?
    int addedButtons;

    const char* chars;
};

#endif // INPUT_H