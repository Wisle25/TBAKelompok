#include "MainPage.h"
#include "App.h"
#include "Components/Button.h"
#include "Pages/NumOnePage.h"

void MainPage::CreateLayout()
{
    Name = "MainPage";
    Super::CreateLayout();
    
    // *** Text *** //
    AddText({
        .TextString="Tugas Kelompok TBA",
        .Size=static_cast<uint16_t>(CalculateByScreenPercent(8.f, 8.f).y),
        .Position=CalculateByScreenPercent(50.f, 8.f),
        .Style=sf::Text::Style::Bold | sf::Text::Style::Underlined
    });

    // *** Buttons *** //

    Button* NumOne = MakeButton({
        .Size=CalculateByScreenPercent(28.5f, 6.5f), 
        .Position=CalculateByScreenPercent(50.f, 22.5f),
    }, {
        .TextString="Convert NFA or e-NFA to DFA"
    });
    NumOne->OnClicked.Bind(this, &MainPage::NumOneOnClicked);
}

///////////////////////////////////////////////
// ================ Buttons ================ //

void MainPage::NumOneOnClicked()
{
    GetApp()->GoToPage<NumOnePage>();
}

void MainPage::NumTwoOnClicked()
{
    
}

void MainPage::NumThreeOnClicked()
{
    
}

void MainPage::NumFourOnClicked()
{
    
}
