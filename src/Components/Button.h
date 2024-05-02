#pragma once

#include "Core.h"
#include "Components/BaseComponent.h"

enum class ButtonState : sf::Uint8 
{
    None,
    Hover,
    Clicked
};

class Button : public BaseComponent
{
public:

    Button(BasePage* Page):
        Super(Page) {}
    Button(BasePage* Page, const FMakeShape& ShapeProperties, const FMakeText& TextProperties);

    // ***===== Lifecycles =====*** //

    virtual void ReceiveEvent(const sf::Event& Event) override;

    // ***===== Attributes =====*** //

    FMakeShape ButtonProperties;

    Delegate<void()> OnClicked;

private:
    sf::Cursor Cursor;
    ButtonState State = ButtonState::None;

    void UpdateState(const sf::Event& Event);
    // ***===== End Attributes =====*** //
};