#pragma once

#include "State.h"
#include "Snake.h"
#include "ofMain.h"

enum powerUp {
    NONE,
    SPEEDBOOST,
    BETTERAPPLE,
    GODMODE
};
class GameState : public State {
    public:
        GameState();
        ~GameState();
        void reset();
        void update();
        void draw();
        void keyPressed(int key);
        virtual void mousePressed(int x, int y, int button);
        void foodSpawner();
        void drawFood();
        void drawStartScreen();
        void drawLostScreen();
        void drawBoardGrid();
        virtual string getCurrentState() {
            return "GameState";
        }

        Snake* snake;
        
        bool foodSpawned = false;

        int currentFoodX;
        int currentFoodY;
        int score = 0;
        float seconds;

        float powerUpSeconds;
        int counter;
        bool usedBetter;
        bool usedSpeed;
        bool usedGod;
        bool activateSpeed;
        bool activateBetter;
        bool activateGod;
        bool spawnPowerUp;
        bool invincible;
        powerUp name;
        powerUp aquiredPowerUp;


        int boardSizeWidth, boardSizeHeight;
        int cellSize; // Pixels
};