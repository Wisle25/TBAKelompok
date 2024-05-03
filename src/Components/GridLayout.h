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

    sf::Vector2i Start;
    sf::Vector2i Goal;
    sf::Vector2f HalfTransition;
    sf::Color PathColor;

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

    void ColorizeTransition(const std::vector<Cell*>& Path);

    // ***===== Grid System =====*** //

    FMakeShape Props;
    float GridSize = 10.f;

    sf::Vector2f StartedPosition;
    std::vector<std::vector<Cell>> Grid;

    void GenerateGrid();

public:
    __forceinline sf::Vector2f GetHalfTransition(const float Offset = 2.f)
    {
        HalfTransition.x -= Offset;
        HalfTransition.y -= Offset;

        return HalfTransition;
    }

    sf::Vector2i GetGridCords(const sf::Vector2f& Position);
    void MakeCellsAsObstacle(const sf::Vector2f& Position, const int32_t Radius);

    const bool IsInBounds() const;

    __forceinline void SetPathColor(const sf::Color& Color)
    {
        PathColor = Color;
    }

    __forceinline void SetStartPoint(const sf::Vector2i& GridCords)
    {
        Start = GridCords;
    }

    __forceinline void SetGoalPoint(const sf::Vector2i& GridCords)
    {
        Goal = GridCords;
    }

    // Visualize Transition using PathFinding with A* algorithm
    void VisualizeTransition();
};