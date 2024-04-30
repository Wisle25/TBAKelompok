#include "Button.h"

Button* Button::MakeButton(const FMakeButton& Properties)
{
    Button* NewButton = new Button();
    NewButton->BaseShape = std::make_unique<sf::RectangleShape>(Properties.Size);
    NewButton->BaseShape->setPosition(Properties.Size);

    return NewButton;
}
