#include "headers.h"
#include <iostream>



Input::Input()
{
    clearButtonsPressed();

    for(int i = 0; i<BUTTONS;i++)
    buttons[i] = 0;

    Button* startButton = new Button;
    startButton->topLeft.x=42;
    startButton->topLeft.y=514;
    startButton->bottomRight.x=82;
    startButton->bottomRight.y=566;
    buttons[START_INP]=startButton;


    Button* stopButton = new Button;
    stopButton->topLeft.x=43;
    stopButton->topLeft.y=603;
    stopButton->bottomRight.x=85;
    stopButton->bottomRight.y=655;
    buttons[PAUSE_INP]=stopButton;
}

void Input::clearButtonsPressed()
{
 for(int i = 0; i<BUTTONS;i++)
    buttonsPressed[i] = false;
}

void Input::leftButtonDown(LPARAM lParam)
{

    mouseX = LOWORD(lParam);
    mouseY = HIWORD(lParam);

    std::cout<<"x = "<<mouseX<<std::endl;
    std::cout<<"y = "<<mouseY<<std::endl;

    for(int i = 0; buttons[i];i++)
    {
        if(buttonIsPressed(i))
        {
            buttonsPressed[i] = !buttonsPressed[i];
                std::cout<<"i = "<<i<<std::endl;
            break;
        }


    }

}
bool Input::buttonIsPressed(int numOfButton)
{
    if(mouseX<(sx/1024.0)*buttons[numOfButton]->bottomRight.x
       &&mouseY<(sy/686.0)*buttons[numOfButton]->bottomRight.y
       &&mouseX>(sx/1024.0)*buttons[numOfButton]->topLeft.x
       &&mouseY>(sy/686.0)*buttons[numOfButton]->topLeft.y)
    {
       // std::cout<<"button is pressed, number: "<<numOfButton<<std::endl;
        return true;
    }
    else
        return false;
}
