// gameOfLife.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
enum class cellType
{
    alive, dead, border
};

std::vector<std::vector<cellType>> generateMap(const int size)
{
    std::vector<std::vector<cellType>> plan(size, std::vector<cellType>(size));

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (i == 0 || j == 0 || i==size-1 || j==size-1) plan[i][j] = cellType::border;
            else plan[i][j] = cellType::dead;
        }
    }
    return plan;
}

void displayPlan(const std::vector<std::vector<cellType>> &plan)
{
    char aliveCh = '@';
    char deadCh = '.';
    char borderCh = '#';

    int planSize = plan.size();

    for (int i = 0; i < planSize; i++)
    {
        for (int j = 0; j < planSize; j++)
        {
            if (plan[i][j] == cellType::border) std::cout << borderCh;
            else if (plan[i][j] == cellType::dead) std::cout << deadCh;
            else std::cout << aliveCh;

            std::cout << ' ';
        }
        std::cout << std::endl;
    }
}

void placeLiving(int x, int y, std::vector<std::vector<cellType>> &plan, bool display=false)
{
    
    plan[y][x] = cellType::alive;

    if (display) displayPlan(plan);
}
int main()
{
    std::vector<std::vector<cellType>> gamePlan = generateMap(25);
    placeLiving(5, 5, gamePlan, true);
    displayPlan(gamePlan);
    return 0;
}

