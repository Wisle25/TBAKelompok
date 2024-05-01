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
    std::map<std::string, sf::Font> Fonts;
    sf::Event AppEvent;

    void InitCore();
    void DrawThread();
    void LoadFonts();

public:
    __forceinline sf::Font& GetFont(const std::string& FontName)
    {
        return Fonts[FontName];
    }
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
