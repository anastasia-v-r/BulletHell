#include "Application.hpp"
#include <iostream>

Application::Application(sf::VideoMode mode) 
: mWindow(mode, "BulletHell", sf::Style::Default) 
, mStates{new SplashState}
, exiting{ false } 
{
}

void Application::run() {
	while (!exiting) {
		mStates.top()->HandleInput(mWindow);
		mStates.top()->UpdateGame(mWindow);
		mStates.top()->DrawElements(mWindow);
		if (!mWindow.isOpen())
			exiting = true;
	}
}