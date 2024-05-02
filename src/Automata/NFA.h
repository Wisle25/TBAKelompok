#pragma once

#include "Core.h"

class NFA 
{
public:
    // Add a transition from state 'from' To state 'To' on input 'symbol'
    __forceinline void AddTransition(std::string From, char Symbol, std::string To) 
    {
        Transitions[{From, Symbol}].insert(To);
    }

    // Add an accept state
    __forceinline void AddAcceptState(std::string State) 
    {
        AcceptStates.insert(State);
    }

    // Check if the NFA accepts the input string
    bool Accept(std::string Input);

private:
    std::map<std::pair<std::string, char>, std::set<std::string>> Transitions;
    std::set<std::string> AcceptStates;

};