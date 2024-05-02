#include "Automata/AutomataState.h"

AutomataState::AutomataState(BasePage* Page, const std::string& Name, const sf::Vector2f& Position):
    Super(Page),
    StateName(Name)
{
    ButtonProperties = {
        .Position=Position,
        .Color=sf::Color::Transparent,
        .SecondaryColor=sf::Color::Transparent,
        .ThirdColor=sf::Color::Transparent,
        .OutlineColor=COLOR,
        .OutlineThickness=5.f
    };

    // Shape
    sf::CircleShape* BaseCircle = MakeCircle(3.f, ButtonProperties);

    // Text
    MakeText({
        .TextString=StateName,
        .Size=CalculateTextScreenPercent(1.5f),
        .Color=COLOR,
        .Position=Position,
        .Style=sf::Text::Bold
    });
}
