#pragma once

#include "Core.h"
#include "Components/Button.h"

enum class EAutomataState
{
    None,
    Hover,
    Pressed,
};

class AutomataState : public Button
{
public:
    typedef Button Super;

    AutomataState(BasePage* Page, const std::string& Name, const sf::Vector2f& Position);

private:
    // ***===== Attributes =====*** //

    std::string StateName;
    sf::Color Color;
    sf::Cursor Cursor;  

};
