#include "NumOnePage.h"
#include "Components/OptionLayout.h"
#include "Components/GridLayout.h"

void NumOnePage::CreateLayout()
{
    Name="NumOnePage";
    Super::CreateLayout();

    // *** Texts *** //

    AddText({
        .TextString="Konversi e-NFA atau NFA ke bentuk DFA",
        .Size=24,
        .Position=SetPositionPercent(50.f, 5.f),
        .Style=sf::Text::Style::Bold | sf::Text::Style::Underlined
    });

    // *** Layout *** //

    AddComponent(new OptionLayout(this));
    AddComponent(new GridLayout(this, {
        .Size=SetPositionPercent(70.f, 80.f),
        .Position=SetPositionPercent(40.f, 50.f),
        .OutlineThickness=5.f
    }));
}
