#pragma once

#include "Core.h"
#include "Pages/BaseAutomataPage.h"

class NumOnePage : public BaseAutomataPage
{
public:
    NumOnePage():
        Super()
    {
        Name = "Konversi e-NFA atau NFA ke bentuk DFA";
    }
};
