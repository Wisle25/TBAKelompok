#pragma once

#include "Core.h"
#include "Components/BaseComponent.h"

class App;
class Button;

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

    sf::Vector2f CalculateByScreenPercent(const float X, const float Y);
    Button* MakeButton(const FMakeShape& ShapeProperties, const FMakeText& TextProperties);

    virtual void CreateLayout();

private:
    std::vector<std::unique_ptr<BaseComponent>> Components;
    std::vector<std::unique_ptr<sf::Text>> Texts;

    // ***===== Core References =====*** //

    std::shared_ptr<App> Application;

protected:
    std::string Name = "Bass";

public:
    __forceinline std::shared_ptr<App> GetApp() const
    {
        return Application;
    }

    __forceinline std::string& GetName() 
    {
        return Name;
    }
    // ***==== End Core References ====*** //

    void QuitPage();
};