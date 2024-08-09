#include "Button.h"
#include <Arduino.h>

Button::Button(int pin)
{
    this->pin = pin;
    this->isPressed = false;
    this->wasPressed = false;

    // instead of nullptr, use a lambda function that does nothing
    this->onClick = []() {
        Serial.println("Button clicked");
    };
    this->onHold = []() {
        Serial.println("Button holded");
    };
    this->onRelease = []() {
        Serial.println("Button released");
    };
    this->onDown = []() {};
    this->onUp = []() {};

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