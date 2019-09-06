#pragma once
#include "State.hpp"
#include "SplashState.hpp"
#include <stack>

class StateManager
{
public:
	StateManager() { mStack.push(new SplashState()); }
	void run();
private:

private:
	std::stack<State*> mStack;
};