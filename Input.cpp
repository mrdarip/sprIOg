#include "Button.h"
#include "Input.h"


// Constructor
Input::Input()
{
    this->addedButtons = 0;
    this->chars = "abcdefgh";
    this->buttons = new Button[8];
}

// Destructor
Input::~Input()
{
    delete[] buttons;
}

void Input::updateState()
{
    for (int i = 0; i < addedButtons; i++)
    {
        buttons[i].updateState();
    }
}

Button Input::getButton(char id)
{
    return buttons[indexOf(id, chars, 8)];
}

Button Input::b(char id)
{
    return getButton(id);
}

void Input::addButton(char id, Button button)
{
    this->buttons[indexOf(id, chars, 8)] = button;
    this->addedButtons++;
}