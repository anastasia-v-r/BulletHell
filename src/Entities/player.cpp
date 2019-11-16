#include "player.hpp"
#include "../globals.hpp"

void Player::move(sf::Time elapsedTime) {
	if (keyMap.at("Up"))
		player.move(0, -speed * elapsedTime.asSeconds());
	if (keyMap.at("Right"))
		player.move(speed * elapsedTime.asSeconds(), 0);
	if (keyMap.at("Down"))
		player.move(0, speed * elapsedTime.asSeconds());
	if (keyMap.at("Left"))
		player.move(-speed * elapsedTime.asSeconds(), 0);
}

void Player::fire(const sf::Time& elapsedTime, std::vector<Bullet>& bullets) {
	static int bullet = 0;
	if (keyMap.at("Space")) {
		if (timeBank.asSeconds() > fireRate) {
			bullets.push_back(Bullet(sf::Vector2f(player.getPosition().x, player.getPosition().y + player.getRadius()), 0.0f, 1000.0f, 0.0f, 5.0f, 10.0f, bul1)); // Normal bullets
			bullet += 1;
			if (bullet == 4) {
				bullets.push_back(Bullet(sf::Vector2f(player.getPosition().x, player.getPosition().y + player.getRadius()), 1000.0f, 5.0f, 25.0f, bul2, true));
				bullet = 0;
			}
			timeBank -= (sf::seconds)(fireRate);
		}
		else {
			timeBank += elapsedTime;
		}
	}
	else {
		if (timeBank >= (sf::seconds)(fireRate * 2.0f)) {
			timeBank -= (sf::seconds)(fireRate);
		}
		else if (timeBank >= (sf::seconds)(fireRate)) {
			timeBank = (sf::seconds)(fireRate);
		}
		else {
			timeBank = sf::Time::Zero;
		}
	}
}

bool Player::detectCollide(std::vector<Bullet>& bullets) {
	auto [x2, y2] = player.getPosition();
	float pRad = player.getRadius();
	for (auto& bullet : bullets) {
		auto [x1, y1] = bullet.getPos();
		if (std::sqrt(std::pow(y2 - y1, 2) + std::pow(x2 - x1, 2)) < (pRad + bullet.getRadius())) {
			hp--;
			bullets.clear();
			if (hp == 2) {
				player.setFillColor(sf::Color(255, 98, 0));
				return false;
			}
			else if (hp == 1) {
				player.setFillColor(sf::Color::Red);
				return false;
			}
			else {
				return true;
			}
		}
	}
	return false;
}