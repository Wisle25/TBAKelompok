#pragma once

#include "Core.h"
#include "Pages/BasePage.h"

class MainPage : public BasePage
{

protected:
    // ***===== Layouting =====*** //

    virtual void CreateLayout() override;

private:
    // ***===== Buttons =====*** //

    void NumOneOnClicked();
    void NumTwoOnClicked();
    void NumThreeOnClicked();
    void NumFourOnClicked();
};
