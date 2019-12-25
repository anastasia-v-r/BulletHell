#pragma once
#include <SFML/Graphics.hpp>
#include "AssetManager.hpp"
#include <stack>
#include <vector>
#include <map>
#include <string>

class ResourceManager
{
public:
	ResourceManager() = default;
	
	// Direct Access
	sf::Font& getFont() const;
	void cleanAssets();

	// Asset Loading
	void loadTexture();
	void loadSfx();
	void loadMusic();
public: 
	AssetManager<sf::Texture> textures;
private:
	sf::Font font;

};