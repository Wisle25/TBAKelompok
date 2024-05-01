#include "Button.h"
#include "Pages/BasePage.h"
#include "Shapes/RoundedRectangleShape.h"

Button* Button::MakeButton(BasePage* Page, const FMakeShape& ShapeProperties, const FMakeText& TextProperties)
{
    // Button
    Button* NewButton = new Button();

    NewButton->MakeShape<sf::RoundedRectangleShape>(ShapeProperties);

    if (TextProperties.TextString != "")
    {
        FMakeText FinalTextProperties = TextProperties;
        const sf::Uint8 TextSize = ShapeProperties.Size.y / 2.5f;
        FinalTextProperties.Size = TextSize;
        FinalTextProperties.Position = ShapeProperties.Position;

        NewButton->MakeText(Page, FinalTextProperties);
    }

    // Core
    NewButton->ButtonProperties = ShapeProperties;
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

        if (OnPressed.IsBinded())
        {
            OnPressed.Execute();

            // Change mouse cursor
            Cursor.loadFromSystem(sf::Cursor::Arrow);
            AppWindow->setMouseCursor(Cursor);
        }
    }
    // Clicked
    else if (State == ButtonState::Hover            &&
        Event.type == sf::Event::MouseButtonPressed && 
        Event.mouseButton.button == sf::Mouse::Left
    )
    {
        Shapes[0]->setFillColor(ButtonProperties.ThirdColor);

        State = ButtonState::Clicked;
    }
    // Hovered
    else if (Shapes[0]->getGlobalBounds().contains(MousePositionFloat))
    {
        State = ButtonState::Hover;

        Shapes[0]->setFillColor(ButtonProperties.SecondaryColor);

        // Change mouse cursor
        Cursor.loadFromSystem(sf::Cursor::Hand);
        AppWindow->setMouseCursor(Cursor);
    }
    // None
    else if (State != ButtonState::None)
    {
        State = ButtonState::None;

        Shapes[0]->setFillColor(ButtonProperties.Color);

        // Change mouse cursor
        Cursor.loadFromSystem(sf::Cursor::Arrow);
        AppWindow->setMouseCursor(Cursor);
    }
}
