#include "stateManager.hpp"

StateManager::StateManager() {
	SplashState* pSplashState = new SplashState();
	mStateStack.push();
}