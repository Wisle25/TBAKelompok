#pragma once

#include "Core.h"
#include "Pages/BasePage.h"

class MainPage : public BasePage
{
public:
    typedef BasePage Super;

protected:
    // ***===== Layouting =====*** //

    virtual void CreateLayout() override;

private:
    // ***===== Buttons =====*** //

    void NumOneOnPressed();
    void NumTwoOnPressed();
    void NumThreeOnPressed();
    void NumFourOnPressed();
};
