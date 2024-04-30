#pragma once

#include "Core.h"
#include "Pages/BasePage.h"

class App
{
public:
    App();

    void Run();

private:
    // ***===== Core =====*** //

    std::unique_ptr<sf::RenderWindow> AppWindow;
    std::unique_ptr<sf::Clock> Clock;

    void InitCore();
    void DrawThread();

    // ***===== Debugging =====*** //

    void DrawDebugMouseLocation();

    // ***===== Lifecycles =====*** //

    void PollEvents();
    void Tick();

    // ***===== Pagination =====*** //

    std::stack<std::unique_ptr<BasePage>> Pages;
};
