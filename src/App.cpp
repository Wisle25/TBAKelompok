#include "App.h"
#include "Pages/MainPage.h"

#include <filesystem>

App::App()
{
    InitCore();
}

////////////////////////////////////////////////////
// ==================== Core ==================== //

void App::InitCore()
{
    // Window
    AppWindow = std::make_shared<sf::RenderWindow>(sf::VideoMode(1000, 600), "TBA Kelompok", sf::Style::Titlebar | sf::Style::Close);
    AppWindow->setFramerateLimit(200);
    AppWindow->setActive(false);

    // Clock
    Clock = std::make_unique<sf::Clock>();

    // Fonts
    LoadFonts();
}

/////////////////////////////////////////////////////////
// ==================== Debugging ==================== //

void App::DrawDebugMouseLocation()
{
    sf::Font font;
    font.loadFromFile("assets/FiraCode-Regular.ttf");

    sf::Text Text;
    char position[50];
    sprintf(position, "Position: %d, %d", sf::Mouse::getPosition(*AppWindow).x, sf::Mouse::getPosition(*AppWindow).y);
    Text.setFont(font);
    Text.setString(position);
    Text.setCharacterSize(8);
    Text.setOrigin(Text.getCharacterSize() / 2, Text.getCharacterSize() / 2);
    Text.setPosition(sf::Mouse::getPosition(*AppWindow).x, sf::Mouse::getPosition(*AppWindow).y);

    AppWindow->draw(Text);
}

//////////////////////////////////////////////////////////
// ==================== Lifecycles ==================== //

void App::PollEvents()
{
    while (AppWindow->pollEvent(AppEvent))
    {
        if (!Pages.empty())
            Pages[CurrentPage]->ReceiveEvent(AppEvent);

        switch (AppEvent.type)
        {
        case sf::Event::Closed:
            AppWindow->close();
            break;

        default:
            break;
        }
    }
    
}

void App::Tick()
{
    const float DeltaTime = Clock->restart().asSeconds();

    if (!Pages.empty())
    {
        Pages[CurrentPage]->Tick(DeltaTime);
    }
    else
        AppWindow->close();
}

void App::DrawThread()
{
    AppWindow->setActive(true);

    while (AppWindow->isOpen())
    {
        AppWindow->clear();

        if (!Pages.empty())
            Pages[CurrentPage]->Draw(AppWindow.get());

        AppWindow->display();
    }
}

void App::LoadFonts()
{
    namespace fs = std::filesystem;

    std::string Path = "Assets\\Fonts";

    for (const auto& Entry : fs::directory_iterator(Path))
    {
        const fs::path    FontFile = Entry.path();
        const std::string FontName = FontFile.filename().stem().string();

        sf::Font Font;
        Font.loadFromFile(FontFile.string());

        Fonts.emplace(FontName, Font);
    }
}

void App::Run()
{
    // Main Page
    GoToPage<MainPage>();

    // Rendering Thread
    sf::Thread RenderingThread(&App::DrawThread, this);
    RenderingThread.launch();

    while (AppWindow->isOpen())    
    {
        PollEvents();
        Tick();
    }
}
