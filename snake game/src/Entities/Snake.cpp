#include "Snake.h"
#include "ofMain.h"

Snake::Snake(int segmentSize, int boardSizeW, int boardSizeH) {
    body.push_back({8, 9});
    body.push_back({9, 9});
    body.push_back({10, 9});
    body.push_back({11, 9});
    this->direction = LEFT;
    this->crashed = false;
    this->segmentSize = segmentSize;
    this->boardSizeWidth = boardSizeW;
    this->boardSizeHeight = boardSizeH;
    godMode = false;
}

Snake::~Snake() {
    // TODO Auto-generated destructor stub
}

void Snake::update() {
    vector<int> oldHead = this->getHead();
    if (!godMode) {
        switch(this->direction) {
            case LEFT: {
                this->body[0][0] -= 1;
                break;
            }
            case DOWN: {
                this->body[0][1] += 1;
                break;
            }
            case RIGHT: {
                this->body[0][0] += 1;
                break;
            }
            case UP: {
                this->body[0][1] -= 1;      
                break;
            }
            case STOP: {
                break;
            }
        }

        if(oldHead[0] == -1 || oldHead[0] == boardSizeWidth || oldHead[1] == -1 || oldHead[1] == boardSizeHeight) {
            crashed = true;
            return;
        }

        int prevX = oldHead[0];
        int prevY = oldHead[1];
        for (int i = 1; i < this->body.size(); i++) {
            int currX = this->body[i][0];
            int currY = this->body[i][1];
            this->body[i][0] = prevX;
            this->body[i][1] = prevY;
            prevX = currX;
            prevY = currY;
        }
        checkSelfCrash();
    } else {
        switch(this->direction) {
            case LEFT: {
                if (this->body[0][0] != 0) {
                this->body[0][0] -= 1;
                }
                break;
            }
            case DOWN: {
                if (this->body[0][1] != boardSizeHeight) {
                this->body[0][1] += 1;
                }
                break;
            }
            case RIGHT: {
                if (this->body[0][0] != boardSizeWidth) {
                this->body[0][0] += 1;
                }
                break;
            }
            case UP: {
                if (this->body[0][0] != 0) {
                this->body[0][1] -= 1;
                } 
                break;
            }
            case STOP: {
                break;
            }
        }

        if(oldHead[0] == -1 || oldHead[0] == boardSizeWidth || oldHead[1] == -1 || oldHead[1] == boardSizeHeight) {
            this->direction = STOP;
            return;
        }
        if (this->direction != STOP) {
            int prevX = oldHead[0];
            int prevY = oldHead[1];
            for (int i = 1; i < this->body.size(); i++) {
                int currX = this->body[i][0];
                int currY = this->body[i][1];
                this->body[i][0] = prevX;
                this->body[i][1] = prevY;
                prevX = currX;
                prevY = currY;
            }
        }
    }
}

void Snake::draw() {
    for (int i = 0; i < body.size(); i++) {
        int curX = this->body[i][0];
        int curY = this->body[i][1];
         if(i == 0){ // Changed head color to red
            ofSetColor(ofColor::blue);
        } else { // Changed Body color to green
            ofSetColor(ofColor::green);
        }
        ofDrawRectangle(curX * segmentSize, curY * segmentSize, segmentSize, segmentSize);
    }
}

void Snake::changeDirection(Direction d) {

    if(this->direction == LEFT and d == RIGHT)
        return;
    if(this->direction == RIGHT and d == LEFT) 
        return;
    if(this->direction == UP and d == DOWN) 
        return;
    if(this->direction == DOWN and d == UP)
        return;
    
   if (d == UNDO and this->body.size() > 2) {
        // Remove the tail segment of the snake
        this->body.pop_back();
        // Update the direction to the new direction of the head
        vector<int> newHead = this->body[0];
        vector<int> secondSegment = this->body[1];
        if (newHead[0] > secondSegment[0])
            this->direction = RIGHT;
        else if (newHead[0] < secondSegment[0])
            this->direction = LEFT;
        else if (newHead[1] > secondSegment[1])
            this->direction = DOWN;
        else
            this->direction = UP;
    }
    else
        this->direction = d;
}

void Snake::checkSelfCrash() {
    std::vector<std::vector<int>> snake = this->body;
    vector<int> head = snake[0];
    for(int i = 1; i < snake.size(); i++) {
        if(head[0] == snake[i][0] and head[1] == snake[i][1]) {
            crashed = true;
            return;
        }
    }
}

void Snake::grow() {
    vector<int> newSegment = this->getTail();
    this->body.push_back(newSegment);
}
void Snake::undo() {
    if (this->body.size() > 2) {
        this->body.pop_back();
    }
}

