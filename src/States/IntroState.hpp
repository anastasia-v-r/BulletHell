#pragma once
#include "State.hpp"
#include "Entities/Splash.hpp"
#include "ResourceManager.hpp"
#include <SFML/Graphics.hpp>
#include <queue>

class IntroState : public State
{
public:
	IntroState(std::queue<std::pair<StateChange, StateID>>& pendingChanges);
	void input(sf::Event evnt, sf::RenderWindow& window, sf::View& view) override;
	void update(sf::Time elapsedTime) override;
	void draw(sf::RenderWindow& window) override;
private:
	std::queue<Splash> splashQueue;
	sf::Texture gameT;
	sf::Texture companyT;
};