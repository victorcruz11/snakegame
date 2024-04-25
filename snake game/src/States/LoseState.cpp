#include "LoseState.h"

LoseState::LoseState(int finalScore) {
    score = finalScore;
}   

LoseState::~LoseState() {

}

void LoseState::reset() {
    setFinished(false);
    setNextState("");
    return;
}

void LoseState::update() {
    
}

void LoseState::draw() {
    ofSetColor(ofColor::black);
    ofDrawRectangle(0,0,ofGetWidth(),ofGetHeight());
    ofSetColor(ofColor::white);
    string text = "You lost! Press any arrow key to play again";
    string text2 = "or press ESC to exit.";
    string scoreText = "Final Score: " + to_string(getScore());
    ofDrawBitmapString(text, ofGetWidth()/2-8*text.length()/2, ofGetHeight()/2-11);
    ofDrawBitmapString(text2, ofGetWidth()/2-8*text2.length()/2, ofGetHeight()/2+2);
    ofDrawBitmapString(scoreText, ofGetWidth()/2-8*scoreText.length()/2, ofGetHeight()/2-22);
    return;
}

void LoseState::keyPressed(int key) {
    if(key == OF_KEY_LEFT || key == OF_KEY_RIGHT || key == OF_KEY_UP || key == OF_KEY_DOWN) {
        State::setPreviousState("LoseState");
        setFinished(true);
        setNextState("GameState");
        return;
    }
}

void LoseState::mousePressed(int x, int y, int button) {
    
}