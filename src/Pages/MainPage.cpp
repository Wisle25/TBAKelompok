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
        .Size=24,
        .Position=CalculateByScreenPercent(50.f, 5.f),
        .Style=sf::Text::Style::Bold | sf::Text::Style::Underlined
    });

    // *** Buttons *** //

    Button* NumOne = MakeButton({
        .Size={ 280.f, 50.f }, 
        .Position=CalculateByScreenPercent(50.f, 20.f),
    }, {
        .TextString="NFA or e-NFA to DFA"
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
