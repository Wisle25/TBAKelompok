#pragma once

#include "Core.h"

class BaseComponent : public sf::Drawable
{
public:
    virtual void Tick(const float DeltaTime) {}
    virtual void draw(sf::RenderTarget& Target, sf::RenderStates States) const override;

protected:
    std::unique_ptr<sf::Shape> BaseShape;
};