#pragma once 

#include "Wall.h"

Wall::Wall() {
	WallColor = sf::Color(100,255,255,255);
	neighboorValue = -1;
	//Vertices = new sf::Vector2f[2];
	Vertices[0] =  sf::Vector2f( 1.0f,1.0f );
	Vertices[1] = sf::Vector2f( 2.0f,5.0f );
}
Wall::Wall(sf::Vector2f point1, sf::Vector2f point2, sf::Color wallCol, int neighboorVal) : WallColor(wallCol),
neighboorValue(neighboorVal)
{
	//Vertices = new sf::Vector2f[2];
	Vertices[0] = point1;
	Vertices[1] = point2;
}

Wall::~Wall()
{
	//delete Vertices;
}