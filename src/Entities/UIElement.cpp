#include "UIElement.hpp"
#include <variant>
#include "UIManager.hpp"

UIElement::UIElement(UIManager* parent) {
	this->parent = parent;
}

UIElement::UIElement(UIElement* parent) {
	this->parent = parent;
}

std::variant<UIElement*, UIManager*>& UIElement::getParent()
{
	return parent;
}

void UIElement::draw(sf::RenderTarget& window, sf::RenderStates states) const {

}
