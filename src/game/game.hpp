#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <player/player.hpp>

enum GameState {
	Splash, MainMenu,
	Playing, Paused, Exiting
};

class Game 
{

public:
	void Start();
	
private:
	
	Player player;
	GameState _gameState{ Splash };
	sf::RenderWindow _mainWindow;
	bool running{ true };

	void GameLoop();

public:
	Game() {
		auto mode = sf::VideoMode::getDesktopMode();
		mode.height += 1;
		_mainWindow.create(mode, "BulletHell!", sf::Style::None);
	};
	~Game();
};