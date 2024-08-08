class Button
{
private:
    bool isPressed;
    bool wasPressed;
    int pin;
    void (*onClick)();
    void (*onHold)();
    void (*onRelease)();
    void (*onDown)();
    void (*onUp)();
    //void (*onLongPress)();
    //int holdTime;
public:
    Button(int pin);
    ~Button();
    void updateState();
    void setOnClick(void (*onClick)());
    void setOnHold(void (*onHold)());
    void setOnRelease(void (*onRelease)());
    void setOnDown(void (*onDown)());
    void setOnUp(void (*onUp)());

    //void setOnLongPress(void (*onLongPress)());
    //void setHoldTime(int holdTime);
    bool IsClicked();
    bool IsHolded();
    bool IsReleased();

    bool IsDown();
    bool IsUp();
};

Button::Button(int pin)
{
    this->pin = pin;
    this->isPressed = false;
    this->wasPressed = false;

    pinMode(pin, INPUT);
}

Button::~Button()
{
}

void Button::updateState()
{
    this->wasPressed = this->isPressed;
    this->isPressed = digitalRead(this->pin);

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
