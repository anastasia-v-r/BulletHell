#include "Boss.hpp"
#include "Bullet.hpp"

void Boss::move(const sf::Time& elapsedTime) {
	// Keep in place
	if (boss.getPosition().x > ((GlobalData::TRUE_MODE.width / 3) * 2))
		goRight = false;
	else if (boss.getPosition().x < ((GlobalData::TRUE_MODE.width / 3)))
		goRight = true;
	// Move
	if (goRight)
		boss.move(speed * elapsedTime.asSeconds(), 0);
	else
		boss.move(-speed * elapsedTime.asSeconds(), 0);
}

void Boss::fire(const sf::Time& elapsedTime, std::vector<Bullet>& bullets) {
	if (timeBank.asSeconds() > fireRate) {
		float speed = 500.0f;
		float size = 15.0f;
		float angVel;
		float dmg = 1;
		if (goRight)
			angVel = -40.0f;
		else
			angVel = 40.0f;
		bullets.push_back(Bullet(boss.getPosition() + sf::Vector2f(boss.getRadius(), boss.getRadius()), 135.0f, speed, angVel, dmg, size, bul1));
		bullets.push_back(Bullet(boss.getPosition() + sf::Vector2f(boss.getRadius() / 2, boss.getRadius()), 157.5f, speed, angVel, dmg, size, bul2));
		bullets.push_back(Bullet(boss.getPosition() + sf::Vector2f(0.0f, boss.getRadius()), 180.0f, speed, angVel, dmg, size, bul1));
		bullets.push_back(Bullet(boss.getPosition() + sf::Vector2f(-boss.getRadius() / 2, boss.getRadius()), 202.5f, speed, angVel, dmg, size, bul2));
		bullets.push_back(Bullet(boss.getPosition() + sf::Vector2f(-boss.getRadius(), boss.getRadius()), 225.0f, speed, angVel, dmg, size, bul1));
		timeBank -= (sf::seconds)(fireRate);
	}
	else {
		timeBank += elapsedTime;
	}
}

bool Boss::detectCollide(std::vector<Bullet>& bullets) {
	auto [x2, y2] = boss.getPosition();
	float bRad = boss.getRadius();
	for (auto& bullet : bullets) {
		auto [x1, y1] = bullet.getPos();
		if (bullet.getVal() && std::sqrt(std::pow(y2 - y1, 2) + std::pow(x2 - x1, 2)) < (bRad + bullet.getRadius())) {
			bullet.invalidate();
			hp -= bullet.getDmg();
			if (hp < (iHp * 0.75f) && hp >= (iHp * 0.50f)) {
				boss.setFillColor(sf::Color::Yellow);
			}
			else if (hp < (iHp * 0.50f) && hp >= (iHp * 0.25f)) {
				boss.setFillColor(sf::Color(255, 98, 0));
			}
			else if (hp < (iHp * 0.25f) && hp >= 1.0f) {
				boss.setFillColor(sf::Color::Red);
			}
			else if (hp < 1) {
				return true;
			}
		}
	}
	return false;
}