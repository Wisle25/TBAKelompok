#include "BaseComponent.h"

void BaseComponent::draw(sf::RenderTarget& Target, sf::RenderStates States) const
{
    if (BaseShape)
        Target.draw(*BaseShape);

    if (Text)
        Target.draw(*Text);
}
