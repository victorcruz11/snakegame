#pragma once
#include <vector>

enum Direction {
        LEFT,
        RIGHT,
        UP,
        DOWN,
        UNDO,
        STOP
    };

class Snake {

private:
    std::vector<std::vector<int>> body;
    Direction direction;
    int boardSizeWidth, boardSizeHeight;
    int segmentSize;
    bool crashed;

public:
    Snake(int segmentSize, int boardSizeW, int boardSizeH);
    ~Snake();

    void update();
    void draw();
    void changeDirection(Direction d);
    Direction getDirection() {
        return direction;
    }
    void checkSelfCrash();
    void grow();
    void undo();
    bool isCrashed() {
        return this->crashed;
    }
    std::vector<int> getHead() {
        return this->body[0];
    }
    std::vector<int> getTail() {
        return this->body[this->body.size() - 1];
    }
    std::vector<std::vector<int>> getBody() {
        return this->body;
    }

    bool godMode;

};
