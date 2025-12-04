#pragma once
#include "Sector.h"
using namespace std;
class Map {
public:
	Map(string mapPath);
	~Map();
	Sector* mapSectors = nullptr;
	int nbSectors = 0;
private:
	
	
	void ReadandProcessMapFile();
};