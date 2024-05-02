#include "Automata/NFA.h"

bool NFA::Accept(std::string Input) 
{
    std::set<std::string> CurrentStates = {"q0"}; // Start from the initial state "q0"

    // For each Symbol in the Input string
    for (char Symbol : Input) 
    {
        std::set<std::string> NextStates;

        // Find all possible next states for the current Input Symbol
        for (std::string State : CurrentStates) 
        {
            for (std::string nextState : Transitions[{State, Symbol}]) 
            {
                NextStates.insert(nextState);
            }
        }

        // Update current States
        CurrentStates = NextStates;
    }

    // Check if any of the current States are accept States
    for (std::string State : CurrentStates) 
    {
        if (AcceptStates.count(State)) 
        {
            return true;
        }
    }

    return false;
}
