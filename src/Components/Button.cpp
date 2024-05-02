#include "Button.h"
#include "App.h"

Button::Button(BasePage* Page, const FMakeShape& ShapeProperties, const FMakeText& TextProperties):
    Super(Page)
{
    // Button
    MakeRoundedRect(ShapeProperties);

    if (TextProperties.TextString != "")
    {
        FMakeText FinalTextProperties = TextProperties;
        const uint8_t TextSize = ShapeProperties.Size.y / 2.5f;
        FinalTextProperties.Size = TextSize;
        FinalTextProperties.Position = ShapeProperties.Position;

        MakeText(FinalTextProperties);
    }

    // Core
    ButtonProperties = ShapeProperties;
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
    if (State == ButtonState::Hover            &&
        Event.type == sf::Event::MouseButtonPressed && 
        Event.mouseButton.button == sf::Mouse::Left
    )
    {
        State = ButtonState::Clicked;

        Shapes[0]->setFillColor(ButtonProperties.ThirdColor);
        if (ButtonProperties.OutlineThickness > 0.f)
        {
            Shapes[0]->setOutlineColor(ButtonProperties.OutlineThirdColor);
        }

        if (OnClicked.IsBinded())
        {
            OnClicked.Execute();

            // Change mouse cursor
            Cursor.loadFromSystem(sf::Cursor::Arrow);
            GetApp()->setMouseCursor(Cursor);
        }
    }
    // Hovered
    else if (Shapes[0]->getGlobalBounds().contains(GetApp()->GetMousePosition()))
    {
        State = ButtonState::Hover;

        Shapes[0]->setFillColor(ButtonProperties.SecondaryColor);

        if (ButtonProperties.OutlineThickness > 0.f)
        {
            Shapes[0]->setOutlineColor(ButtonProperties.OutlineSecondaryColor);
        }

        // Change mouse cursor
        Cursor.loadFromSystem(sf::Cursor::Hand);
        GetApp()->setMouseCursor(Cursor);
    }
    // None
    else if (State != ButtonState::None)
    {
        State = ButtonState::None;

        Shapes[0]->setFillColor(ButtonProperties.Color);
        if (ButtonProperties.OutlineThickness > 0.f)
        {
            Shapes[0]->setOutlineColor(ButtonProperties.OutlineColor);
        }

        // Change mouse cursor
        Cursor.loadFromSystem(sf::Cursor::Arrow);
        GetApp()->setMouseCursor(Cursor);
    }
}
