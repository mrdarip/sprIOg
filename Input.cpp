#include "Input.h"
#include "Button.h"
#include <Arduino.h>

// Constructor
Input::Input()
{
    this->addedButtons = 0;

    char tempChars[8] = {'w', 'a', 's', 'd', 'i', 'j', 'k', 'l'};
    for (int i = 0; i < 8; i++) {
        this->chars[i] = tempChars[i];
    }
    
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
    int index = 0;
    for (int i = 0; i < 8; i++)
    {
        if (chars[i] == id)
        {
            index = i;
            break;
        }
    }

    return buttons[index];
}

Button Input::b(char id)
{
    return getButton(id);
}

void Input::addButton(char id, Button button)
{

    int index = -1;
    for (int i = 0; i < 8; i++)
    {
        Serial.println("chars[i]: " + String(chars[i]) + " id: " + String(id));
        if (chars[i] == id)
        {
            Serial.println("found");
            index = i;
            break;
        }
    }

    if (index == -1)
    {
        Serial.println("Button not added");
        return;
    }
    
    this->buttons[index] = button;
    this->addedButtons++;
}
