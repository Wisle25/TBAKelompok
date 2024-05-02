#pragma once

#include "Core.h"

namespace sf
{
class RoundedRectangleShape;
}

class BasePage;

struct FMakeText
{
    const std::string& TextString = "";
    const std::string& FontName   = "FiraCode-Regular";
    sf::Uint16 Size = 12;
    sf::Color Color = sf::Color::White;
    sf::Vector2f Position;
    sf::Uint32 Style = sf::Text::Style::Regular;
};

struct FMakeShape
{
    sf::Vector2f Size;
    sf::Vector2f Position;
    sf::Color Color = COLOR;
    sf::Color SecondaryColor = SECONDARY_COLOR;
    sf::Color ThirdColor     = THIRD_COLOR;
    sf::Color OutlineColor = sf::Color::Transparent;
    float OutlineThickness = 1.f;
    float BorderRadius = 5.f;
};

class BaseComponent : public sf::Drawable
{
public:
    typedef BaseComponent Super;

    BaseComponent(BasePage* Page);

    // ***===== Lifecycles =====*** //
    virtual void ReceiveEvent(const sf::Event& Event);
    virtual void Tick(const float DeltaTime);
    virtual void draw(sf::RenderTarget& Target, sf::RenderStates States) const override;

protected:
    // ***===== References =====*** //

    std::shared_ptr<BasePage> Page;

    sf::Vector2f CalculateByScreenPercent(const float X, const float Y);

    // ***===== End References =====*** //

protected:
    // ***===== SFML =====*** //
    
    std::vector<std::unique_ptr<sf::Shape>> Shapes;
    std::vector<std::unique_ptr<sf::Text>> Texts;
    std::vector<std::unique_ptr<BaseComponent>> ChildComponents;

    void AddChildComponent(BaseComponent* Child);
    sf::RoundedRectangleShape* MakeRoundedRect(const FMakeShape& Properties);
    sf::CircleShape*           MakeCircle(float Radius, const FMakeShape& Props);

    void MakeText(const FMakeText& Properties);
};