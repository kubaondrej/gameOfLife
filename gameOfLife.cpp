// gameOfLife.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
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

			if (i == 0 || j == 0 || i == size - 1 || j == size - 1) plan[i][j] = cellType::border;
			else plan[i][j] = cellType::dead;
		}
	}
	return plan;
}


void displayPlan(const std::vector<std::vector<cellType>>& plan, int highX = 0, int highY = 0, bool highLight = false)
{
	char aliveCh = '#';
	char deadCh = '.';
	char borderCh = 'X';

	int planSize = plan.size();


	for (int i = 0; i < planSize; i++)
	{
		/*if (i == 0)
		{
			std::cout << ' ' << ' ';
			for (int k = 0;k < planSize;k++) {
				std::cout << k << ' ';
			}
			std::cout << std::endl;
		}*/

		for (int j = 0; j < planSize; j++)
		{
			//if (j == -1) std::cout << i;

			if (plan[i][j] == cellType::border) std::cout << borderCh;
			else if (plan[i][j] == cellType::dead) std::cout << deadCh;
			else std::cout << aliveCh;

			std::cout << ' ';
		}
		std::cout << std::endl;
	}
}


void placeLiving(int x, int y, std::vector<std::vector<cellType>>& plan, bool display = false)
{

	plan[y][x] = cellType::alive;


	if (display) displayPlan(plan);
}

int countAliveNeighbours(int x, int y, std::vector<std::vector<cellType>>& plan, bool debug = false)
{
	int neighbourCount = 0;

	for (int localY = -1;localY < 2;localY++)
	{
		for (int localX = -1;localX < 2;localX++)
		{
			if (localY == 0 && localX == 0) continue;
			if ((plan[y + localY][x + localX] == cellType::alive)) neighbourCount++;
		}
	}
	return neighbourCount;
}

void placeLivingPattern(int x, int y, std::vector<std::vector<cellType>>& plan, bool debug = false)
{
	std::vector<std::vector<bool>> pattern =
	{ {0,1,0 },
	{  1,1,1 },
	{  0,1,0 } };
	for (int i = 0;i < 3;i++)
	{
		for (int j = 0;j < 3;j++)
		{
			if (pattern[i][j]) plan[y + (i - 1)][x + (j - 1)] = cellType::alive;
			else plan[y + (i - 1)][x + (j - 1)] = cellType::dead;
		}
	}
}

std::vector<std::vector<cellType>> calculateNextGen(std::vector<std::vector<cellType>>& plan)
{
	int planSize = plan.size();
	std::vector<std::vector<cellType>> newGen(planSize, std::vector<cellType>(planSize));
	newGen = generateMap(planSize);
	for (int i = 1; i < planSize - 1;i++)
	{
		for (int j = 1; j < planSize - 1; j++)
		{
			int planNeighbourCount = countAliveNeighbours(j, i, plan);

			///Any live cell with fewer than two live neighbours dies, as if by underpopulation.
			if (plan[i][j] == cellType::alive && planNeighbourCount < 2)
			{
				newGen[i][j] = cellType::dead;
			}
			//Any live cell with two or three live neighbours lives on to the next generation.
			else if (plan[i][j] == cellType::alive && (planNeighbourCount == 2 || planNeighbourCount == 3))
			{
				newGen[i][j] = cellType::alive;
			}
			//Any live cell with more than three live neighbours dies, as if by overpopulation.
			else if (plan[i][j] == cellType::alive && (planNeighbourCount > 3))
			{
				newGen[i][j] = cellType::dead;
			}
			//Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.
			else if (plan[i][j] == cellType::dead && (planNeighbourCount == 3))
			{
				newGen[i][j] = cellType::alive;
			}
			else
			{
				newGen[i][j] = cellType::dead;
			}
		}
	}
	return newGen;
}

int main()
{
	std::vector<std::vector<cellType>> gamePlan = generateMap(15);
	placeLivingPattern(5, 5, gamePlan);
	std::string xxx;
	while (1)
	{
		displayPlan(gamePlan);
		gamePlan = calculateNextGen(gamePlan);
		std::this_thread::sleep_for(std::chrono::milliseconds(500)); // pauza 0.5 sekundy
		std::cout << std::flush;
	}




	/*std::cout << countAliveNeighbours(3, 2, gamePlan);
	std::cout << countAliveNeighbours(1, 1, gamePlan);*/

	//std::cout << countAliveNeighbours(2, 2, gamePlan, true);
	return 0;
}


