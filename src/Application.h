#include <SFML/Graphics.hpp>

class Application
{
private: // Variables
	sf::RenderWindow mWindow;
public: // Public funcs
	Application();
	void runApp();
private: // Interal funcs
	void proccessInput();
	void updateGame();
	void renderGame();
};