#pragma once

#include "Core.h"
#include "Components/BaseComponent.h"

class Button;

class OptionLayout : public BaseComponent
{
public:
    OptionLayout(BasePage* Page);

    Button* GetOption(int Index) const;
};
