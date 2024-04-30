#pragma once

#include "Core.h"
#include "Components/BaseComponent.h"

struct FMakeButton
{
    sf::Vector2f Size;
    sf::Vector2f Position;
};

class Button : public BaseComponent
{
public:
    static Button* MakeButton(const FMakeButton& Properties);
};