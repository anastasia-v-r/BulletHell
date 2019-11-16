#pragma once
#include "State.hpp"
#include <SFML/Graphics.hpp>

class IntroState : public State
{
public:
	IntroState(std::queue<std::pair<StateChange, StateID>>& /* pendingChanges */);
	void input(sf::Event /* evnt */, bool& /* close */, sf::RenderWindow& /* window */, sf::View& /* view */) override;
	void update(sf::Time /* elapsedTime */, bool& /* close */) override;
	void draw(sf::RenderWindow& /* window */) override;
private:
	sf::RectangleShape button;
	sf::Text text;
	sf::Font font;
};