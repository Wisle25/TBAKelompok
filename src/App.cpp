#include "App.h"
#include "Pages/MainPage.h"

App::App()
{
    InitCore();
}

////////////////////////////////////////////////////
// ==================== Core ==================== //

void App::InitCore()
{
    // Window
    AppWindow = std::make_unique<sf::RenderWindow>(sf::VideoMode(800, 600), "TBA Kelompok", sf::Style::Titlebar | sf::Style::Close);
    AppWindow->setFramerateLimit(144);
    AppWindow->setActive(false);

    // Clock
    Clock = std::make_unique<sf::Clock>();
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
    sf::Event AppEvent;

    while (AppWindow->pollEvent(AppEvent))
    {
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
        Pages.top()->Tick(DeltaTime);
}


void App::DrawThread()
{
    AppWindow->setActive(true);

    while (AppWindow->isOpen())
    {
        AppWindow->clear();

        if (!Pages.empty())
            Pages.top()->Draw(AppWindow.get());
        DrawDebugMouseLocation();
        
        AppWindow->display();
    }
}

void App::Run()
{
    // Main Page
    Pages.push(std::make_unique<MainPage>());

    // Rendering Thread
    sf::Thread RenderingThread(&App::DrawThread, this);
    RenderingThread.launch();

    while (AppWindow->isOpen())    
    {
        PollEvents();
        Tick();
    }
}
