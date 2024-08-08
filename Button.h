#ifndef BUTTON_H
#define BUTTON_H

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
    Button() : pin(-1){};
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

#endif // BUTTON_H