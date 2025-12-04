#pragma once 
#include "Sector.h"

Sector::Sector(int sectorNb, int floorH, int ceilH, int wallsNb, sf::Color floorColor) : SectorNumber(sectorNb), FloorHeight(floorH), CeilHeight(ceilH), nbWalls(wallsNb),floorColor(floorColor)
{
	sectorWalls = new Wall[sectorNb];
	for (int i = 0; i < sectorNb; i++) {
		//Wall* myWall = new Wall(sf::Vector2f(0, 0), sf::Vector2f(0, 0), sf::Color::White, -1);
		//dsectorWalls[i] = *myWall;
	}
}

Sector::Sector() {
	sectorWalls = new Wall[5];
	nbWalls = 5;
	CeilHeight = 10;
	FloorHeight = 0;
	SectorNumber = 0;
}

Sector::~Sector()
{
	delete[] sectorWalls;
}

void Sector::addWall(Wall wall,int index)
{
	sectorWalls[index] = wall;
}
