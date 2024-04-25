#include "GameState.h"

//--------------------------------------------------------------
GameState::GameState() {
    foodSpawned = false;
    cellSize = 25;
    boardSizeWidth = 64;
    boardSizeHeight = 36;
    snake = new Snake(cellSize, boardSizeWidth, boardSizeHeight);
    counter = 0;
    powerUpSeconds = 0;
    spawnPowerUp = false;
    usedSpeed = false;
    usedBetter = false;
    usedGod = false;
    activateSpeed = false;
    activateBetter = false;
    activateGod = false;
    invincible = false;
    name = NONE;
    aquiredPowerUp = NONE;

}
//--------------------------------------------------------------
GameState::~GameState() {
    delete snake;
}
//--------------------------------------------------------------
void GameState::reset() {
    if (State::getPreviousState() == "PauseState") {
        setFinished(false);
        setNextState("");
    }
    else {
        delete snake;
        score = 0;
        snake = new Snake(cellSize, boardSizeWidth, boardSizeHeight);
        foodSpawned = false;
        setFinished(false);
        setNextState("");
        usedSpeed = false;
        usedBetter = false;
        usedGod = false;
        activateSpeed = false;
        activateBetter = false;
        activateGod = false;
        invincible = false;
        counter = 0;
        name = NONE;
    }
}
//--------------------------------------------------------------
void GameState::update() {
    seconds = ofGetElapsedTimef();
    if (!invincible) {
        if(snake->isCrashed()) {
            State::setPreviousState("GameState");
            this->setNextState("LoseState");
            this->setFinished(true);
            return;
        }
    }

    if(snake->getHead()[0] == currentFoodX && snake->getHead()[1] == currentFoodY) {
        snake->grow();
        foodSpawned = false;
        score = score + 10;
    }

    foodSpawner();
    if (activateSpeed && usedSpeed) {
        counter++;
        powerUpSeconds = counter/60;
        if (powerUpSeconds < 15) {
            if(ofGetFrameNum() % 7 == 0) {
                snake->update();
            }
        } else {
            activateSpeed = false;
            powerUpSeconds=0;
            counter=0;
            name = NONE;
        }
    } else {
        if(ofGetFrameNum() % 10 == 0) {
            snake->update();
        }
    } 

    if (activateBetter && usedBetter) {
        name = NONE;
        activateBetter = false;
        aquiredPowerUp = NONE;
        snake->grow();
        snake->grow();
    }

    if (activateGod && usedGod) {
        snake->godMode = true;
        counter++;
        powerUpSeconds = counter/60;
        if (powerUpSeconds < 10) {
            invincible = true;
        }
        else {
            invincible = false;
            activateGod = false;
            name = NONE;
            powerUpSeconds=0;
            counter=0;
            snake->godMode = false;
        }
    }

    if(score == 50 || score == 100 || score == 150) {
        spawnPowerUp = true;
    }

    if (score == 60 && !usedSpeed) {
        name = SPEEDBOOST;
        if (activateSpeed) {
            name = NONE;
        }
    }
    if (score == 110 && !usedBetter) {
        name = BETTERAPPLE;
    }

    // if (score == 160 && !usedGod) {
    //     name = GODMODE;
    //     if (activateGod) {
    //         name = NONE;
    //     }
    // }
 
}
//--------------------------------------------------------------
void GameState::draw() {
    drawBoardGrid();
    snake->draw();
    drawFood();
    
    ofSetColor(ofColor::red);
    ofDrawBitmapString("Score: " + to_string(score), ofGetWidth()/2, 10);
    if (name == SPEEDBOOST) {
        ofDrawBitmapString("Power Up: Speed Boost", ofGetWidth()/2, 20);
    }
    else if (name == BETTERAPPLE) {
        ofDrawBitmapString("Power Up: Better Apple", ofGetWidth()/2, 20);
    }
    else if (name == GODMODE) {
        ofDrawBitmapString("Power Up: God Mode", ofGetWidth()/2, 20);
    }
    else if (name == NONE) {
        ofDrawBitmapString("Power Up: None", ofGetWidth()/2, 20);  
    }
    // TESTERS
    // ofDrawBitmapString("Time: " + to_string(seconds), ofGetWidth()/2, 30);
    // ofDrawBitmapString("Power Up Time: " + to_string(powerUpSeconds), ofGetWidth()/2, 40);



}
//--------------------------------------------------------------


//--------------------------------------------------------------

void GameState::keyPressed(int key) {

    // if(key != OF_KEY_LEFT && key != OF_KEY_RIGHT && key != OF_KEY_UP && key != OF_KEY_DOWN) { return; }

    switch(key) {
        case OF_KEY_LEFT:
            snake->changeDirection(LEFT);
            break;
        case OF_KEY_RIGHT:
            snake->changeDirection(RIGHT);
            break;
        case OF_KEY_UP:
            snake->changeDirection(UP);
            break;
        case OF_KEY_DOWN:
            snake->changeDirection(DOWN);
            break;
        case 'u':
            snake->undo();
            break;
        case 'a':
            score = score + 10;
            break;
        case 'p':
            State::setPreviousState("GameState");
            setFinished(true);
            setNextState("PauseState");
            break;
        case 'b':
            if (name == SPEEDBOOST) {
                activateSpeed = true;
                usedSpeed = true;
            } else if (name == BETTERAPPLE) {
                activateBetter = true;
                usedBetter = true;
            } else if (name == GODMODE) {
                activateGod = true;
                usedGod = true;
            }
            break;
    }
}
//--------------------------------------------------------------

void GameState::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------

void GameState::foodSpawner() {
    if((!foodSpawned || seconds>=30) && (!spawnPowerUp)) {
        ofResetElapsedTimeCounter();
        bool isInSnakeBody;
        do {
            isInSnakeBody = false;
            currentFoodX = ofRandom(1, boardSizeWidth-1);
            currentFoodY = ofRandom(1, boardSizeHeight-1);
            for(unsigned int i = 0; i < snake->getBody().size(); i++) {
                if(currentFoodX == snake->getBody()[i][0] and currentFoodY == snake->getBody()[i][1]) {
                    isInSnakeBody = true;
                }
            }
        } while(isInSnakeBody);
        foodSpawned = true;
    } else if (!foodSpawned && spawnPowerUp) {
        ofResetElapsedTimeCounter();
        bool isInSnakeBody;
        do {
            isInSnakeBody = false;
            currentFoodX = ofRandom(1, boardSizeWidth-1);
            currentFoodY = ofRandom(1, boardSizeHeight-1);
            for(unsigned int i = 0; i < snake->getBody().size(); i++) {
                if(currentFoodX == snake->getBody()[i][0] and currentFoodY == snake->getBody()[i][1]) {
                    isInSnakeBody = true;
                }
            }
        } while(isInSnakeBody);
        foodSpawned = true;
        spawnPowerUp = false;
    }
}
//--------------------------------------------------------------
void GameState::drawFood() {
    ofSetColor(ofColor::red);
    if (score == 50) {
        ofSetColor(ofColor::skyBlue);
    }
    if (score == 100) {
        ofSetColor(ofColor::darkRed);
    }
    if (score == 150) {
        ofSetColor(ofColor::gold);
    }
    if(foodSpawned) {
        if (!spawnPowerUp) {
            if (seconds>=15) {
                ofSetColor(ofColor::saddleBrown);
            }
        }
        ofDrawRectangle(currentFoodX*cellSize, currentFoodY*cellSize, cellSize, cellSize);
    } 
}
//--------------------------------------------------------------
void GameState::drawStartScreen() {
    ofSetColor(ofColor::black);
    ofDrawRectangle(0,0,ofGetWidth(),ofGetHeight());
    ofSetColor(ofColor::white);
    string text = "Press any arrow key to start.";
    ofDrawBitmapString(text, ofGetWidth()/2-8*text.length()/2, ofGetHeight()/2-11);
    return;
}
//--------------------------------------------------------------
void GameState::drawLostScreen() {
    ofSetColor(ofColor::black);
    ofDrawRectangle(0,0,ofGetWidth(),ofGetHeight());
    ofSetColor(ofColor::white);
    string text = "You lost! Press any arrow key to play again";
    string text2 = "or press ESC to exit.";
    ofDrawBitmapString(text, ofGetWidth()/2-8*text.length()/2, ofGetHeight()/2-11);
    ofDrawBitmapString(text2, ofGetWidth()/2-8*text2.length()/2, ofGetHeight()/2+2);
    return;
}
//--------------------------------------------------------------
void GameState::drawBoardGrid() {
    
    ofDrawGrid(25, 64, false, false, false, true);
    
    // ofSetColor(ofColor::white);
    // for(int i = 0; i <= boardSize; i++) {
    //     ofDrawLine(i*cellSize, 0, i*cellSize, ofGetHeight());
    //     ofDrawLine(0, i*cellSize, ofGetWidth(), i*cellSize);
    // }
}
//--------------------------------------------------------------

