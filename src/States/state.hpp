#pragma once
#include <SFML/Graphics.hpp>

enum StateID
{
	INTRO,
	MENU,
	GAME
};

class State
{
public:
	State(StateID);
	virtual void update(sf::Time /* elapsedTime */, bool& /* close */) = 0;
protected:
	StateID m_id;
};