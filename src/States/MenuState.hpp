#pragma once
#include "State.hpp"
#include <SFML/Graphics.hpp>
#include <map>
#include <stack>
#include "UIManager.hpp"
#include "Entities/Button.hpp"

class MenuState : public State
{
public:
	MenuState(std::queue<std::pair<StateChange, StateID>>& pendingChanges);
	void input(sf::Event evnt, sf::RenderWindow& window, sf::View& view) override;
	void update(sf::Time elapsedTime) override;
	void draw(sf::RenderWindow& window) override;
private:
	sf::RectangleShape background;
	UIManager m_UIMng;
};