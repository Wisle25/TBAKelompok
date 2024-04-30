#include "BasePage.h"

BasePage::BasePage()
{
    
}

void BasePage::Tick(const float DeltaTime)
{
    for (const auto& Component : Components)
        Component->Tick(DeltaTime);
}

void BasePage::Draw(sf::RenderTarget* RenderTarget)
{
    for (const auto& Component : Components)
        RenderTarget->draw(*Component);
}
