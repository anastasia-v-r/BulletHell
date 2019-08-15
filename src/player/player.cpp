#include "player.hpp"
#include <iostream>
#include <fstream>
#include <iostream>

void Player::loadPlayer(std::string plrname) {
	std::ifstream stream;
	std::cout << plrname << std::endl;
	stream.open("players/" + plrname + "/playerdata.txt");
	if (!stream.is_open()) {
		std::cout << "yikes" << std::endl;
	}
	stream >> name;
	stream >> level;
	stream >> xp;
	stream >> deaths;
	std::cout << name << "\n" << level << "\n" << xp << "\n" << deaths << "\n";
	profilePicture.loadFromFile("players/" + plrname + "/pfp.png");
};

sf::Image* Player::getPlrPfp() {
	return &profilePicture;
}