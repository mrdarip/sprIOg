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

    void updateState() {
        for(int i = 0; i < addedButtons; i++) {
            buttons[i].updateState();
        }
    }

    Button getButton(char id) {
        return buttons[indexOf(id,chars,8)];
    }

    Button b(char id) {
        return getButton(id);
    }

    void addButton(char id,Button button) {
        this->buttons[indexOf(id,chars,8)] = button;
        this->addedButtons++;
    }

private:
    // Private members
    Button[] buttons = new Buttons[8];
    int addedButtons;

    const chars = ['w','a','s','d','i','j','k','l'];
};

int indexOf(char c, const char* chars, int size) {
    for (int i = 0; i < size; i++) {
        if (chars[i] == c) {
            return i;
        }
    }
    return -1;
}