#pragma once

#include "Core.h"
#include "Pages/BasePage.h"

class App : public sf::RenderWindow
{
public:
    typedef sf::RenderWindow Super;

    App();

    void Run();

private:
    // ***===== Core =====*** //

    std::unique_ptr<sf::Clock> Clock;
    std::map<std::string, sf::Font> Fonts;
    sf::Event AppEvent;

    sf::Vector2f MousePosition;

    void DrawThread();
    void LoadFonts();

public:
    __forceinline sf::Font& GetFont(const std::string& FontName)
    {
        return Fonts[FontName];
    }
    __forceinline sf::Vector2f GetMousePosition() const
    {
        return MousePosition;
    }

    // ***===== End Core =====*** //

private:

    // ***===== Debugging =====*** //

    void DrawDebugMouseLocation();

    // ***===== Lifecycles =====*** //

    void PollEvents();
    void Tick();

    // ***===== Pagination =====*** //

    BasePage* LastPage = nullptr;

    std::stack<BasePage*> Pages;

public:
    /** NOTE: This is still a naive approach, gonna fix this later */
    template <typename T>
    __forceinline void GoToPage()
    {
        T* NewPage = new T();
        NewPage->Prepare(this);

        Pages.push(NewPage);
    }

    __forceinline void GoBackPage()
    {
        LastPage = Pages.top();

        // --CurrentPage;
        Pages.pop();
    }
    // ***===== End Pagination =====*** //

    // ***===== Randomizer =====*** //

    static int32_t RandRange(int32_t Min, int32_t Max)
    {
        std::random_device Rd;
        std::mt19937 Gen(Rd());

        std::uniform_int_distribution<> Dis(Min, Max);

        return Dis(Gen);
    }
};
