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
        .Size=static_cast<sf::Uint16>(CalculateByScreenPercent(8.f, 8.f).y),
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
    NumOne->OnPressed.Bind(this, &MainPage::NumOneOnPressed);
}

///////////////////////////////////////////////
// ================ Buttons ================ //

void MainPage::NumOneOnPressed()
{
    GetApp()->GoToPage<NumOnePage>();
}

void MainPage::NumTwoOnPressed()
{
    
}

void MainPage::NumThreeOnPressed()
{
    
}

void MainPage::NumFourOnPressed()
{
    
}
