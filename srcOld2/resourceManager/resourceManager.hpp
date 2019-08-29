#pragma once
#include <SFML/Graphics.hpp>
#include <nlohmann/json.hpp>

class ResourceManager
{
private:
	nlohmann::json j;

public:
	ResourceManager();

};
