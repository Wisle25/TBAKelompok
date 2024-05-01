#pragma once

#include "Core.h"
#include "Pages/BasePage.h"

class NumOnePage : public BasePage
{
public:
    typedef BasePage Super;
    
protected:
    virtual void CreateLayout() override;
};