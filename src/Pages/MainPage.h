#pragma once

#include "Core.h"
#include "Pages/BasePage.h"

class MainPage : public BasePage
{
public:
    typedef BasePage Super;

    MainPage(App* Application);

private:
    // ***===== Buttons =====*** //

    void CreateButtons();

    void TestBtnOnPressed()
    {
        std::cout << "DELEGATE FROM MAIN PAGE!\n";
    }
};
