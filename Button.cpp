#include "Button.h"
#include <Arduino.h>

Button::Button(int pin)
{
    this->pin = pin;
    this->isPressed = false;
    this->wasPressed = false;
    this->onClick = nullptr;
    this->onHold = nullptr;
    this->onRelease = nullptr;
    this->onDown = nullptr;
    this->onUp = nullptr;


    pinMode(pin, INPUT_PULLUP);
}

Button::~Button()
{
}

void Button::updateState()
{
    if(this->pin == -1)
    {
        return;
    }

    this->wasPressed = this->isPressed;
    this->isPressed = !digitalRead(this->pin);

    if (this->IsClicked())
    {
        if (this->onClick != nullptr)
        {
            this->onClick();
        }
    }

    if (this->IsHolded())
    {
        if (this->onHold != nullptr)
        {
            this->onHold();
        }
    }

    if (this->IsReleased())
    {
        if (this->onRelease != nullptr)
        {
            this->onRelease();
        }
    }

    if (this->IsDown())
    {
        if (this->onDown != nullptr)
        {
            this->onDown();
        }
    }

    if (this->IsUp())
    {
        if (this->onUp != nullptr)
        {
            this->onUp();
        }
    }
}

void Button::setOnClick(void (*onClick)())
{
    this->onClick = onClick;
}

void Button::setOnHold(void (*onHold)())
{
    this->onHold = onHold;
}

void Button::setOnRelease(void (*onRelease)())
{
    this->onRelease = onRelease;
}

void Button::setOnDown(void (*onDown)())
{
    this->onDown = onDown;
}

void Button::setOnUp(void (*onUp)())
{
    this->onUp = onUp;
}

bool Button::IsDown()
{
    return this->isPressed;
}

bool Button::IsUp()
{
    return !this->isPressed;
}

bool Button::IsClicked()
{
    return this->isPressed && !this->wasPressed;
}

bool Button::IsHolded()
{
    return this->isPressed && this->wasPressed;
}

bool Button::IsReleased()
{
    return !this->isPressed && this->wasPressed;
}