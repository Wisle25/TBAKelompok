#pragma once

#include "Core.h"
#include "Components/BaseComponent.h"

class App;
class Button;

struct FMakeButton;
struct FMakeText;

class BasePage
{

public:

    // ***==== Lifecycles ====*** //
    void Prepare(std::shared_ptr<App> InApplication);
    void ReceiveEvent(const sf::Event& Event);
    void Tick(const float DeltaTime);
    void Draw(sf::RenderTarget* RenderTarget);

protected:
    // ***==== User Interfaces ====*** //

    __forceinline void AddComponent(BaseComponent* NewComponent)
    {
        Components.push_back(std::unique_ptr<BaseComponent>(std::move(NewComponent)));
    }
    
    void AddText(const FMakeText& Properties);

    __forceinline sf::Vector2f SetPositionPercent(const float X, const float Y)
    {
        return {
            AppWindow->getSize().x * X / 100.f,
            AppWindow->getSize().y * Y / 100.f
        };
    }

    Button* MakeButton(const FMakeShape& ShapeProperties, const FMakeText& TextProperties);

    virtual void CreateLayout();

private:
    std::vector<std::unique_ptr<BaseComponent>> Components;
    std::vector<std::unique_ptr<sf::Text>> Texts;

    // ***===== Core References =====*** //
    std::shared_ptr<App> Application;
    std::shared_ptr<sf::RenderWindow> AppWindow;

protected:
    std::string Name = "Bass";

public:
    __forceinline std::shared_ptr<App> GetApp() const
    {
        return Application;
    }

    __forceinline std::shared_ptr<sf::RenderWindow> GetAppWindow() const
    {
        return AppWindow;
    }
    __forceinline std::string& GetName() 
    {
        return Name;
    }
    // ***==== End Core References ====*** //

    void QuitPage();
};