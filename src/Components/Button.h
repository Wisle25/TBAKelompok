#pragma once

#include "Core.h"
#include "Components/BaseComponent.h"

class BasePage;

struct FMakeButton
{
    // Container
    sf::Vector2f Size;
    sf::Vector2f Position;
    sf::Color Color = sf::Color(237, 148, 85);
    sf::Color HoverColor = sf::Color(255, 187, 112);
    sf::Color ActiveColor = sf::Color(255, 236, 158);
    sf::Color OutlineColor = sf::Color::Transparent;
    float OutlineThickness = 1.f;
    float BorderRadius = 0.f;

    // Text
    sf::Color TextColor = sf::Color::Black;
    std::string FontName = "FiraCode-Regular.ttf";
    std::string TextString = "";
};

enum class ButtonState : sf::Uint8 
{
    None,
    Hover,
    Clicked,
    Pressed
};

class Button : public BaseComponent
{
public:
    Button() {}
    virtual ~Button() override {}

    static Button* MakeButton(BasePage* Page, const FMakeButton& Properties);

    // ***===== Lifecycles =====*** //

    virtual void ReceiveEvent(const sf::Event& Event) override;

    // ***===== Attributes =====*** //

    FMakeButton ButtonProperties;

    Delegate<void()> OnPressed;

private:
    sf::Cursor Cursor;
    ButtonState State = ButtonState::None;

    void UpdateState(const sf::Event& Event);
    // ***===== End Attributes =====*** //

    // ***===== References =====*** //

    std::shared_ptr<sf::RenderWindow> AppWindow;
};