class Input {
public:
    // Constructor
    Input() {
        // Initialize class members here
    }

    // Destructor
    ~Input() {
        // Clean up resources here
    }

    // Member functions
    void updateState() {
        
    }

    void addButton(Button button) {
        Button* temp = new Button[buttonCount + 1];
        for (int i = 0; i < buttonCount; i++)
        {
            temp[i] = buttons[i];
        }
        temp[buttonCount] = button;
        delete[] buttons;
        buttons = temp;
        buttonCount++;
    }

private:
    // Private members
    Button* buttons;
    int buttonCount;
};