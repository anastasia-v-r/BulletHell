#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>

class Bullet : public sf::Drawable
{
public:
	Bullet(sf::Vector2f pos) 
		: bullet{sf::RectangleShape(sf::Vector2f(10.0f, 10.0f))} {
		bullet.setPosition(pos);
		bullet.setFillColor(sf::Color::Green);
	}
	void travel() {
		bullet.move(0.0f, -1.0f);
	}
	virtual void draw(sf::RenderTarget& window, sf::RenderStates states) const {
		window.draw(bullet, states);
	}
private:
	sf::RectangleShape bullet;
};

int main() {
	// Create Render Window
	sf::RenderWindow window;
	window.create(sf::VideoMode::getDesktopMode(), "Danmaku", sf::Style::Default);
	// Test object
	sf::RectangleShape box(sf::Vector2f(50.0f, 50.0f));
	box.setFillColor(sf::Color::Red);
	// Bullet vector
	std::vector<Bullet> bullets;
	// Run While the window is open
	while (window.isOpen()) {
		// Process Events
		sf::Event evnt;
		while (window.pollEvent(evnt)) {
			switch (evnt.type)
			{
			case sf::Event::KeyPressed:
				switch (evnt.key.code)
				{
				case sf::Keyboard::Escape:
					window.close();
					break;
				case sf::Keyboard::Space:
					bullets.push_back(Bullet(box.getPosition()));
					break;
				case sf::Keyboard::W:
					box.move(0.0f, -10.0f);
					break;
				case sf::Keyboard::A:
					box.move(-10.0f, 0.0f);
					break;
				case sf::Keyboard::S:
					box.move(0.0f, 10.0f);
					break;
				case sf::Keyboard::D:
					box.move(10.0f, 0.0f);
					break;
				default:
					break;
				}
			default:
				break;
			}
		}
		// Update Game
		if (!bullets.empty())
			for (auto& bullet : bullets) {
				bullet.travel();
			}
		// Draw objects
		window.clear();
		window.draw(box);
		if (!bullets.empty())
			for (const auto& bullet : bullets) {
				window.draw(bullet);
			}
		window.display();
	}
}