#ifndef BUTTON_H
#define BUTTON_H

#include <functional>

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

    std::function<void()> onClick = []() {};
    std::function<void()> onHold = []() {};
    std::function<void()> onRelease = []() {};
    std::function<void()> onDown = []() {};
    std::function<void()> onUp = []() {};

    void setOnClick(std::function<void()> f);
    void setOnHold(std::function<void()> f);
    void setOnRelease(std::function<void()> f);
    void setOnDown(std::function<void()> f);
    void setOnUp(std::function<void()> f);

    bool IsClicked();
    bool IsHolded();
    bool IsReleased();

    bool IsDown();
    bool IsUp();
};

#endif // BUTTON_H