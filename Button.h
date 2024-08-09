#ifndef BUTTON_H
#define BUTTON_H

class Button
{
private:
    bool isPressed;
    bool wasPressed;
    int pin;
    //void (*onLongPress)();
    //int holdTime;
public:
    Button(int pin);
    ~Button();
    Button() : pin(-1){};
    void updateState();

    void (*onClick)();
    void (*onHold)();
    void (*onRelease)();
    void (*onDown)();
    void (*onUp)();

    bool IsClicked();
    bool IsHolded();
    bool IsReleased();

    bool IsDown();
    bool IsUp();
};

#endif // BUTTON_H