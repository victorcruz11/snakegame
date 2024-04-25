#pragma once
#include "State.h"
#include "ofMain.h"

class PauseState : public State {
private: 
    bool pressed = false;
    int xPos, yPos, width, height;
public:
    PauseState();
    ~PauseState();
    void reset();
    void update();
    void draw();
    void keyPressed(int key);
    virtual void mousePressed(int x, int y, int button);

    bool wasPressed() {return pressed;}
    void setPressed(bool b) {pressed = b;}
    virtual string getCurrentState() {
        return "PauseState";
    }
};