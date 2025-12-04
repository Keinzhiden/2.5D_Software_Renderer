#pragma once
#include "Wall.h"
class Sector
{
public:
	Sector();
	Sector(int sectorNb,int floorH,int ceilH,int wallsNb,sf::Color floorColor = sf::Color::Blue);
	~Sector();

	Wall* sectorWalls = nullptr;

	int FloorHeight;
	int CeilHeight;
	int nbWalls;
	int SectorNumber;
	sf::Color floorColor;

	void addWall(Wall wall,int index);

//	int neighboors;
private:

};


