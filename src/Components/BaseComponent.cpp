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
        GetApp()->GetFont(Properties.FontName),
        Properties.Size
    );
    Text->setColor(Properties.Color);
    Text->setOrigin(Text->getLocalBounds().width / 2.f, Text->getLocalBounds().height / 1.25f);
    Text->setPosition(Properties.Position);

    Texts.push_back(std::shared_ptr<sf::Text>(Text));
}

sf::Vector2f BaseComponent::CalculateByScreenPercent(const float X, const float Y)
{
    return {
        GetApp()->getSize().x * X / 100.f,
        GetApp()->getSize().y * Y / 100.f
    };
}

App* BaseComponent::GetApp() const
{
    return Page->GetApp();
}

void BaseComponent::AddChildComponent(BaseComponent* Child)
{
    ChildComponents.push_back(std::shared_ptr<BaseComponent>(Child));
}

sf::RoundedRectangleShape* BaseComponent::MakeRoundedRect(const FMakeShape& Properties)
{
    sf::RoundedRectangleShape* NewShape = new sf::RoundedRectangleShape(Properties.Size, Properties.BorderRadius, 8);
    
    NewShape->setOrigin(Properties.Size / 2.f);
    NewShape->setPosition(Properties.Position);
    NewShape->setFillColor(Properties.Color);
    NewShape->setOutlineColor(Properties.OutlineColor);
    NewShape->setOutlineThickness(Properties.OutlineThickness); 

    Shapes.push_back(std::shared_ptr<sf::RoundedRectangleShape>(NewShape));

    return NewShape;
}

sf::CircleShape* BaseComponent::MakeCircle(float Radius, const FMakeShape& Props)
{
    float ResposiveRadius = CalculateByScreenPercent(Radius, Radius).y;
    sf::CircleShape* NewCircle = new sf::CircleShape(ResposiveRadius);

    NewCircle->setOrigin(NewCircle->getLocalBounds().width / 2.f, NewCircle->getLocalBounds().width / 2.f);
    NewCircle->setPosition(Props.Position);
    NewCircle->setFillColor(Props.Color);
    NewCircle->setOutlineColor(Props.OutlineColor);
    NewCircle->setOutlineThickness(Props.OutlineThickness); 

    Shapes.push_back(std::shared_ptr<sf::CircleShape>(NewCircle));

    return NewCircle;
}

void BaseComponent::SetPosition(const sf::Vector2f& Position)
{
    Shapes[0]->setPosition(Position);
    Texts [0]->setPosition(Position);
}
