#include "App.h"
#include "Pages/MainPage.h"

#include <filesystem>

App::App():
    // Super(sf::VideoMode::getDesktopMode(), "TBA Kelompok", sf::Style::Fullscreen)
    Super(sf::VideoMode(800, 600), "TBA Kelompok")
{
    // Window   
    setFramerateLimit(175);
    setActive(false);

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
    sprintf(position, "Position: %d, %d", sf::Mouse::getPosition(*this).x, sf::Mouse::getPosition(*this).y);
    Text.setFont(font);
    Text.setString(position);
    Text.setCharacterSize(8);
    Text.setOrigin(Text.getCharacterSize() / 2, Text.getCharacterSize() / 2);
    Text.setPosition(sf::Mouse::getPosition(*this).x, sf::Mouse::getPosition(*this).y);

    draw(Text);
}

//////////////////////////////////////////////////////////
// ==================== Lifecycles ==================== //

void App::PollEvents()
{
    while (pollEvent(AppEvent))
    {
        const sf::Vector2i MousePositionInt = sf::Mouse::getPosition(*this);
        MousePosition = { static_cast<float>(MousePositionInt.x), static_cast<float>(MousePositionInt.y) };

        if (!Pages.empty())
            Pages.top()->ReceiveEvent(AppEvent);

        switch (AppEvent.type)
        {
        case sf::Event::Closed:
            close();
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
        Pages.top()->Tick(DeltaTime);
    else
        close();
}

void App::DrawThread()
{
    setActive(true);

    while (isOpen())
    {
        clear();

        if (!Pages.empty())
            Pages.top()->Draw(this);

        display();
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

    while (isOpen())    
    {
        PollEvents();
        Tick();
    }
}
