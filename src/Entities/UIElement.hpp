#pragma once
#include <SFML/Graphics.hpp>
#include <variant>

class UIElement : public sf::Drawable
{
public:
	UIElement();
	void setParent(UIElement& parent);
	UIElement& getParent();
private:
	UIElement* parent;
};