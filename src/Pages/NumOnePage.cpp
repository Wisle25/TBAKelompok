#include "NumOnePage.h"
#include "App.h"
#include "Automata/AutomataState.h"
#include "Components/OptionLayout.h"
#include "Components/GridLayout.h"

void NumOnePage::CreateLayout()
{
    Name="NumOnePage";
    Super::CreateLayout();

    // *** Texts *** //

    AddText({
        .TextString="Konversi e-NFA atau NFA ke bentuk DFA",
        .Size=CalculateTextScreenPercent(2.5f),
        .Position=CalculateByScreenPercent(50.f, 5.f),
        .Style=sf::Text::Style::Bold | sf::Text::Style::Underlined
    });

    // *** Layout *** //

    /** Option Layout */
    OptionLayout* Option = new OptionLayout(this);
    Option->GetOption(0)->OnPressed.Bind(this, &NumOnePage::AddOnPlacingAutomataState);

    AddComponent(Option);
    
    /** Grid */
    AddComponent(new GridLayout(this, {
        .Size=CalculateByScreenPercent(70.f, 80.f),
        .Position=CalculateByScreenPercent(40.f, 50.f),
        .OutlineThickness=5.f
    }));
}

void NumOnePage::Tick(const float DeltaTime)
{
    Super::Tick(DeltaTime);

    MoveAutomata();
}

////////////////////////////////////////////////////////
// ==================== Automata ==================== //

void NumOnePage::MoveAutomata()
{
    if (!OnPlacingAutomataState) return;

    OnPlacingAutomataState->SetPosition(GetApp()->GetMousePosition());
}

void NumOnePage::AddOnPlacingAutomataState()
{
    OnPlacingAutomataState  = new AutomataState(this, "Q0", GetApp()->GetMousePosition());
}
