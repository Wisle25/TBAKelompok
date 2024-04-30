#include "MainPage.h"
#include "Components/Button.h"

MainPage::MainPage(App* Application):
    Super(Application)
{
    CreateButtons();  
}

void MainPage::CreateButtons()
{
    Button* TestBtn = Button::MakeButton(this, {
        .Size={ 130.f, 60.f }, 
        .Position=SetPositionPercent(50.f, 10.f),
        .BorderRadius=8.f,
        .TextString="Hello!"
    });
    TestBtn->OnPressed.Bind(this, &MainPage::TestBtnOnPressed);

    AddComponent(TestBtn);
}
