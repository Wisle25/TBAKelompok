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

    void DrawThread();
    void LoadFonts();

public:
    __forceinline sf::Font& GetFont(const std::string& FontName)
    {
        return Fonts[FontName];
    }

    // ***===== End Core =====*** //

private:

    // ***===== Debugging =====*** //

    void DrawDebugMouseLocation();

    // ***===== Lifecycles =====*** //

    void PollEvents();
    void Tick();

    // ***===== Pagination =====*** //

    sf::Uint8 CurrentPage = -1;

    std::vector<std::unique_ptr<BasePage>> Pages;

    const sf::Int16 PageIsExists(BasePage* CheckPage)
    {
        for (sf::Int16 I = 0; I < Pages.size(); ++I)
        {   
            if (Pages[I]->GetName() == CheckPage->GetName())
                return I;
        }

        return -1;
    }

public:
    /** NOTE: This is still a naive approach, gonna fix this later */
    template <typename T>
    __forceinline void GoToPage()
    {
        T* NewPage = new T();
        NewPage->Prepare(std::shared_ptr<App>(this));

        sf::Int16 ExistedPage = PageIsExists(NewPage);

        if (ExistedPage == -1)
        {
            Pages.push_back(std::unique_ptr<T>(std::move(NewPage)));
            ++CurrentPage;
        }
        else
        {
            CurrentPage = ExistedPage;
        }
    }

    __forceinline void GoBackPage()
    {
        --CurrentPage;
        // Pages.pop_back();
    }
};
