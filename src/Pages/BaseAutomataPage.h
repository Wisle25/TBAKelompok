#pragma once

#include "Core.h"
#include "Automata/NFA.h"
#include "Pages/BasePage.h"

class AutomataState;
class GridLayout;
class NFA;
class OptionLayout;
class InputToaster;

class BaseAutomataPage : public BasePage
{
    
public:
    typedef BaseAutomataPage Super;

    // ***===== Lifecycles =====*** //

    virtual void ReceiveEvent(const sf::Event& Event) override;
    virtual void Tick(const float DeltaTime) override;

protected:
    virtual void CreateLayout() override;

    // ***===== Components =====*** //

    std::shared_ptr<OptionLayout> Option;
    std::shared_ptr<GridLayout> Grid;
    std::shared_ptr<InputToaster> TransitionInput;

    // ***===== Automata =====*** //

    std::unique_ptr<NFA> Nfa;

    std::shared_ptr<AutomataState> OnPlacingAutomataState;

    bool bAutomataAdded      = false;
    bool bOnAddingTransition = false;

    int16_t StateCount = 0;

    void AddOnPlacingAutomataState();
    void MoveAutomata();
    void PlaceAutomata(const sf::Event& Event);
    void AddTransition(AutomataState* FromState);
    void TransitionDestination(AutomataState* ToState);
    void AddTransitionSymbol(const std::string& Transition);
};