#ifndef INPUT_H_INCLUDED
#define INPUT_H_INCLUDED

const int BUTTONS = 50;
enum Commands
{
    START_INP,
    PAUSE_INP,
    RESET_INP,
    LITTLE_HOUSE_INP,
    BIG_BEN_INP,
    PRECISION_IDEAL_INP,
    PRECISION_REAL_INP,
    FREQ_LOW_INP,
    FREQ_MED_INP,
    FREQ_HIGH_INP,
    MOON_INP,
    EARTH_INP,
    MARS_INP,
    JUPITER_INP,
    EXPORT_ON_INP,
    STANDARD_DATALIST_INP,
    ADVANCED_DATALIST_INP
};

class Input
{
public:
    Input();
    void leftButtonDown(LPARAM lParam);
    void clearButtonsPressed();
    void setButtonsLocation(int clientWidth, int clientHeight)
    {
        sx = clientWidth;
        sy = clientHeight;
    }
    bool isButtonPressed(int butNum)
    {
        return buttonsPressed[butNum];
    }
    void pressButton(int commandNum)
    {
        buttonsPressed[commandNum] = true;
    }
protected:
    bool buttonsPressed[BUTTONS];
    bool buttonIsPressed(int numOfButton);
    int mouseX;
    int mouseY;
    struct Point
    {
        int x;
        int y;
    };
    struct Button
    {
        Point topLeft;
        Point bottomRight;
    };

    int sx;
    int sy;

    Button* buttons[BUTTONS];

};

#endif // INPUT_H_INCLUDED
