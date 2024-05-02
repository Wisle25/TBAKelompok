#pragma once

#include "Core.h"
#include "Components/BaseComponent.h"

class State : public BaseComponent
{
public:
    State(BasePage* Page, const std::string& Name, const sf::Vector2f& Position);

private:
    std::string StateName;

    sf::Color Color;

    
};
