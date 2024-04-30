#pragma once

#include "Core.h"
#include "Components/BaseComponent.h"

class App;

class BasePage
{
public:
    BasePage(App* Application);

public:
    void ReceiveEvent(const sf::Event& Event);
    void Tick(const float DeltaTime);
    void Draw(sf::RenderTarget* RenderTarget);

protected:
    __forceinline void AddComponent(BaseComponent* NewComponent)
    {
        Components.push_back(std::unique_ptr<BaseComponent>(std::move(NewComponent)));
    }
    __forceinline sf::Vector2f SetPositionPercent(const float X, const float Y)
    {
        return {
            AppWindow->getSize().x * X / 100.f,
            AppWindow->getSize().y * Y / 100.f
        };
    }

private:
    std::vector<std::unique_ptr<BaseComponent>> Components;

    // ***===== Core References =====*** //
    std::shared_ptr<sf::RenderWindow> AppWindow;

public:
    __forceinline std::shared_ptr<sf::RenderWindow> GetAppWindow() const
    {
        return AppWindow;
    }
};