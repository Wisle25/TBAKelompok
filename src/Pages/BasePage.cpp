#include "BasePage.h"
#include "App.h"
#include "Components/Button.h"

//////////////////////////////////////////////////
// ================ Lifecycles ================ //

void BasePage::Prepare(App* InApplication)
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
    std::shared_ptr<Button> NewButton = std::make_shared<Button>(this, ShapeProperties, TextProperties);
    AddComponent(NewButton);

    return NewButton.get();
}

void BasePage::AddText(const FMakeText& Properties)
{

    std::shared_ptr<sf::Text> NewText = std::make_shared<sf::Text>(
        Properties.TextString,
        Application->GetFont(Properties.FontName),
        Properties.Size
    );

    NewText->setFillColor(Properties.Color);
    NewText->setOrigin(NewText->getLocalBounds().width / 2.f, NewText->getLocalBounds().height / 1.5f);
    NewText->setPosition(Properties.Position);
    NewText->setStyle(Properties.Style);

    Texts.push_back(NewText);
}

void BasePage::CreateLayout()
{
    // *** Buttons *** //

    Button* BackButton = MakeButton({
        .Size=CalculateByScreenPercent(8.5f, 4.5f), 
        .Position=CalculateByScreenPercent(90.f, 95.f)
    }, {
        .TextString="Keluar"
    });

    BackButton->OnClicked.Bind(this, &BasePage::QuitPage);
}

////////////////////////////////////////////////////
// ==================== ?/?? ==================== //

sf::Vector2f BasePage::CalculateByScreenPercent(const float X, const float Y)
{
    return {
        Application->getSize().x * X / 100.f,
        Application->getSize().y * Y / 100.f
    };
}

void BasePage::QuitPage()
{
    Application->GoBackPage();
}
