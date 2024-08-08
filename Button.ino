class Button
{
private:
    bool isPressed;
    bool wasPressed;
    int pin;

public:
    Button(int pin);
    ~Button();
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
