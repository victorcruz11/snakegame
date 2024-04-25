#include "PauseState.h"
#include <iostream>

PauseState::PauseState() {
    xPos = ofGetWidth()/2 - 85;
    yPos = ofGetHeight()/2 - 17;
    width = 170;
    height = 22;
}

PauseState::~PauseState() {}

void PauseState::reset() {
    setFinished(false);
    setNextState("");
    return;
}

void PauseState::update() {
    if (this->wasPressed()) {
        setPressed(false);
        State::setPreviousState("PauseState"); 
        setFinished(true);
        setNextState("GameState");
        return;
    }
}

void PauseState::draw() {
    ofSetColor(ofColor::black);
    ofDrawRectangle(0,0,ofGetWidth(),ofGetHeight());
    ofSetColor(ofColor::white);
    string text = "Game is paused.";
    string text2 = "Click here to unpause.";
    ofDrawBitmapString(text, ofGetWidth()/2-8*text.length()/2, ofGetHeight()/2-11);
    ofDrawBitmapString(text2, ofGetWidth()/2-8*text2.length()/2, ofGetHeight()/2+2);

    // for testing
    ofSetColor(ofColor::white);
    ofNoFill();
    ofDrawRectangle(ofGetWidth()/2 - 85, ofGetHeight()/2 - 17, 170, 22);
    ofFill();

    return;
}

void PauseState::keyPressed(int key) {

}

void PauseState::mousePressed(int x, int y, int button) {
    if((button==OF_MOUSE_BUTTON_LEFT) && (x>=ofGetWidth()/2 - 85) && (x<=(ofGetWidth()/2 - 85)+170) && (y>=ofGetHeight()/2 - 17) && (y<=(ofGetHeight()/2 - 17)+22)){
        setPressed(true);
        return;
    }
}
