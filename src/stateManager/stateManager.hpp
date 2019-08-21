#pragma once
#include <stack>
#include <SFML/Graphics.hpp>
#include "state.hpp"
#include <stateManager/states/splashState.hpp>

class StateManager
{
public:
	enum CurrentState
	{
		Splash,
		Menu,
		Loading,
		Game,
		Pause
	};

private:
	std::stack<State*> mStateStack;
	CurrentState mCurrentState{ CurrentState::Splash };

public:
	void processStack(sf::RenderWindow);
	StateManager();

};
