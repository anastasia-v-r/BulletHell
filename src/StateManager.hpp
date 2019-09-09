#pragma once
#include "State.hpp"
#include "SplashState.hpp"
#include <stack>

class StateManager
{
public:
	StateManager() { mStack.push(new SplashState()); }
	void run();
	std::stack<State*> mStack;
private:

private:

};