#include "Button.h"
#include <Arduino.h>
#include <functional>

Button::Button(int pin)
{
    this->pin = pin;
    this->isPressed = false;
    this->wasPressed = false;

    // instead of nullptr, use a lambda function that does nothing
    this->onClick = []() {};
    this->onHold = []() {};
    this->onRelease = []() {};
    this->onDown = []() {};
    this->onUp = []() {};
    

    pinMode(pin, INPUT_PULLUP);

    this->isPressed = digitalRead(this->pin) != HIGH;
    this->wasPressed = this->isPressed;
}

Button::~Button()
{
}

void Button::updateState()
{
    if (this->pin == -1)
    {
        return;
    }

    this->wasPressed = this->isPressed;
    this->isPressed = digitalRead(this->pin) != HIGH;

    if (this->IsClicked())
    {
        this->onClick();
    }

    if (this->IsHolded() && onHold != nullptr)
    {
        this->onHold();
    }

    if (this->IsReleased())
    {
        this->onRelease();
    }

    if (this->IsDown())
    {
        this->onDown();
    }

    if (this->IsUp())
    {
        this->onUp();
    }
}

void Button::setOnClick(std::function<void()> f)
{
    f();
    this->onClick = f;
}

void Button::setOnHold(std::function<void()> f)
{
    f();
    this->onHold = f;
}

void Button::setOnRelease(std::function<void()> f)
{
    f();
    this->onRelease = f;
}

void Button::setOnDown(std::function<void()> f)
{
    f();
    this->onDown = f;
}

void Button::setOnUp(std::function<void()> f)
{
    f();
    this->onUp = f;
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