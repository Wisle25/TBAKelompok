#pragma once

#include "Core.h"
#include "Automata/NFA.h"
#include "Pages/BasePage.h"

class AutomataState;
class GridLayout;
class NFA;
class OptionLayout;

class NumOnePage : public BasePage
{
public:
    typedef BasePage Super;
    
public:
    // ***===== Lifecycles =====*** //

    virtual void ReceiveEvent(const sf::Event& Event) override;
    virtual void Tick(const float DeltaTime) override;

protected:
    virtual void CreateLayout() override;

private:
    // ***===== Components =====*** //

    std::shared_ptr<OptionLayout> Option;
    std::shared_ptr<GridLayout> Grid;

    // ***===== Automata =====*** //

    std::unique_ptr<NFA> Nfa;

    std::shared_ptr<AutomataState> OnPlacingAutomataState;

    bool bAutomataAdded      = false;
    bool bOnAddingTransition = false;

    int16_t StateCount = 0;

    void MoveAutomata();
    void PlaceAutomata(const sf::Event& Event);
    void AddTransition(AutomataState* FromState);
    void TransitionDestination(AutomataState* ToState);

public:
    void AddOnPlacingAutomataState();
    // ***===== End Automata =====*** //
};