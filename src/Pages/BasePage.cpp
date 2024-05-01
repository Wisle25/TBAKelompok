#include "BasePage.h"
#include "App.h"
#include "Components/Button.h"

//////////////////////////////////////////////////
// ================ Lifecycles ================ //

void BasePage::Prepare(std::shared_ptr<App> InApplication)
{
    Application = InApplication;

    CreateLayout();
}

void BasePage::ReceiveEvent(const sf::Event& Event)
{
    for (const auto& Component : Components)
        Component->ReceiveEvent(Event);
}

void BasePage::Tick(const float DeltaTime)
{
    for (const auto& Component : Components)
        Component->Tick(DeltaTime);
}

void BasePage::Draw(sf::RenderTarget* RenderTarget)
{
    for (const auto& Component : Components)
        RenderTarget->draw(*Component);

    for (const auto& Text : Texts)
        RenderTarget->draw(*Text);
}

////////////////////////////////////////////////////
// ================ User Interfaces ================ //

Button* BasePage::MakeButton(const FMakeShape& ShapeProperties, const FMakeText& TextProperties)
{
    Button* NewButton = new Button(this, ShapeProperties, TextProperties);

    AddComponent(NewButton);

    return NewButton;
}

void BasePage::AddText(const FMakeText& Properties)
{

    std::unique_ptr<sf::Text> NewText = std::make_unique<sf::Text>(
        Properties.TextString,
        Application->GetFont(Properties.FontName),
        Properties.Size
    );

    NewText->setFillColor(Properties.Color);
    NewText->setOrigin(NewText->getLocalBounds().width / 2.f, NewText->getLocalBounds().height / 1.5f);
    NewText->setPosition(Properties.Position);
    NewText->setStyle(Properties.Style);

    Texts.push_back(std::move(NewText));
}

void BasePage::CreateLayout()
{
    // *** Buttons *** //

    Button* BackButton = MakeButton({
        .Size={ 80.f, 30.f }, 
        .Position=CalculateByScreenPercent(95.f, 95.f)
    }, {
        .TextString="Keluar"
    });

    BackButton->OnPressed.Bind(this, &BasePage::QuitPage);
}

////////////////////////////////////////////////////
// ==================== ?/?? ==================== //

sf::Vector2f BasePage::CalculateByScreenPercent(const float X, const float Y)
{
    return {
        Application->GetAppWindow()->getSize().x * X / 100.f,
        Application->GetAppWindow()->getSize().y * Y / 100.f
    };
}


void BasePage::QuitPage()
{
    Application->GoBackPage();
}
