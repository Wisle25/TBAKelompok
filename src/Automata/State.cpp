#include "State.h"

State::State(BasePage* Page, const std::string& Name, const sf::Vector2f& Position):
    Super(Page),
    StateName(Name)
{
    // Shape
    sf::CircleShape* BaseCircle = MakeCircle(30.f, {
        .Position=Position,
        .Color=sf::Color::Transparent,
        .OutlineColor=sf::Color::White,
        .OutlineThickness=5.f
    });

    // Text
    MakeText({
        .TextString=StateName,
        .Color=sf::Color::White,
        .Position=Position
    });
}
