#pragma once

#include "Core.h"
#include "Components/BaseComponent.h"

class Button;

class BasePage
{

public:
    // ***==== Lifecycles ====*** //
    virtual void Prepare(App* InApplication);
    virtual void ReceiveEvent(const sf::Event& Event);
    virtual void Tick(const float DeltaTime);
    virtual void Draw(sf::RenderTarget* RenderTarget);

protected:
    // ***==== User Interfaces ====*** //

    __forceinline void AddComponent(BaseComponent* NewComponent)
    {
        Components.push_back(std::shared_ptr<BaseComponent>(NewComponent));
    }
    
    void AddText(const FMakeText& Properties);

    sf::Vector2f CalculateByScreenPercent(const float X, const float Y);
    __forceinline sf::Uint16 CalculateTextScreenPercent(float Size)
    {
        return static_cast<sf::Uint16>(CalculateByScreenPercent(Size, Size).y);
    }

    Button* MakeButton(const FMakeShape& ShapeProperties, const FMakeText& TextProperties);

    virtual void CreateLayout();

protected:
    std::vector<std::shared_ptr<BaseComponent>> Components;
    std::vector<std::shared_ptr<sf::Text>> Texts;

    // ***===== Core References =====*** //

    App* Application;

protected:
    std::string Name = "Bass";

public:
    __forceinline App* GetApp() const
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