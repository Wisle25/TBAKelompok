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
    uint16_t Size = 12;
    sf::Color Color = sf::Color::White;
    sf::Vector2f Position;
    uint32_t Style = sf::Text::Style::Regular;
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
    
    __forceinline uint16_t CalculateTextScreenPercent(float Size)
    {
        return static_cast<uint16_t>(CalculateByScreenPercent(Size, Size).y);
    }
    App* GetApp() const;

    // ***===== End References =====*** //

protected:
    // ***===== SFML =====*** //
    
    bool bDisableTick  = false;
    bool bDisableEvent = false;
    bool bDisableDraw  = false;

    std::vector<std::shared_ptr<sf::Shape>> Shapes;
    std::vector<std::shared_ptr<sf::Text>> Texts;
    std::vector<std::shared_ptr<BaseComponent>> ChildComponents;

    void AddChildComponent(const std::shared_ptr<BaseComponent>& Child);
    sf::RoundedRectangleShape* MakeRoundedRect(const FMakeShape& Properties);
    sf::CircleShape*           MakeCircle(float Radius, const FMakeShape& Props);

    void MakeText(const FMakeText& Properties);

public:
    __forceinline sf::Vector2f GetPosition() const
    {
        return Shapes[0]->getPosition();
    }
    void SetPosition(const sf::Vector2f& Position);
};