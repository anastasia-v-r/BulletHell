#include "UIElement.hpp"

UIElement::UIElement()
	: parent{ nullptr } {

}

void UIElement::setParent(UIElement& parent) {
	this->parent = &parent;
}

UIElement& UIElement::getParent()
{
	if (parent == nullptr)
		throw std::logic_error("Cannot access a parent-less object");
	return *parent;
}
