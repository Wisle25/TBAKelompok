#include "BaseComponent.h"

void BaseComponent::draw(sf::RenderTarget& Target, sf::RenderStates States) const
{
    Target.draw(*BaseShape);
}
