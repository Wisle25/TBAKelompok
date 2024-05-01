#pragma once

#include "Core.h"
#include "Components/BaseComponent.h"

#include <queue>

class GridLayout : public BaseComponent
{
public:
    GridLayout(BasePage* Page, const FMakeShape& ShapeProps);

    // ***===== Lifecycles =====*** //

    virtual void ReceiveEvent(const sf::Event& Event) override;

private:
    // ***===== Using A* for path finding =====*** //

    // NOTE: ONLY FOR TESTING!!!
    // sf::Vector2i Start;
    // sf::Vector2i Goal;

    // Structure to represent a cell
    struct Cell 
    {
        sf::Vector2f Position;
        sf::Shape* Shape;

        double Cost;
        double Heuristic;
        Cell* Parent;
        bool IsObstacle = false;
        sf::Vector2i GridPosition;
        
        Cell() {}

        Cell(sf::Vector2f position, double cost, double heuristic, Cell* parent, sf::Shape* shape, sf::Vector2i gridPosition)
            : Position(position), Cost(cost), Heuristic(heuristic), Parent(parent), Shape(shape), GridPosition(gridPosition) {}

        // Calculate total cost (f = g + h)
        __forceinline double GetTotalCost() const 
        {
            return Cost + Heuristic;
        }
    };

    // Function to calculate the heuristic (Euclidean distance)
    __forceinline double Heuristic(const sf::Vector2f& p1, const sf::Vector2f& p2) 
    {
        return std::sqrt(std::pow(p1.x - p2.x, 2) + std::pow(p1.y - p2.y, 2));
    }

    // Comparator function for priority queue
    __forceinline static bool CompareCells(const Cell* a, const Cell* b) 
    {
        return a->GetTotalCost() > b->GetTotalCost();
    }

    // A* algorithm
    std::vector<Cell*> AStar(std::vector<std::vector<Cell>>& Grid, const sf::Vector2i& StartIdx, const sf::Vector2i& GoalIdx);

    // ***===== Grid System =====*** //

    FMakeShape Props;
    float GridSize = 10.f;

    sf::Vector2f StartedPosition;
    std::vector<std::vector<Cell>> Grid;

    void GenerateGrid();

};