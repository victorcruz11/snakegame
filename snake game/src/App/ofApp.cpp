#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    ofSetWindowTitle("Snake");

    gameState = new GameState();
    menuState = new MenuState();
    loseState;
    pauseState = new PauseState();
    currentState = menuState;
    music.load("snake.mp3");
    music.play();

}

//--------------------------------------------------------------
void ofApp::update(){
    if(currentState->hasFinished()) {
        string prev = currentState->getCurrentState();
        if(currentState->getNextState() == "GameState") {
            gameState->setPreviousState(prev);
            gameState->reset();
            currentState = gameState;
        } else if(currentState->getNextState() == "MenuState") {
            menuState->reset();
            currentState = menuState;
        } else if(currentState->getNextState() == "LoseState") {
            loseState = new LoseState(gameState->score);
            loseState->setPreviousState(prev);
            loseState->reset();
            currentState = loseState;
        } else if(currentState->getNextState() == "PauseState") {
            pauseState->setPreviousState(prev);
            pauseState->reset();
            currentState = pauseState;
        }
    }
    currentState->update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    currentState->draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    currentState->keyPressed(key);
}
//--------------------------------------------------------------

void ofApp::mousePressed(int x, int y, int button){
    currentState->mousePressed(x,y,button);
}
