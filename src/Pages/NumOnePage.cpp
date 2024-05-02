#include "NumOnePage.h"
#include "App.h"
#include "Automata/AutomataState.h"
#include "Components/OptionLayout.h"
#include "Components/GridLayout.h"

void NumOnePage::CreateLayout()
{
    Name = "NumOnePage";
    Nfa  = std::make_unique<NFA>();

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
    Option = std::make_shared<OptionLayout>(this);
    Option->GetOption(0)->OnClicked.Bind(this, &NumOnePage::AddOnPlacingAutomataState);

    AddComponent(Option);
    
    /** Grid */
    const FMakeShape GridShape = {
        .Size=CalculateByScreenPercent(70.f, 80.f),
        .Position=CalculateByScreenPercent(40.f, 50.f),
        .OutlineThickness=5.f
    };
    Grid = std::make_shared<GridLayout>(this, GridShape);
    AddComponent(Grid);
}

void NumOnePage::ReceiveEvent(const sf::Event& Event)
{
    Super::ReceiveEvent(Event);

    PlaceAutomata(Event);
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

    if (!bAutomataAdded)
    {
        bAutomataAdded = true;
        AddComponent(OnPlacingAutomataState);
    }

    OnPlacingAutomataState->SetPosition(GetApp()->GetMousePosition());
}

void NumOnePage::PlaceAutomata(const sf::Event& Event)
{
    if (!OnPlacingAutomataState) return;

    if (Grid->IsInBounds() && Event.type == sf::Event::MouseButtonPressed)
    {
        OnPlacingAutomataState->SetIsPlaced();
        Grid->MakeCellsAsObstacle(OnPlacingAutomataState->GetPosition(), 2);

        // Reset
        OnPlacingAutomataState.reset();
        bAutomataAdded         = false;
    }
}

void NumOnePage::AddTransition(AutomataState* State)
{
    if (bOnAddingTransition) return;
    
    bOnAddingTransition = true;
    Grid->SetStartPoint(State->GetPosition());
    Grid->SetPathColor(State->GetColor());
}

void NumOnePage::TransitionDestination(AutomataState* State)
{
    if (!bOnAddingTransition) return;

    bOnAddingTransition = false;
    Grid->SetGoalPoint(State->GetPosition());
    Grid->VisualizeTransition();
}

void NumOnePage::AddOnPlacingAutomataState()
{
    char StateName[10];
    sprintf(StateName, "Q%d", StateCount++);
    
    OnPlacingAutomataState = std::make_shared<AutomataState>(this, StateName, GetApp()->GetMousePosition(), bOnAddingTransition, true);
    OnPlacingAutomataState->OnAddTransition.Bind(this, &NumOnePage::AddTransition);
    OnPlacingAutomataState->OnReceivingTransition.Bind(this, &NumOnePage::TransitionDestination);
}
