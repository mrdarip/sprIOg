#include "Button.h"
#include <Arduino.h>

Button::Button(int pin)
{
    this->pin = pin;
    this->isPressed = false;
    this->wasPressed = false;

    //instead of nullptr, use a lambda function that does nothing
    this->onClick = []() {};
    this->onHold = []() {};
    this->onRelease = []() {};
    this->onDown = []() {};
    this->onUp = []() {};

    pinMode(pin, INPUT_PULLUP);

    this->isPressed = digitalRead(this->pin) != HIGH;
    this->wasPressed = this->isPressed;

    Serial.println(String("Button created with pin")+String(pin)+String(" isPressed: ")+String(this->isPressed));
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
    this->isPressed = digitalRead(this->pin) != HIGH;
    Serial.println(String("Button updated with pin")+String(pin)+String(" isPressed: ")+String(this->isPressed));

    if (this->IsClicked())
    {
        if (this->onClick != nullptr)
        {
            Serial.println("Button clicked");
            this->onClick();
        }
    }

    if (this->IsHolded())
    {
        if (this->onHold != nullptr)
        {
            Serial.println("Button holded");
            this->onHold();
        }
    }

    if (this->IsReleased())
    {
        if (this->onRelease != nullptr)
        {
            Serial.println("Button released");
            this->onRelease();
        }
    }

    if (this->IsDown())
    {
        if (this->onDown != nullptr)
        {
            Serial.println("Button down");
            this->onDown();
        }
    }

    if (this->IsUp())
    {
        if (this->onUp != nullptr)
        {
            Serial.println("Button up");
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
    Serial.println(String("Button clicked with pin")+String(pin));
    return this->isPressed && !this->wasPressed;
}

bool Button::IsHolded()
{
    Serial.println(String("Button holded with pin")+String(pin));
    return this->isPressed && this->wasPressed;
}

bool Button::IsReleased()
{
    Serial.println(String("Button released with pin")+String(pin));
    return !this->isPressed && this->wasPressed;
}