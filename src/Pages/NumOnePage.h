#pragma once

#include "Core.h"
#include "Pages/BasePage.h"

class AutomataState;

class NumOnePage : public BasePage
{
public:
    typedef BasePage Super;
    
public:
    // ***===== Lifecycles =====*** //

    virtual void Tick(const float DeltaTime) override;

protected:
    virtual void CreateLayout() override;

private:
    // ***===== Automata =====*** //

    AutomataState* OnPlacingAutomataState;

    void MoveAutomata();

public:
    void AddOnPlacingAutomataState();
    // ***===== End Automata =====*** //
};