#pragma once

#include "Core.h"
#include "Components/BaseComponent.h"

enum class InputState : uint8_t
{
    None,
    OnFocus
};

class InputText : public BaseComponent
{
public:
    InputText(BasePage* Page, const FMakeShape& Props, const std::string& InLabel);

    // ***===== Lifecycles =====*** //

    virtual void ReceiveEvent(const sf::Event& Event) override;

private:
    // ***===== Attributes =====*** //
    std::string Label;
    std::string Value;
    sf::Cursor Cursor;

    InputState State = InputState::None;

public:
    const std::string& GetValue() const
    {
        return Value;
    }
};
