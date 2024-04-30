#include "Button.h"
#include "Pages/BasePage.h"
#include "Shapes/RoundedRectangleShape.h"

Button* Button::MakeButton(BasePage* Page, const FMakeButton& Properties)
{

    // Button
    Button* NewButton = new Button();
    NewButton->BaseShape = std::make_unique<sf::RoundedRectangleShape>(Properties.Size, Properties.BorderRadius, 8);
    NewButton->BaseShape->setOrigin(Properties.Size / 2.f);
    NewButton->BaseShape->setPosition(Properties.Position);
    NewButton->BaseShape->setFillColor(Properties.Color);
    NewButton->BaseShape->setOutlineColor(Properties.OutlineColor);
    NewButton->BaseShape->setOutlineThickness(Properties.OutlineThickness);

    if (Properties.TextString != "")
    {
        NewButton->Font = std::make_unique<sf::Font>();
        NewButton->Font->loadFromFile("assets/" + Properties.FontName);

        const sf::Uint16 TextSize = Properties.Size.y / 2.5f;

        NewButton->Text = std::make_unique<sf::Text>(Properties.TextString, *NewButton->Font, TextSize);
        NewButton->Text->setColor(Properties.TextColor);
        NewButton->Text->setOrigin(NewButton->Text->getLocalBounds().width / 2.f, NewButton->Text->getLocalBounds().height / 1.5f);
        NewButton->Text->setPosition(Properties.Position);
    }

    // Core
    NewButton->ButtonProperties = Properties;
    NewButton->AppWindow = Page->GetAppWindow();

    return NewButton;
}

//////////////////////////////////////////////////////////
// ==================== Lifecycles ==================== //

void Button::ReceiveEvent(const sf::Event& Event)
{
    UpdateState(Event);
}

//////////////////////////////////////////////////////////
// ==================== Attributes ==================== //

void Button::UpdateState(const sf::Event& Event)
{
    const sf::Vector2i MousePosition = sf::Mouse::getPosition(*AppWindow);
    const sf::Vector2f MousePositionFloat = { static_cast<float>(MousePosition.x), static_cast<float>(MousePosition.y) };

    // Pressed
    if (State == ButtonState::Clicked                &&
        Event.type == sf::Event::MouseButtonReleased
    )
    {
        State = ButtonState::Pressed;
        OnPressed.Execute();        
    }
    // Clicked
    else if (State == ButtonState::Hover            &&
        Event.type == sf::Event::MouseButtonPressed && 
        Event.mouseButton.button == sf::Mouse::Left
    )
    {
        BaseShape->setFillColor(ButtonProperties.ActiveColor);

        State = ButtonState::Clicked;
    }
    // Hovered
    else if (BaseShape->getGlobalBounds().contains(MousePositionFloat))
    {
        State = ButtonState::Hover;

        BaseShape->setFillColor(ButtonProperties.HoverColor);

        // Change mouse cursor
        Cursor.loadFromSystem(sf::Cursor::Hand);
        AppWindow->setMouseCursor(Cursor);
    }
    // None
    else if (State != ButtonState::None)
    {
        State = ButtonState::None;

        BaseShape->setFillColor(ButtonProperties.Color);

        // Change mouse cursor
        Cursor.loadFromSystem(sf::Cursor::Arrow);
        AppWindow->setMouseCursor(Cursor);
    }
}
