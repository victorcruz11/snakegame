#pragma once

#include "State.h"
#include "ofMain.h"

class MenuState : public State {

public:
    MenuState();
    ~MenuState();
    void reset();
    void update();
    void draw();
    void keyPressed(int key);
    virtual void mousePressed(int x, int y, int button);
    virtual string getCurrentState() {
        return "MenuState";
    }

};