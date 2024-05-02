#pragma once

#include "Core.h"

class App;
class BasePage;

namespace sf
{
class RoundedRectangleShape;
}

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
    sf::Color OutlineColor = COLOR;
    sf::Color OutlineSecondaryColor = SECONDARY_COLOR;
    sf::Color OutlineThirdColor = THIRD_COLOR;
    float OutlineThickness = 0.f;
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

    BasePage* Page;

    sf::Vector2f CalculateByScreenPercent(const float X, const float Y);
    
    __forceinline sf::Uint16 CalculateTextScreenPercent(float Size)
    {
        return static_cast<sf::Uint16>(CalculateByScreenPercent(Size, Size).y);
    }
    App* GetApp() const;

    // ***===== End References =====*** //

protected:
    // ***===== SFML =====*** //
    
    std::vector<std::shared_ptr<sf::Shape>> Shapes;
    std::vector<std::shared_ptr<sf::Text>> Texts;
    std::vector<std::shared_ptr<BaseComponent>> ChildComponents;

    void AddChildComponent(const std::shared_ptr<BaseComponent>& Child);
    sf::RoundedRectangleShape* MakeRoundedRect(const FMakeShape& Properties);
    sf::CircleShape*           MakeCircle(float Radius, const FMakeShape& Props);

    void MakeText(const FMakeText& Properties);

public:
    void SetPosition(const sf::Vector2f& Position);
};