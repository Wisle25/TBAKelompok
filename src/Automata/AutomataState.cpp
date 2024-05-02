#include "Automata/AutomataState.h"
#include "App.h"

AutomataState::AutomataState(BasePage* Page, const std::string& Name, const sf::Vector2f& Position, bool& bInOnReceivingTransition, bool bRandomizeColor):
    Super(Page),
    StateName(Name),
    bOnReceivingTransition(bInOnReceivingTransition)
{
    if (bRandomizeColor)
    {
        uint8_t Red   = App::RandRange(0, 255);
        uint8_t Green = App::RandRange(0, 255);
        uint8_t Blue  = App::RandRange(0, 255);

        Color = sf::Color(Red, Green, Blue);
    }

    ButtonProperties = {
        .Position=Position,
        .Color=sf::Color::Transparent,
        .SecondaryColor=sf::Color::Transparent,
        .ThirdColor=sf::Color::Transparent,
        .OutlineColor=Color,
        .OutlineThickness=5.f
    };

    // Shape
    sf::CircleShape* BaseCircle = MakeCircle(3.f, ButtonProperties);

    // Text
    MakeText({
        .TextString=StateName,
        .Size=CalculateTextScreenPercent(1.5f),
        .Color=Color,
        .Position=Position,
        .Style=sf::Text::Bold
    });
}

//////////////////////////////////////////////////////////
// ==================== Lifecycles ==================== //

void AutomataState::ReceiveEvent(const sf::Event& Event)
{
    Super::ReceiveEvent(Event);

    if (State != ButtonState::Clicked) return;

    if (bOnReceivingTransition && OnReceivingTransition.IsBinded())
    {
        OnReceivingTransition.Execute(this);
    }
    else if (bPlaced && OnAddTransition.IsBinded())
    {
        OnAddTransition.Execute(this);
    }
}
