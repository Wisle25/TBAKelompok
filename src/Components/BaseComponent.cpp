#include "BaseComponent.h"
#include "App.h"
#include "Pages/BasePage.h"
#include "Shapes/RoundedRectangleShape.h"

BaseComponent::BaseComponent(BasePage* Page):
    Page(Page)
{

}

void BaseComponent::ReceiveEvent(const sf::Event& Event)
{
    for (const auto& Child : ChildComponents)
        Child->ReceiveEvent(Event);
}

void BaseComponent::Tick(const float DeltaTime)
{
    for (const auto& Child : ChildComponents)    
        Child->Tick(DeltaTime);
}

void BaseComponent::draw(sf::RenderTarget& Target, sf::RenderStates States) const
{
    for (const auto& Shape : Shapes)
        Target.draw(*Shape);

    for (const auto& Text : Texts)
        Target.draw(*Text);

    for (const auto& Child : ChildComponents)
        Target.draw(*Child);
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
        Page->GetApp()->getSize().x * X / 100.f,
        Page->GetApp()->getSize().y * Y / 100.f
    };
}

void BaseComponent::AddChildComponent(BaseComponent* Child)
{
    ChildComponents.push_back(std::unique_ptr<BaseComponent>(std::move(Child)));
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

sf::CircleShape* BaseComponent::MakeCircle(float Radius, const FMakeShape& Props)
{
    sf::CircleShape* NewCircle = new sf::CircleShape(Radius);

    NewCircle->setOrigin(NewCircle->getLocalBounds().width / 2.f, NewCircle->getLocalBounds().width / 2.f);
    NewCircle->setPosition(Props.Position);
    NewCircle->setFillColor(Props.Color);
    NewCircle->setOutlineColor(Props.OutlineColor);
    NewCircle->setOutlineThickness(Props.OutlineThickness); 

    Shapes.push_back(std::unique_ptr<sf::CircleShape>(std::move(NewCircle)));

    return NewCircle;
}
