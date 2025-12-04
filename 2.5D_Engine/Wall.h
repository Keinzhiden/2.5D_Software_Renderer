#pragma once
#include <SFML/Graphics.hpp>

class Wall
{
public:
	Wall(sf::Vector2f point1, sf::Vector2f point2, sf::Color wallCol,int neighboorVal = -1);
	Wall();
	~Wall();

	sf::Vector2f Vertices[2];
	sf::Color WallColor;

	int neighboorValue = -1;


private:

};

