#pragma once

#include <string>

class State {
	public:
		State() {}
		virtual void reset() = 0;
		virtual void update() = 0;
		virtual void draw() = 0;
        virtual void keyPressed(int key) = 0;
		virtual void mousePressed(int x, int y, int button) = 0;
		virtual std::string getCurrentState() = 0;

		bool hasFinished(){
			return finished;
		}
		std::string getNextState(){
			return nextState;
		}

		std::string getPreviousState() {
			return previousState;
		}

		void setFinished(bool finished){
			this->finished = finished;
		}

		void setNextState(std::string nextState){
			this->nextState = nextState;
		}

		void setPreviousState(std::string previousState) {
			this->previousState = previousState;
		}

	private:
		std::string previousState;
		std::string nextState;
		bool finished = false;

};