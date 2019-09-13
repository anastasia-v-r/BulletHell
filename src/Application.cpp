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
		if (mStates.top()->moveState)
			switch (mStates.top()->nextState)
			{
			case StateEnum::Menu:

				break;
			case StateEnum::Game:
				mStates.push(new GameState);
				break;
			}
	}
	mWindow.close();
}
