#include "MainPage.h"
#include "App.h"
#include "Components/Button.h"
#include "Pages/NumOnePage.h"
#include "Pages/NumFourPage.h"

void MainPage::CreateLayout()
{
    BasePage::CreateLayout();
    
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

    Button* NumFour = MakeButton({
        .Size=CalculateByScreenPercent(28.5f, 6.5f), 
        .Position=CalculateByScreenPercent(50.f, 50.f),
    }, {
        .TextString="Cek Equivalensi dua DFA"
    });
    NumFour->OnClicked.Bind(this, &MainPage::NumFourOnClicked);
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
    GetApp()->GoToPage<NumFourPage>();
}
