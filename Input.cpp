#include "Input.h"
#include "Button.h"
#include <Arduino.h>
#include <map>

// Constructor
Input::Input()
{
}

// Destructor
Input::~Input()
{
}

void Input::updateState()
{
    for (auto &pair : buttons)
    {
        pair.second.updateState();
    }
}

std:map<char, Button> Input::getButtons()
{
    return buttons;
}

Button& Input::getButton(char id)
{
    return buttons[id];
}

Button& Input::b(char id)
{
    return buttons[id];
}

void Input::addButton(char id, Button button)
{
    buttons[id] = button;
}
