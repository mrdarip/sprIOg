#ifndef INPUT_H
#define INPUT_H

#include "Button.h"
#include <map>

class Input {
public:
    // Constructor
    Input();

    // Destructor
    ~Input();

    void updateState();

    Button& getButton(char id);

    Button& b(char id);

    void addButton(char id, Button button);

    std::map<char, Button> getButtons();

private:
    std::map<char, Button> buttons;
};

#endif // INPUT_H