#include "Components/OptionLayout.h"
#include "Automata/AutomataState.h"

OptionLayout::OptionLayout(BasePage* Page):
    Super(Page)
{
    MakeRoundedRect({
        .Size=CalculateByScreenPercent(20.f, 75.f),
        .Position=CalculateByScreenPercent(88.f, 50.f),
        .Color=sf::Color::Transparent,
        .OutlineColor=COLOR,
        .OutlineThickness=5.f,
    });

    AddChildComponent(std::make_shared<AutomataState>(
        Page,
        "State",
        CalculateByScreenPercent(88.f, 30.f))
    );
}

Button* OptionLayout::GetOption(int Index) const
{
    return dynamic_cast<Button*>(ChildComponents[Index].get());
}
