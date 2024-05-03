#pragma once

#include "Core.h"
#include "Components/Button.h"

class AutomataState : public Button
{
public:
    typedef Button Super;

    AutomataState(
        BasePage* Page, 
        const std::string& Name, 
        const sf::Vector2f& Position, 
        bool& bInOnReceivingTransition,
        bool bRandomizeColor = false
    );

    // ***===== Lifecycles =====*** //

    virtual void ReceiveEvent(const sf::Event& Event) override;

private:
    // ***===== Attributes =====*** //

    std::string StateName;
    std::set<AutomataState> Transitions;
    std::vector<sf::Vector2i> StartingPoints;

    int16_t CurrentStartingPoint = 0;

    sf::Color Color = COLOR;
    sf::Cursor Cursor;

    bool bPlaced = false;
    bool& bOnReceivingTransition;

public:
    Delegate<void(AutomataState*)> OnAddTransition;
    Delegate<void(AutomataState*)> OnReceivingTransition;

    void SetStartingPoints(const sf::Vector2i& GridCords);

    __forceinline const sf::Vector2i GetStartingPoint()
    {
        return StartingPoints[CurrentStartingPoint++];
    }

    __forceinline const sf::Vector2i GetGoalPoint()
    {
        return StartingPoints[1];
    }

    __forceinline std::string& GetStateName()
    {
        return StateName;
    }

    __forceinline const sf::Color& GetColor() const
    {
        return Color;
    }

    __forceinline void SetIsPlaced()
    {
        bPlaced = true;
    }
};
