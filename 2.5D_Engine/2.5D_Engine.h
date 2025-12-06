#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <chrono>
#include "Map.h"
#include "MyMath.h"
//#include <algorithm>

using namespace std;

struct PortalRender
{
	int sectorIndex = -1;
	int fromWallIndex = -1;
	int fromSectorIndex = -1;
	sf::Color portalColor = sf::Color::Black;

	sf::Vector2i xLimits;
	sf::Vector2i yLimits;
	sf::Vector2i yBottomLimits;
};

class Engine {
public:
	Engine(sf::RenderWindow& actualwindow);
	~Engine();
	sf::CircleShape playerMinimap;
	sf::CircleShape playerTransformedMinimap;
	sf::CircleShape playerDirMinimap;
	sf::CircleShape playerTransformedDirMinimap;
	float playerMinimapRadius = 7;
	float playerDirMinimapRadius = 3;
	float offsetPlayerDirMinimap = 15;
	sf::Vertex WallsLines [2];
	sf::Vertex WallsTransformedLines [2];
	sf::Vertex LinesDirVisionMinimap [2];
	sf::Vertex LinesPerspectiveTOP [2];
	sf::Vertex LinesPerspectiveBOTTOM [2];
	sf::Vertex LinesPerspectiveLEFT [2];
	sf::Vertex LinesPerspectiveRIGHT [2];
	sf::Vertex LinesDirVisionTransformedMinimap [2];

	const unsigned int minimapScale = 4;
	unsigned int xWidth = 750;
	unsigned int yHeight = 500;
	int resolutionFactor = 2;

	static const unsigned int nbVertices = 6;
	static const unsigned int nbVData = 2;
	sf::Vector2f vertices[nbVertices];

	sf::Color* pixelTab = nullptr;

	double PI = 3.141592653589793238462643383279502884;


	int playerCurrentSector = 0;
	Map* myMap = nullptr; 
	sf::Vector3f playerPosition;
	static const unsigned int FOV = 90;
	float playerVisionAngle = 0;
	float playerYaw = 0;
	
	sf::Vector2f firstWallpoint;
	sf::Vector2f secondWallpoint;
	float tz1 = 0.f;
	float tz2 = 0.f;

	float FNCross(float x1, float y1, float x2, float y2);
	void CalcTranformAndRotatedWall(int sectorIndex, int wallIndex);
	void CalcPerspectiveWall(int sectorIndex, int wallIndex,sf::Color wallColor, bool& bwasRendered,PortalRender currentPortal,PortalRender& newPortal);
	void RenderAllSectorWalls();
	void WallDraw();
	void vline(int x, int y1, int y2, int top, int middle, int bottom, sf::Color col, sf::Color portalColor);
	void Intersect(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4, double& x, double& y);

	void Render();
	void RenderMinimaps();
	sf::Sprite spriteRender = sf::Sprite();
	sf::Image imageRender = sf::Image();
	sf::Texture textureRender = sf::Texture();

	sf::RenderWindow* window = nullptr;


	void rotatePlayerOnMouse(sf::Vector2i mousePos, sf::RenderWindow& window);

	void movePlayerOnInput(sf::Vector2i dir);
	void updatePlayerSector(sf::Vector2f& movement);

	bool bDebugRenderOn = false;
	#define hfov (0.73f*xWidth)
	#define vfov (.45f*yHeight)

private:

};
