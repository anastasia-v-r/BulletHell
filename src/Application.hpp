#pragma once
#include <SFML/Graphics.hpp>

class State;

class Application
{
public:
	static Application* _App;
	Application(Application const&) = delete;
	void operator=(Application const&) = delete;
private:
	Application();
};