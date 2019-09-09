#include "Application.hpp"
#include <iostream>

Application::Application(sf::VideoMode mode) 
: mWindow(mode, "BulletHell", sf::Style::Default) 
, mStackManager()
, mResourceManager()
, exiting{ false } 
{
}

void Application::run() {
	while (!exiting) {
		mStackManager.mStack.top()->HandleInput(mWindow);
		mStackManager.mStack.top()->UpdateGame(mWindow);
		mStackManager.mStack.top()->DrawElements(mWindow);
	}
}