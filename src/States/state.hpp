#pragma once
#include <SFML/Graphics.hpp>
#include <queue>

enum struct StateID
{
	INTRO,
	MENU,
	GAME
};

enum struct StateChange {
	ADD,
	REMOVE
};

class State
{
public:
	State(StateID, std::queue<std::pair<StateChange, StateID>>& /* pendingChanges */);
	virtual void update(sf::Time /* elapsedTime */, bool& /* close */) = 0;
	virtual void draw(sf::RenderWindow& /* window */) = 0;
	inline StateID getId() const { return m_id; };
protected:
	StateID m_id;
	std::queue<std::pair<StateChange, StateID>>& pendingChanges;
};