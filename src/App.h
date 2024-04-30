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

    std::shared_ptr<sf::RenderWindow> AppWindow;
    std::unique_ptr<sf::Clock> Clock;
    sf::Event AppEvent;


    void InitCore();
    void DrawThread();

public:
    __forceinline std::shared_ptr<sf::RenderWindow> GetAppWindow() const
    {
        return AppWindow;
    }

    // ***===== End Core =====*** //

private:

    // ***===== Debugging =====*** //

    void DrawDebugMouseLocation();

    // ***===== Lifecycles =====*** //

    void PollEvents();
    void Tick();

    // ***===== Pagination =====*** //

    std::stack<std::unique_ptr<BasePage>> Pages;
};
