#include "MainPage.h"
#include "../Components/Button.h"

MainPage::MainPage()
{
    CreateButtons();    
}

void MainPage::CreateButtons()
{
    Button* TestBtn = Button::MakeButton({
        .Size={ 40.f, 20.f }, 
        .Position={100.f, 100.f }}
    );

    AddComponent(TestBtn);
}
