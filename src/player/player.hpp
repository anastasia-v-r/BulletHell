#pragma once
#include <string>
#include <SFML/Graphics.hpp>

class Player 
{
private:
	sf::Image profilePicture;
	std::string name;
	int level;
	int xp;
	int deaths;
public:
	void loadPlayer(std::string plrName);
	sf::Image* getPlrPfp();
};