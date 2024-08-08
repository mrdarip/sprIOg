#include "Input.h"
#include "Button.h"

// Constructor
Input::Input()
{
    this->addedButtons = 0;
    this->chars = {'w', 'a', 's', 'd', 'i', 'j', 'k', 'l'};
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

    int index = 0;
    for (int i = 0; i < 8; i++)
    {
        if (chars[i] == id)
        {
            index = i;
            break;
        }
    }
    this->buttons[index] = button;
    this->addedButtons++;
}
