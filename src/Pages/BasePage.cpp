#include "BasePage.h"
#include "App.h"

BasePage::BasePage(App* Application):
    AppWindow(Application->GetAppWindow())
{
}

void BasePage::ReceiveEvent(const sf::Event& Event)
{
    for (const auto& Component : Components)
        Component->ReceiveEvent(Event);
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
