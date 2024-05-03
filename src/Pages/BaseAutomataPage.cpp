#include "Pages/BaseAutomataPage.h"
#include "App.h"
#include "Automata/AutomataState.h"
#include "Components/GridLayout.h"
#include "Components/InputToaster.h"
#include "Components/OptionLayout.h"

void BaseAutomataPage::CreateLayout()
{
    Nfa  = std::make_unique<NFA>();

    BasePage::CreateLayout();

    // *** Texts *** //

    AddText({
        .TextString=Name,
        .Size=CalculateTextScreenPercent(2.5f),
        .Position=CalculateByScreenPercent(50.f, 5.f),
        .Style=sf::Text::Style::Bold | sf::Text::Style::Underlined
    });

    // *** Layout *** //

    /** Option Layout */
    Option = std::make_shared<OptionLayout>(this);
    Option->GetOption(0)->OnClicked.Bind(this, &BaseAutomataPage::AddOnPlacingAutomataState);

    AddComponent(Option);
    
    /** Grid */
    const FMakeShape GridShape = {
        .Size=CalculateByScreenPercent(70.f, 80.f),
        .Position=CalculateByScreenPercent(40.f, 50.f),
        .OutlineThickness=5.f
    };
    Grid = std::make_shared<GridLayout>(this, GridShape);
    AddComponent(Grid);

    TransitionInput = std::make_shared<InputToaster>(this, "Masukan Transisi: ", "Pisahkan dengan koma (,) saja");
    TransitionInput->OnSubmit.Bind(this, &BaseAutomataPage::AddTransitionSymbol);

    AddComponent(TransitionInput);
}

void BaseAutomataPage::ReceiveEvent(const sf::Event& Event)
{
    BasePage::ReceiveEvent(Event);

    PlaceAutomata(Event);
}

void BaseAutomataPage::Tick(const float DeltaTime)
{
    BasePage::Tick(DeltaTime);

    MoveAutomata();
}

////////////////////////////////////////////////////////
// ==================== Automata ==================== //

void BaseAutomataPage::MoveAutomata()
{
    if (!OnPlacingAutomataState) return;

    if (!bAutomataAdded)
    {
        bAutomataAdded = true;
        AddComponent(OnPlacingAutomataState);
    }

    OnPlacingAutomataState->SetPosition(GetApp()->GetMousePosition());
}

void BaseAutomataPage::PlaceAutomata(const sf::Event& Event)
{
    if (!OnPlacingAutomataState) return;

    if (Grid->IsInBounds() && Event.type == sf::Event::MouseButtonPressed)
    {
        const sf::Vector2f WorldPosition = OnPlacingAutomataState->GetPosition();

        OnPlacingAutomataState->SetIsPlaced();
        OnPlacingAutomataState->SetStartingPoints(Grid->GetGridCords(WorldPosition));
        Grid->MakeCellsAsObstacle(WorldPosition, 2);

        // Reset
        OnPlacingAutomataState.reset();
        bAutomataAdded         = false;
    }
}

void BaseAutomataPage::AddTransition(AutomataState* State)
{
    if (bOnAddingTransition) return;
    
    bOnAddingTransition = true;
    Grid->SetStartPoint(State->GetStartingPoint());
    Grid->SetPathColor(State->GetColor());
}

void BaseAutomataPage::TransitionDestination(AutomataState* State)
{
    if (!bOnAddingTransition) return;

    bOnAddingTransition = false;
    Grid           ->SetGoalPoint(State->GetGoalPoint());
    TransitionInput->ShowToaster();
}

void BaseAutomataPage::AddTransitionSymbol(const std::string& Transition)
{
    Grid->VisualizeTransition();

    // Also add text
    AddText({
        .TextString=Transition,
        .Size=CalculateTextScreenPercent(2.f),
        .Color=sf::Color::White,
        .Position=Grid->GetHalfTransition(
            CalculateByScreenPercent(3.f, 3.f).x
        ),
    });
}

void BaseAutomataPage::AddOnPlacingAutomataState()
{
    char StateName[10];
    sprintf(StateName, "Q%d", StateCount++);
    
    OnPlacingAutomataState = std::make_shared<AutomataState>(this, StateName, GetApp()->GetMousePosition(), bOnAddingTransition, true);
    OnPlacingAutomataState->OnAddTransition.Bind(this, &BaseAutomataPage::AddTransition);
    OnPlacingAutomataState->OnReceivingTransition.Bind(this, &BaseAutomataPage::TransitionDestination);
}
