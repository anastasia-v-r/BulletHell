#pragma once
#include "State.hpp"
#include <SFML/Graphics.hpp>

class MenuState : public State
{
public:
	MenuState(std::queue<std::pair<StateChange, StateID>>& /* pendingChanges */);
	void update(sf::Time /* elapsedTime */, bool& /* close */) override;
	void draw(sf::RenderWindow& /* window */) override;
private:
	sf::RectangleShape button;
	sf::Text text;
	sf::Font font;
};