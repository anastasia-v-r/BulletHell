#include "Application.hpp"
#include <iostream>

Application::Application(sf::VideoMode mode) 
: mWindow(mode, "BulletHell", sf::Style::Default)
, exiting{ false } 
{
	mStates.push(new SplashState);
}

void Application::run() {
	while (!mStates.empty()) {
		mStates.top()->HandleInput(mWindow);
		mStates.top()->UpdateGame(mWindow);
		mStates.top()->DrawElements(mWindow);
		if (State::addState) {
			switch (State::nextState)
			{
			case StateEnum::None:
				break;
			case StateEnum::Menu:

				break;
			case StateEnum::Game:
				mStates.push(new GameState);
				break;
			}
			State::addState = false;
			State::nextState = StateEnum::None;
		}
		else if (State::removeState) {
			mStates.pop();
			State::removeState = false;
		} else if (State::wipeStates) {
			while (!mStates.empty()) {
				mStates.pop();
			}
		}
	}
	mWindow.close();
}
