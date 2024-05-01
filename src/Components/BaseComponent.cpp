#include "BaseComponent.h"
#include "App.h"
#include "Pages/BasePage.h"

BaseComponent::BaseComponent(BasePage* Page):
    Application(Page->GetApp())
{

}

void BaseComponent::draw(sf::RenderTarget& Target, sf::RenderStates States) const
{
    for (const auto& Shape : Shapes)
        Target.draw(*Shape);

    for (const auto& Text : Texts)
        Target.draw(*Text);
}

void BaseComponent::MakeText(BasePage* Page, const FMakeText& Properties)
{
    if (!Application)
        Application = Page->GetApp();

    sf::Text* Text = new sf::Text(
        Properties.TextString,
        Application->GetFont(Properties.FontName),
        Properties.Size
    );
    Text->setColor(Properties.Color);
    Text->setOrigin(Text->getLocalBounds().width / 2.f, Text->getLocalBounds().height / 1.25f);
    Text->setPosition(Properties.Position);

    Texts.push_back(std::unique_ptr<sf::Text>(std::move(Text)));
}

sf::Vector2f BaseComponent::CalculateByScreenPercent(const float X, const float Y)
{
    return {
        Application->GetAppWindow()->getSize().x * X / 100.f,
        Application->GetAppWindow()->getSize().y * Y / 100.f
    };
}
