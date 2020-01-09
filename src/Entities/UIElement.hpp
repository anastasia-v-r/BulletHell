#pragma once
#include <SFML/Graphics.hpp>
#include <variant>

class UIElement : public sf::Drawable
{
public:
	UIElement();
	void setParent(UIElement& parent);
	UIElement& getParent();
	
	// Optional functions
	virtual inline bool contains(sf::Vector2f point) { static_assert("This is not implemented in the derived class"); return 0; }


private:
	UIElement* parent;
};