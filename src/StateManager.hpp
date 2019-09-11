#pragma once
#include "State.hpp"
#include "SplashState.hpp"
#include "GameState.hpp"
#include <stack>

class StateManager
{
public:
	StateManager() { mStack.push(new GameState()); }
	void run();
	std::stack<State*> mStack;
private:

private:

};