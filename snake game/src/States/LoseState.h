#pragma once
#include "State.h"
#include "ofMain.h"

class LoseState : public State {
private:
    int score = 0;
public:
    LoseState(int finalScore);
    ~LoseState();
    void reset();
    void update();
    void draw();
    void keyPressed(int key);
    virtual void mousePressed(int x, int y, int button); 

    int getScore() {
        return score;
    }
    virtual string getCurrentState() {
        return "LoseState";
    }

};