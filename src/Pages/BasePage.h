#pragma once

#include "Core.h"
#include "Components/BaseComponent.h"

class BasePage
{
public:
    BasePage();

public:
    void Tick(const float DeltaTime);
    void Draw(sf::RenderTarget* RenderTarget);

protected:
    __forceinline void AddComponent(BaseComponent* NewComponent)
    {
        Components.push_back(std::unique_ptr<BaseComponent>(std::move(NewComponent)));
    }

private:
    std::vector<std::unique_ptr<BaseComponent>> Components;
};