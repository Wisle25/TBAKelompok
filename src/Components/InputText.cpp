#include "InputText.h"
#include "App.h"

InputText::InputText(BasePage* Page, const FMakeShape& Props, const std::string& InLabel):
    Super(Page),
    Label(InLabel)
{
    MakeRoundedRect(Props);
    MakeText({
        .TextString="",
        .Size=CalculateTextScreenPercent(2.5f),
        .Color=sf::Color::White,
        .Position=Props.Position,
    });

    // Re-arrange position
    Texts[0]->setOrigin(0.f, 0.f);
    Texts[0]->setPosition(Props.Position.x - Props.Size.x / 2.f + 5.f, Props.Position.y - Props.Size.y / 2.f + 2.f);
    Texts[0]->setString(Label);
    Texts[0]->setFillColor(sf::Color(255, 255, 255, 100));
}

//////////////////////////////////////////////////////////
// ==================== Lifecycles ==================== //

void InputText::ReceiveEvent(const sf::Event& Event)
{
    if (State == InputState::OnFocus && Event.type == sf::Event::TextEntered)
    {
        // Delete
        if (Event.text.unicode == 8)
        {
            Value = Value.substr(0, Value.size() - 1);
        }
        // Normal
        else
        {
            Value += Event.text.unicode;
        }

        Texts[0]->setString(Value);
    }
    else if (Shapes[0]->getGlobalBounds().contains(GetApp()->GetMousePosition()) && 
        Event.type               == sf::Event::MouseButtonPressed           &&
        Event.mouseButton.button == sf::Mouse::Left
    )
    {
        State = InputState::OnFocus;
        Texts[0]->setString(Value);
        Texts[0]->setFillColor(sf::Color::White);

        Cursor.loadFromSystem(sf::Cursor::Text);
        GetApp()->setMouseCursor(Cursor);
    }
    else if (!Shapes[0]->getGlobalBounds().contains(GetApp()->GetMousePosition()) && 
        Event.type               == sf::Event::MouseButtonPressed           &&
        Event.mouseButton.button == sf::Mouse::Left
    )
    {
        State = InputState::None;

        Texts[0]->setString(Label);
        Texts[0]->setFillColor(sf::Color(255, 255, 255, 100));

        Cursor.loadFromSystem(sf::Cursor::Arrow);
        GetApp()->setMouseCursor(Cursor);
    }
}
