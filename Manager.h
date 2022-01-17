/*
The Manager class is responsible of managing the interactions between the two main callbacks (Timer and Observer).
The user can choose between two type of simulation: 
    - oscillation without damping ('n' pressed) 
    - damped oscillation ('d' pressed)
If the user press the button 's' of the keyboard the class attribute "enable" is set to 1, then Timer begin the count.
*/
#pragma once

class Manager
{
public:

    Manager::Manager() : enable(0), angle(1) {}
    void setEnable(void)
    {
        enable = 1;
    } 
    void setAngleWithoutDamping(void)
    {
        angle = 1;
    }
    void setAngleWithDamping(void)
    {
        angle = 2;
    }
    int enable;
    int angle;

};


      