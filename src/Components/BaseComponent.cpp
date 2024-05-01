#include "BaseComponent.h"
#include "App.h"
#include "Pages/BasePage.h"
#include "Shapes/RoundedRectangleShape.h"

BaseComponent::BaseComponent(BasePage* Page):
    Page(Page)
{

}

void BaseComponent::draw(sf::RenderTarget& Target, sf::RenderStates States) const
{
    for (const auto& Shape : Shapes)
        Target.draw(*Shape);

    for (const auto& Text : Texts)
        Target.draw(*Text);
}

void BaseComponent::MakeText(const FMakeText& Properties)
{
    sf::Text* Text = new sf::Text(
        Properties.TextString,
        Page->GetApp()->GetFont(Properties.FontName),
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
        Page->GetApp()->GetAppWindow()->getSize().x * X / 100.f,
        Page->GetApp()->GetAppWindow()->getSize().y * Y / 100.f
    };
}

sf::RoundedRectangleShape* BaseComponent::MakeRoundedRect(const FMakeShape& Properties)
{
    sf::RoundedRectangleShape* NewShape = new sf::RoundedRectangleShape(Properties.Size, Properties.BorderRadius, 8);
    
    NewShape->setOrigin(Properties.Size / 2.f);
    NewShape->setPosition(Properties.Position);
    NewShape->setFillColor(Properties.Color);
    NewShape->setOutlineColor(Properties.OutlineColor);
    NewShape->setOutlineThickness(Properties.OutlineThickness); 

    Shapes.push_back(std::unique_ptr<sf::RoundedRectangleShape>(std::move(NewShape)));

    return NewShape;
}