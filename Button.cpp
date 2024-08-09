#include "Button.h"
#include <Arduino.h>

Button::Button(int pin)
{
    this->pin = pin;
    this->isPressed = false;
    this->wasPressed = false;

    // instead of nullptr, use a lambda function that does nothing
    this->onClick = nullptr;
    this->onHold = nullptr;
    this->onRelease = nullptr;
    this->onDown = nullptr;
    this->onUp = nullptr;
    

    pinMode(pin, INPUT_PULLUP);

    this->isPressed = digitalRead(this->pin) != HIGH;
    this->wasPressed = this->isPressed;

    Serial.println(String("Button created with pin") + String(pin) + String(" isPressed: ") + String(this->isPressed));
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
        Serial.println("Button " + String(this->pin) + " clicked");
        this->onClick();
    }

    if (this->IsHolded())
    {
        Serial.println("Button " + String(this->pin) + " holded");
        this->onHold();
    }

    if (this->IsReleased())
    {
        Serial.println("Button " + String(this->pin) + " released");
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