#pragma once
#include <SFML/Graphics.hpp>
#include <queue>
#include "UIManager.hpp"

enum struct StateID
{
	INTRO,
	MENU,
	SETTING,
	PROFILE,
	GAME
};

enum struct StateChange {
	ADD,
	REMOVE,
	WIPE
};

class State
{
public:
	State(StateID, std::queue<std::pair<StateChange, StateID>>& pendingChanges);
	virtual void input(sf::Event events , sf::RenderWindow& window, sf::View& view) = 0;
	virtual void update(sf::Time elapsedTime) = 0;
	virtual void draw(sf::RenderWindow& window) = 0;
	inline StateID getId() const { return m_id; };
protected:
	StateID m_id;
	std::queue<std::pair<StateChange, StateID>>& pendingChanges;
	UIManager m_UIMng;
};