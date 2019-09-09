#include <Application.hpp>
#include <nlohmann/json.hpp>

int main() {
	auto mode = sf::VideoMode::getDesktopMode();
	mode.height += 1;
	Application app(mode);
	app.run();
}