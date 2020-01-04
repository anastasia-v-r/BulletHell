#include "ResourceManager.hpp"
#include <SFML/Graphics.hpp>
#include <stdexcept>

ResourceManager& ResourceManager::instance() {
	static ResourceManager s_instance;
	return s_instance;
}

ResourceManager::ResourceManager() {
	if (false) {
		throw std::logic_error("Cannot have more than one resource manager");
	} else {
		textures.insert({ "1", sf::Texture() });
		textures.at("1").loadFromFile("assets/splashScreen/BulletHellSplash.png");
		textures.insert({ "2", sf::Texture() });
		textures.at("2").loadFromFile("assets/splashScreen/ValorianSplash.png");
		// Init stuff
	}
}

sf::Font& ResourceManager::getFont() {
	return game_font;
}

sf::Texture& ResourceManager::getTexture(const std::string id) {
	return textures[id];
}

sf::SoundBuffer& ResourceManager::getSound(const std::string id) {
	return sounds[id];
}

void ResourceManager::loadState(const std::string assetList) {

}

void ResourceManager::unloadState() {

}
