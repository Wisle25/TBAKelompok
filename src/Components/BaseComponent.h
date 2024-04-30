#pragma once

#include "Core.h"

class BaseComponent : public sf::Drawable
{
public:
    BaseComponent() {}
    virtual ~BaseComponent() {}

    // ***===== Lifecycles =====*** //
    virtual void ReceiveEvent(const sf::Event& Event) {};
    virtual void Tick(const float DeltaTime) {}
    virtual void draw(sf::RenderTarget& Target, sf::RenderStates States) const override;

protected:
    // ***===== SFML =====*** //
    
    std::unique_ptr<sf::Shape> BaseShape;
    std::unique_ptr<sf::Font> Font;
    std::unique_ptr<sf::Text> Text;
};