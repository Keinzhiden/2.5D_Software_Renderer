#pragma once 
#include "Map.h"

Map::Map(string mapPath)
{
	ReadandProcessMapFile();
}

Map::~Map()
{
	delete[] mapSectors;
}

void Map::ReadandProcessMapFile()
{
	nbSectors = 9;
	mapSectors = new Sector[nbSectors]{
		Sector(0, 0, 16, 5),Sector(1, 3,12, 3),Sector(2, -1, 9, 6),
		Sector(3, 0, 16, 3),
		Sector(4, 1, 16, 6),
		Sector(5, 1, 16, 4),Sector(6, 4, 11, 4),Sector(7, 1, 16, 4),
		Sector(8, 1, 16, 7)
	};
	
	//mapSectors[0] = Sector(1, 0, 10, 5);
	//mapSectors[1] = Sector(2, 0, 10, 3);
	//mapSectors[2] = Sector(3, 0, 10, 4);
	
	//Walls Sector 1
	/*Wall* s1wall1 = new Wall(sf::Vector2f{ 30,80 }, sf::Vector2f{ 130,50 }, sf::Color::White, -1);
	Wall* s1wall2 = new Wall(sf::Vector2f{ 130,50 }, sf::Vector2f{ 130,130 }, sf::Color::Red, -1);
	Wall* s1wall3 = new Wall(sf::Vector2f{ 130,130 }, sf::Vector2f{ 100,150 }, sf::Color::Magenta, -1);
	Wall* s1wall4 = new Wall(sf::Vector2f{ 100,150 }, sf::Vector2f{ 0,100 }, sf::Color::Yellow, -1);
	Wall* s1wall5 = new Wall(sf::Vector2f{ 0,100 }, sf::Vector2f{ 30,80 }, sf::Color::Green, -1);*/
	
	mapSectors[0].sectorWalls = new Wall[mapSectors[0].nbWalls]{
		Wall(sf::Vector2f{ 30,80 }, sf::Vector2f{ 130,50 }, sf::Color::Red, 2),
		Wall(sf::Vector2f{ 130,50 }, sf::Vector2f{ 130,130 }, sf::Color::Red, 1),
		Wall(sf::Vector2f{ 130,130 }, sf::Vector2f{ 100,150 }, sf::Color::Magenta, -1),
		Wall(sf::Vector2f{ 100,150 }, sf::Vector2f{ 0,100 }, sf::Color::Yellow, -1),
		Wall(sf::Vector2f{ 0,100 }, sf::Vector2f{ 30,80 }, sf::Color::Green, 3)
	};

	mapSectors[0].floorColor = sf::Color{120,120,120,255};

	mapSectors[1].sectorWalls = new Wall[mapSectors[1].nbWalls]{
		Wall(sf::Vector2f{ 130,50 }, sf::Vector2f{ 165,90 }, sf::Color::White, -1),
		Wall(sf::Vector2f{ 165,90 }, sf::Vector2f{ 130,130 }, sf::Color::Magenta, -1),
		Wall(sf::Vector2f{ 130,130 }, sf::Vector2f{ 130,50 }, sf::Color::Red, 0)
	};
	mapSectors[1].floorColor = sf::Color{ 100,60,190,255 };

	mapSectors[2].sectorWalls = new Wall[mapSectors[2].nbWalls]{
		Wall(sf::Vector2f{ 30,80 }, sf::Vector2f{ 30,45 }, sf::Color::White, 4),
		Wall(sf::Vector2f{ 30,45 }, sf::Vector2f{ 30,35 }, sf::Color::Yellow, 7),
		Wall(sf::Vector2f{ 30,35 }, sf::Vector2f{ 30,15 }, sf::Color::Yellow, 8),
		Wall(sf::Vector2f{ 30,15 }, sf::Vector2f{ 130,15 }, sf::Color::Yellow, -1),
		Wall(sf::Vector2f{ 130,15 }, sf::Vector2f{ 130,50 }, sf::Color::Magenta, -1),
		Wall(sf::Vector2f{ 130,50 }, sf::Vector2f{ 30,80 }, sf::Color::Red, 0),
	};

	mapSectors[2].floorColor = sf::Color{ 0,0,190,255 };

	mapSectors[3].sectorWalls = new Wall[mapSectors[3].nbWalls]{
		Wall(sf::Vector2f{ 30,80 },sf::Vector2f{ 0,100 }, sf::Color::Green, 0),
		Wall(sf::Vector2f{ 0,100 }, sf::Vector2f{ 0,80 }, sf::Color::Green, -1),
		Wall(sf::Vector2f{ 0,80 }, sf::Vector2f{ 30,80 }, sf::Color::Green, 4),
	};
	mapSectors[3].floorColor = sf::Color{ 120,120,120,255 };

	mapSectors[4].sectorWalls = new Wall[mapSectors[4].nbWalls]{
		Wall(sf::Vector2f{ 30,80 },sf::Vector2f{ 0,80 }, sf::Color::Green, 3),
		Wall(sf::Vector2f{ 0,80 }, sf::Vector2f{ 0,45 }, sf::Color::Yellow, -1),
		Wall(sf::Vector2f{ 0,45 }, sf::Vector2f{ 10,45 }, sf::Color::Green, 5),
		Wall(sf::Vector2f{ 10,45 }, sf::Vector2f{ 20,45 }, sf::Color::Green, 6),
		Wall(sf::Vector2f{ 20,45 }, sf::Vector2f{ 30,45 }, sf::Color::Green, 7),
		Wall(sf::Vector2f{ 30,45 }, sf::Vector2f{ 30,80 }, sf::Color::Green, 2),
	};
	mapSectors[4].floorColor = sf::Color{ 120,120,120,255 };

	mapSectors[5].sectorWalls = new Wall[mapSectors[5].nbWalls]{
		Wall(sf::Vector2f{ 0,45 },sf::Vector2f{ 0,35 }, sf::Color::Yellow, -1),
		Wall(sf::Vector2f{ 0,35 }, sf::Vector2f{ 10,35 }, sf::Color::Yellow, 8),
		Wall(sf::Vector2f{ 10,35 }, sf::Vector2f{ 10,45 }, sf::Color::Green, 6),
		Wall(sf::Vector2f{ 10,45 }, sf::Vector2f{ 0,45 }, sf::Color::Green, 4),
	};
	mapSectors[5].floorColor = sf::Color{ 120,120,120,255 };

	mapSectors[6].sectorWalls = new Wall[mapSectors[6].nbWalls]{
		Wall(sf::Vector2f{ 10,45 },sf::Vector2f{ 10,35 }, sf::Color::Yellow, 5),
		Wall(sf::Vector2f{ 10,35 }, sf::Vector2f{ 20,35 }, sf::Color::Yellow, 8),
		Wall(sf::Vector2f{ 20,35 }, sf::Vector2f{ 20,45 }, sf::Color::Green, 7),
		Wall(sf::Vector2f{ 20,45 }, sf::Vector2f{ 10,45 }, sf::Color::Green, 4),
	};
	mapSectors[6].floorColor = sf::Color{ 180,100,100,255 };

	mapSectors[7].sectorWalls = new Wall[mapSectors[7].nbWalls]{
		Wall(sf::Vector2f{ 20,45 },sf::Vector2f{ 20,35 }, sf::Color::Yellow, 6),
		Wall(sf::Vector2f{ 20,35 }, sf::Vector2f{ 30,35 }, sf::Color::Yellow, 8),
		Wall(sf::Vector2f{ 30,35 }, sf::Vector2f{ 30,45 }, sf::Color::Green, 2),
		Wall(sf::Vector2f{ 30,45 }, sf::Vector2f{ 20,45 }, sf::Color::Green, 4),
	};
	mapSectors[7].floorColor = sf::Color{ 120,120,120,255 };

	mapSectors[8].sectorWalls = new Wall[mapSectors[8].nbWalls]{
		Wall(sf::Vector2f{ 0,35 },sf::Vector2f{ 0,0 }, sf::Color::Yellow, -1),
		Wall(sf::Vector2f{ 0,0 }, sf::Vector2f{ 30,0 }, sf::Color::Yellow, -1),
		Wall(sf::Vector2f{ 30,0 }, sf::Vector2f{ 30,15 }, sf::Color::Yellow, -1),
		Wall(sf::Vector2f{ 30,15 }, sf::Vector2f{ 30,35 }, sf::Color::Green, 2),
		Wall(sf::Vector2f{ 30,35 }, sf::Vector2f{ 20,35 }, sf::Color::Green, 7),
		Wall(sf::Vector2f{ 20,35 }, sf::Vector2f{ 10,35 }, sf::Color::Green, 6),
		Wall(sf::Vector2f{ 10,35 }, sf::Vector2f{ 0,35 }, sf::Color::Green, 5),
	};
	mapSectors[8].floorColor = sf::Color{ 120,120,120,255 };
	
}
