#include "NumOnePage.h"
#include "Components/OptionLayout.h"

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

    /* Option Layout */
    // AddComponent(new OptionLayout());
}
