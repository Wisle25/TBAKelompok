#include "GridLayout.h"
#include "App.h"
#include "Shapes/RoundedRectangleShape.h"

GridLayout::GridLayout(BasePage* Page, const FMakeShape& ShapeProps):
    Super(Page)
{
    FMakeShape FinalShapeProps = ShapeProps;
    FinalShapeProps.Color = sf::Color::Transparent;
    FinalShapeProps.OutlineColor = COLOR;

    Props = FinalShapeProps;

    MakeShape<sf::RoundedRectangleShape>(FinalShapeProps);
    GenerateGrid();
}

///////////////////////////////////////////////////////////
// ==================== Grid System ==================== //

void GridLayout::GenerateGrid()
{
    const sf::Uint32 MaxX = Props.Size.x / GridSize;
    const sf::Uint32 MaxY = Props.Size.y / GridSize;
    StartedPosition = Props.Position - Shapes[0]->getOrigin() + sf::Vector2f(Props.OutlineThickness, Props.OutlineThickness);

    Grid.resize(MaxX);
    for (sf::Uint32 X = 0; X < MaxX; ++X)
    {
        Grid[X].resize(MaxY);
        for (sf::Uint32 Y = 0; Y < MaxY; ++Y)
        {
            sf::Vector2f CurrentPosition = sf::Vector2f(X, Y) * GridSize + StartedPosition;

            sf::RoundedRectangleShape* Shape = MakeShape<sf::RoundedRectangleShape>({
                .Size=sf::Vector2f(GridSize, GridSize),
                .Position=CurrentPosition,
                .Color=sf::Color::Transparent,
                .OutlineColor=sf::Color::Transparent,
                .OutlineThickness=1.f,
                .BorderRadius=0.f
            });

            Cell NewCell(CurrentPosition, INFINITY, INFINITY, nullptr, Shape, sf::Vector2i(X, Y));
            Grid[X][Y] = NewCell;
        }
    }
}

//////////////////////////////////////////////////////////
// ==================== Lifecycles ==================== //

void GridLayout::ReceiveEvent(const sf::Event& Event)
{
    // NOTE: Only for TESTING!
    // switch (Event.type)
    // {
    //     case sf::Event::MouseButtonPressed:
    //     {
    //         sf::Vector2i MousePosition      = sf::Mouse::getPosition(*Application->GetAppWindow());
    //         sf::Vector2f WorldMousePosition;
    //         WorldMousePosition.x = MousePosition.x * Application->GetAppWindow()->getDefaultView().getSize().x / 1000.f;
    //         WorldMousePosition.y = MousePosition.y * Application->GetAppWindow()->getDefaultView().getSize().y / 600.f;

    //         // Convert mouse position to grid coordinates
    //         sf::Vector2i GridCoords;
    //         GridCoords.x = static_cast<int>((WorldMousePosition.x - StartedPosition.x) / GridSize);
    //         GridCoords.y = static_cast<int>((WorldMousePosition.y - StartedPosition.y) / GridSize);

    //         if (Event.mouseButton.button == sf::Mouse::Left)
    //         {
    //             // Check if the grid coordinates are within bounds
    //             if (GridCoords.x >= 0 && GridCoords.x < Grid.size() && GridCoords.y >= 0 && GridCoords.y < Grid[0].size())
    //             {
    //                 Cell& ClickedCell = Grid[GridCoords.x][GridCoords.y];

    //                 ClickedCell.IsObstacle = true;
    //                 ClickedCell.Shape->setFillColor(sf::Color::Red);
    //             }
    //         }

    //         if (Event.mouseButton.button == sf::Mouse::Right)
    //         {
    //             // Check if the grid coordinates are within bounds
    //             if (GridCoords.x >= 0 && GridCoords.x < Grid.size() && GridCoords.y >= 0 && GridCoords.y < Grid[0].size())
    //             {
    //                 Cell& ClickedCell = Grid[GridCoords.x][GridCoords.y];

    //                 ClickedCell.Shape->setFillColor(sf::Color::Yellow);
                    
    //                 Start = GridCoords;
    //             }
    //         }

    //         if (Event.mouseButton.button == sf::Mouse::Middle)
    //         {
    //             // Check if the grid coordinates are within bounds
    //             if (GridCoords.x >= 0 && GridCoords.x < Grid.size() && GridCoords.y >= 0 && GridCoords.y < Grid[0].size())
    //             {
    //                 Cell& ClickedCell = Grid[GridCoords.x][GridCoords.y];

    //                 ClickedCell.Shape->setFillColor(sf::Color::Green);
    //                 Goal = GridCoords;
    //             }
    //         }

    //         break;
    //     }

    //     case sf::Event::KeyPressed:
    //     {
    //         if (Event.key.code == sf::Keyboard::Enter)
    //         {
    //             std::vector<Cell*> Path = AStar(Grid, Start, Goal);

    //             for (const auto& Cell : Path)
    //             {
    //                 Cell->Shape->setFillColor(sf::Color::Cyan);
    //             }
    //         }

    //         break;
    //     }

    //     default:
    //         break;
    // }
}

//////////////////////////////////////////////////////////////
// ==================== A* Pathfinding ==================== //

std::vector<GridLayout::Cell*> GridLayout::AStar(std::vector<std::vector<Cell>>& Grid, const sf::Vector2i& StartIdx, const sf::Vector2i& GoalIdx) 
{
    int Rows = Grid.size();
    int Cols = Grid[0].size();

    // Priority queue to store open cells
    std::priority_queue<Cell*, std::vector<Cell*>, decltype(&CompareCells)> Open(&CompareCells);
    std::unordered_map<std::string, double> Cost;
    std::unordered_map<std::string, Cell*> CameFrom;

    // Initialize start cell
    Cell* StartCell = &Grid[StartIdx.x][StartIdx.y];
    StartCell->Cost = 0;
    StartCell->Heuristic = Heuristic(StartCell->Position, Grid[GoalIdx.x][GoalIdx.y].Position);
    Open.push(StartCell);
    Cost[std::to_string(StartIdx.x) + "," + std::to_string(StartIdx.y)] = 0;

    while (!Open.empty()) 
    {
        // Get the cell with the lowest total cost from the open list
        Cell* Current = Open.top();
        Open.pop();

        // Check if the goal cell is reached
        if (Current->Position == Grid[GoalIdx.x][GoalIdx.y].Position) 
        {
            // Reconstruct the path
            std::vector<Cell*> Path;
            while (Current != nullptr) 
            {
                Path.push_back(Current);
                Current = CameFrom[std::to_string(Current->GridPosition.x) + "," + std::to_string(Current->GridPosition.y)];
            }
            std::reverse(Path.begin(), Path.end());
            
            return Path;
        }

        // Expand current cell
        int X = Current->GridPosition.x;
        int Y = Current->GridPosition.y;

        std::vector<sf::Vector2i> Neighbors = {{X - 1, Y}, {X + 1, Y}, {X, Y - 1}, {X, Y + 1}};
        
        for (const auto& Neighbor : Neighbors) 
        {
            int NX = Neighbor.x;
            int NY = Neighbor.y;
            
            if (NX >= 0 && NX < Rows && NY >= 0 && NY < Cols && !Grid[NX][NY].IsObstacle) 
            {
                Cell* NextCell = &Grid[NX][NY];
                double NewCost = Cost[std::to_string(X) + "," + std::to_string(Y)] + 1;

                if (!Cost.count(std::to_string(NX) + "," + std::to_string(NY)) || NewCost < Cost[std::to_string(NX) + "," + std::to_string(NY)]) 
                {
                    Cost[std::to_string(NX) + "," + std::to_string(NY)] = NewCost;
                    NextCell->Cost = NewCost;
                    NextCell->Heuristic = Heuristic(NextCell->Position, Grid[GoalIdx.x][GoalIdx.y].Position);
                    Open.push(NextCell);
                    CameFrom[std::to_string(NX) + "," + std::to_string(NY)] = Current;
                }
            }
        }
    }

    // No path found
    return {};
}
