#pragma once 
#include "2.5D_Engine.h"
#include <time.h>

/*
' Acquire the x,y coordinates of these two vertexes
vx1 = vertex(v1).x : vy1 = vertex(v1).y
vx2 = vertex(v2).x : vy2 = vertex(v2).y
' Transform the vertices into the player's view
vx1 = vx1 - player.where.x : vy1 = vy1 - player.where.y
vx2 = vx2 - player.where.x : vy2 = vy2 - player.where.y
' Rotate them around the player's view
tz1 = vx1 * player.anglecos + vy1 * player.anglesin
tz2 = vx2 * player.anglecos + vy2 * player.anglesin
' Is the wall at least partially in front of the player?
IF tz1 <= 0 AND tz2 <= 0 THEN GOTO nextsector
' Yes (either Z was > 0). Do the rest of the rotation
tx1 = vx1 * player.anglesin - vy1 * player.anglecos
tx2 = vx2 * player.anglesin - vy2 * player.anglecos
' If it's partially behind the player, clip it at z = 0.1
IF tz1 <= 0 THEN tx1 = (0.1 - tz1) * (tx2 - tx1) / (tz2 - tz1) + tx1 : tz1 = 0.1
IF tz2 <= 0 THEN tx2 = (0.1 - tz2) * (tx1 - tx2) / (tz1 - tz2) + tx2 : tz2 = 0.1
' Do perspective transformation
xscale1 = 140 / tz1 : yscale1 = 32 / tz1
xscale2 = 140 / tz2 : yscale2 = 32 / tz2
x1 = W\2 + CINT(-tx1 * xscale1)
x2 = W\2 + CINT(-tx2 * xscale2)

*/
Engine::Engine(sf::RenderWindow& actualwindow) {

	myMap = new Map("blabla");

	window = &actualwindow;

	xWidth = window->getSize().x/resolutionFactor;
	yHeight = window->getSize().y/resolutionFactor;

	playerPosition.x = 50;
	playerPosition.y = 100;
	playerPosition.z = 4;


	imageRender.create(xWidth, yHeight, sf::Color::Black);

	pixelTab = new sf::Color[int((double)xWidth * (double)yHeight)];

	playerMinimap.setFillColor(sf::Color::Blue);
	playerDirMinimap.setFillColor(sf::Color::Blue);
	playerMinimap.setRadius(playerMinimapRadius);
	playerDirMinimap.setRadius(playerDirMinimapRadius);

	playerTransformedMinimap.setFillColor(sf::Color::Blue);
	playerTransformedDirMinimap.setFillColor(sf::Color::Blue);
	playerTransformedMinimap.setRadius(playerMinimapRadius);
	playerTransformedDirMinimap.setRadius(playerDirMinimapRadius);

	srand(time(0));
}

Engine::~Engine() {
	delete[] pixelTab;
	//delete mysector;
	//	delete window;
	delete myMap;
}
void Engine::CalcTranformAndRotatedWall(int sectorIndex,int wallIndex) {
	firstWallpoint = { myMap->mapSectors[sectorIndex].sectorWalls[wallIndex].Vertices[0].x - playerPosition.x,myMap->mapSectors[sectorIndex].sectorWalls[wallIndex].Vertices[0].y - playerPosition.y };
	secondWallpoint = { myMap->mapSectors[sectorIndex].sectorWalls[wallIndex].Vertices[1].x - playerPosition.x,myMap->mapSectors[sectorIndex].sectorWalls[wallIndex].Vertices[1].y - playerPosition.y };
	
	tz2 = secondWallpoint.x * (cos(playerVisionAngle * PI / 180)) + secondWallpoint.y * (sin(playerVisionAngle * PI / 180));
	tz1 = firstWallpoint.x * (cos(playerVisionAngle * PI / 180)) + firstWallpoint.y * (sin(playerVisionAngle * PI / 180));
	firstWallpoint.x = firstWallpoint.x * (sin(playerVisionAngle * PI / 180)) - firstWallpoint.y * (cos(playerVisionAngle * PI / 180));
	secondWallpoint.x = secondWallpoint.x * (sin(playerVisionAngle * PI / 180)) - secondWallpoint.y * (cos(playerVisionAngle * PI / 180));

	playerTransformedMinimap.setPosition(300- playerMinimapRadius,300 - playerMinimapRadius);
	playerTransformedDirMinimap.setPosition(((playerTransformedMinimap.getPosition().x - playerMinimapRadius +1 * offsetPlayerDirMinimap) - playerDirMinimapRadius), ((playerTransformedMinimap.getPosition().y - playerMinimapRadius - playerDirMinimapRadius)));
	
	LinesDirVisionTransformedMinimap[0] = sf::Vector2f{ 300,300 };
	LinesDirVisionTransformedMinimap[1] = sf::Vector2f{ playerTransformedDirMinimap.getPosition().x + playerDirMinimapRadius, playerTransformedDirMinimap.getPosition().y + playerDirMinimapRadius };


	WallsTransformedLines[0] = sf::Vector2f(300 - firstWallpoint.x, 300 - tz1);
	WallsTransformedLines[1] = sf::Vector2f(300 - secondWallpoint.x, 300 - tz2);

}
void Engine::CalcPerspectiveWall(int sectorIndex, int wallIndex,sf::Color wallColor,bool& bwasRendered,PortalRender currentPortal,PortalRender& newPortal) {

	sf::Color currentPortalColor = currentPortal.portalColor;
	sf::Color newPortalColor = newPortal.portalColor;

	double ix1  = 0.0;
	double ix2 = 0.0;
	double iz1 = 0.0;
	double iz2 = 0.0;

	if (tz1 > 0.0f || tz2 > 0.0f) {
		
		Intersect((double)firstWallpoint.x, (double)tz1, (double)secondWallpoint.x, (double)tz2, -1e-6f, 1e-4f, -20.0, 1, ix1, iz1);
		Intersect((double)firstWallpoint.x, (double)tz1, (double)secondWallpoint.x, (double)tz2, 1e-6f, 1e-4f, 20.0, 1, ix2, iz2);
		//std::cout << "\x1B[2J\x1B[H";
		//cout << " TZ " << tz1 << " | " << tz2 << endl;
		if (tz1 < 1e-4f) {
			if (iz1 > 0.0) {
				firstWallpoint.x = (float)ix1;
				tz1 = iz1;
			}
			else {
				firstWallpoint.x = (float)ix2;
				tz1 = iz2;
			}
		}

		if (tz2 < 1e-4f) {
			if (iz1 > 0.0) {
				secondWallpoint.x = (float)ix1;
				tz2 = iz1;
			}
			else {
				secondWallpoint.x = (float)ix2;
				tz2 = iz2;
			}
		}

		float x1Minimap = -firstWallpoint.x * 16 / tz1;
		float x2Minimap = -secondWallpoint.x * 16 / tz2;
		float y1aMinmimap = -500 / tz1;
		float y2aMinmimap = -500 / tz2;
		float y1bMinmimap = 500 / tz1;
		float y2bMinmimap = 500 / tz2;

		LinesPerspectiveTOP[0] = sf::Vector2f{ 500 + x1Minimap,500 + y1aMinmimap };
		LinesPerspectiveTOP[1] = sf::Vector2f{ 500 + x2Minimap,500 + y2aMinmimap };
		LinesPerspectiveBOTTOM[0] = sf::Vector2f{ 500 + x2Minimap,500 + y2bMinmimap };
		LinesPerspectiveBOTTOM[1] = sf::Vector2f{ 500 + x1Minimap,500 + y1bMinmimap };
		LinesPerspectiveLEFT[0] = sf::Vector2f{ 500 + x1Minimap,500 + y1aMinmimap };
		LinesPerspectiveLEFT[1] = sf::Vector2f{ 500 + x1Minimap,500 + y1bMinmimap };
		LinesPerspectiveRIGHT[0] = sf::Vector2f{ 500 + x2Minimap,500 + y2aMinmimap };
		LinesPerspectiveRIGHT[1] = sf::Vector2f{ 500 + x2Minimap,500 + y2bMinmimap };

		LinesPerspectiveTOP[0].color = sf::Color::Green;
		LinesPerspectiveBOTTOM[0].color = sf::Color::Green;
		LinesPerspectiveTOP[1].color = sf::Color::Green;
		LinesPerspectiveBOTTOM[1].color = sf::Color::Green;

		/*
		window->draw(LinesPerspectiveTOP, 2, sf::Lines);
		window->draw(LinesPerspectiveBOTTOM, 2, sf::Lines);
		window->draw(LinesPerspectiveLEFT, 2, sf::Lines);
		window->draw(LinesPerspectiveRIGHT, 2, sf::Lines);
		*/

		//Texter and perspective view

		
		float xscale1 = hfov / tz1;
		float yscale1 = vfov / tz1;
		long int x1 = int(xWidth / 2) - (firstWallpoint.x * xscale1);
		float xscale2 = hfov / tz2;
		float yscale2 = vfov / tz2;
		long int x2 = int(xWidth / 2) - (secondWallpoint.x * xscale2);
		/*
		cout << "i 1 : " << ix1 << " | " << iz1 << endl;
		cout << "i 2 : " << ix2 << " | " << iz2 << endl;
		
		cout << "Brut : " << firstWallpoint.x << " / " << secondWallpoint.x << " - " << (firstWallpoint.x * xscale1) << endl;
		cout << "Scaled : " << x1 << " / " << x2 << endl;
		*/
		//x1 = (int)fmax(x1, 0);
		//x2 = (int)fmin(x2, xWidth);
		if (x1 >= x2 || x2 < 0  || x1 > (int)xWidth ) {
			bwasRendered = false;
			return;
		}
		else{
			float yceil = myMap->mapSectors[sectorIndex].CeilHeight - playerPosition.z;
			float yfloor = myMap->mapSectors[sectorIndex].FloorHeight - playerPosition.z;

			

			int neighbor = myMap->mapSectors[sectorIndex].sectorWalls[wallIndex].neighboorValue;
			float nyceil = 0, nyfloor = 0;
			if (neighbor >= 0) // Is another sector showing through this portal?
			{
				nyceil = myMap->mapSectors[neighbor].CeilHeight - playerPosition.z;
				nyfloor = myMap->mapSectors[neighbor].FloorHeight - playerPosition.z;
			}
				
			#define Yaw(y,z) (y + z*playerYaw)
			int y1a = yHeight / 2 - (int)(Yaw(yceil, tz1) * yscale1), y1b = yHeight / 2 - (int)(Yaw(yfloor, tz1) * yscale1);
			int y2a = yHeight / 2 - (int)(Yaw(yceil, tz2) * yscale2), y2b = yHeight / 2 - (int)(Yaw(yfloor, tz2) * yscale2);
			/* The same for the neighboring sector */
			int ny1a = yHeight / 2 - (int)(Yaw(nyceil, tz1) * yscale1), ny1b = yHeight / 2 - (int)(Yaw(nyfloor, tz1) * yscale1);
			int ny2a = yHeight / 2 - (int)(Yaw(nyceil, tz2) * yscale2), ny2b = yHeight / 2 - (int)(Yaw(nyfloor, tz2) * yscale2);


			int beginx = (int)fmax(x1, 0);
			int endx = (int)fmin(x2, xWidth);

			if (currentPortal.xLimits.x > endx || currentPortal.xLimits.y < beginx)
			{
				return;
			}
			if (neighbor >= 0)
			{
				newPortal.xLimits.x = beginx;
				newPortal.xLimits.y = endx;
			}

			beginx = (int)fmax(x1, currentPortal.xLimits.x);
			endx = (int)fmin(x2, currentPortal.xLimits.y);
			//std::cout << "\x1B[2J\x1B[H";
			
			//beginx = (int)fmin(x1, x2);
			//endx = (int)fmax(x1, x2);

			for (int x = beginx; x < endx; ++x)
			{
				/* Acquire the Y coordinates for our ceiling & floor for this X coordinate. Clamp them. */
				int ya = (x - x1) * (y2a - y1a) / (x2 - x1) + y1a;
				int cya = clamp(ya, 0, yHeight - 1); // top
				int yb = (x - x1) * (y2b - y1b) / (x2 - x1) + y1b;
				int cyb = clamp(yb, 0, yHeight - 1); // bottom

				/* Render ceiling: everything above this sector's ceiling height. */
				vline(x, 0, cya , 0x111111, 0x222222, 0x111111, (myMap->mapSectors[sectorIndex].floorColor), currentPortalColor);
				/* Render floor: everything below this sector's floor height. */
				vline(x, cyb , yHeight, 0x0000FF, 0x0000AA, 0x0000FF, myMap->mapSectors[sectorIndex].floorColor + sf::Color(40, 40, 40, 0), currentPortalColor);
				if (neighbor >= 0)
				{
					/* Same for _their_ floor and ceiling */
					
					int nya = (x - x1) * (ny2a - ny1a) / (x2 - x1) + ny1a;
					int cnya = clamp(nya, 0, yHeight -1);
					int nyb = (x - x1) * (ny2b - ny1b) / (x2 - x1) + ny1b;
					int cnyb = clamp(nyb, 0, yHeight -1);
					//cout << "(Ceil) cya :" << cya << "  (NCeil) :" << cnya << endl;
					//cout << "(Floor )cyb :" << cyb << "  (NFloor) :" << cnyb << endl;
					/* If our ceiling is higher than their ceiling, render upper wall */
					//unsigned r1 = 0x010101 * (255 - z), r2 = 0x040007 * (31 - z / 8);
					vline(x, cya, cnya-1 ,0,0,0, myMap->mapSectors[neighbor].floorColor - sf::Color(40, 40, 40, 0), currentPortalColor); // Between our and their ceiling
					//ytop[x] = clamp(max(cya, cnya), ytop[x], H - 1);   // Shrink the remaining window below these ceilings
					/* If our floor is lower than their floor, render bottom wall */

					vline(x, cnyb , cyb+1, 0,0,0, myMap->mapSectors[neighbor].floorColor + sf::Color(20, 20, 20, 0), currentPortalColor); // Between their and our floor

					vline(x, cnya, cnyb, 0, 0, 0, newPortalColor, currentPortalColor);
					bwasRendered = true;
					//ybottom[x] = clamp(min(cyb, cnyb), 0, ybottom[x]); // Shrink the remaining window above these floors
				}
				else {
					vline(x, cya, cyb, 0, 0, 0, wallColor, currentPortalColor);
					bwasRendered = false;
				}	
			}
		}
		// Only render if it's visible
		/* Acquire the floor and ceiling heights, relative to where the player's view is */
		
	}
	else {
		//cout << "PAS de TZ" << endl;
	}


}

struct WallToTreat
{
	int sectorIndex;
	int wallIndex;
	int sectorNeighbor;
	sf::Color wallColor;
};
void Engine::RenderAllSectorWalls() {
	vector<PortalRender> Portals;
	PortalRender firstPortalRender;
	firstPortalRender.sectorIndex = playerCurrentSector;
	firstPortalRender.fromSectorIndex = playerCurrentSector;
	firstPortalRender.fromWallIndex = -1;
	firstPortalRender.portalColor = sf::Color::Black;
	firstPortalRender.xLimits.x = 0;
	firstPortalRender.xLimits.y = xWidth;
	Portals.push_back(firstPortalRender);

	int nbPortalPerFrame = 0;

	while (!Portals.empty())
	{
		PortalRender currentPortal = Portals.front();
		
		if (currentPortal.sectorIndex != -1)
		{
			for (int i = 0; i < myMap->mapSectors[currentPortal.sectorIndex].nbWalls; i++) {
				bool bIsWallRendered = false;
				WallToTreat wallToTreat;
				wallToTreat.sectorIndex = currentPortal.sectorIndex;
				wallToTreat.wallIndex = i;
				wallToTreat.sectorNeighbor = myMap->mapSectors[currentPortal.sectorIndex].sectorWalls[i].neighboorValue;
				wallToTreat.wallColor = myMap->mapSectors[currentPortal.sectorIndex].sectorWalls[i].WallColor;

				PortalRender newPortalRender;
				newPortalRender.portalColor = sf::Color(rand()%256, rand() % 256, rand() % 256, 255);
				newPortalRender.sectorIndex = wallToTreat.sectorNeighbor;
				newPortalRender.fromSectorIndex = currentPortal.sectorIndex;
				newPortalRender.fromWallIndex = i;

				CalcTranformAndRotatedWall(wallToTreat.sectorIndex, wallToTreat.wallIndex);
				CalcPerspectiveWall(wallToTreat.sectorIndex, wallToTreat.wallIndex, wallToTreat.wallColor, bIsWallRendered, currentPortal,newPortalRender);
				if (bIsWallRendered && newPortalRender.sectorIndex != -1)
				{
					Portals.push_back(newPortalRender);
					nbPortalPerFrame++;
				}
				if (bDebugRenderOn)
				{
					for (auto i = 0; i < xWidth; i++) {
						for (auto j = 0; j < yHeight; j++) {
							imageRender.setPixel(i, j, pixelTab[i * yHeight + j]);
						}
					}
					textureRender.update(imageRender);
					spriteRender.setTexture(textureRender);
					window->draw(spriteRender);

					window->display();
					bool bNextStep = false;
					sf::Event event;
					while (bNextStep == false)
					{
						sf::Event event;
						while (window->pollEvent(event))
						{
							if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Space)) {
								bNextStep = true;
							}
							else if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::P)) {
								bDebugRenderOn = false;
								bNextStep = true;
							}
						}

					}
				}
			}			
		}
		Portals.erase(Portals.begin());	
	}
	//cout << "Portal num : " << nbPortalPerFrame << endl;
}

float Engine::FNCross(float x1, float y1, float x2, float y2) { return (x1 * y2 - y1 * x2); }

void Engine::Intersect(double x1, double y1 , double x2, double y2 , double x3, double y3 , double x4, double y4 , double& x, double& y) {
	#define vxs(x0,y0, x1,y1)    ((x0)*(y1) - (x1)*(y0))
	/*float ax;
	float ay;
	ax  = FNCross(x1, y1, x2, y2);
	ay = FNCross(x3, y3, x4, y4);
	float det = FNCross(x1 - x2, y1 - y2, x3 - x4, y3 - y4);
	ax = FNCross(x, x1 - x2, y, x3 - x4) / det;
	ay = FNCross(x, y1 - y2, y, y3 - y4) / det;
	if (det == 0) {
		cout << "DET = 0" << endl;
	}*/

	x = vxs(vxs(x1, y1, x2, y2), (x1)-(x2), vxs(x3, y3, x4, y4), (x3)-(x4)) / vxs((x1)-(x2), (y1)-(y2), (x3)-(x4), (y3)-(y4));
	y = vxs(vxs(x1, y1, x2, y2), (y1)-(y2), vxs(x3, y3, x4, y4), (y3)-(y4)) / vxs((x1)-(x2), (y1)-(y2), (x3)-(x4), (y3)-(y4));

}

void Engine::RenderMinimaps() {
	playerMinimap.setPosition((playerPosition.x-playerMinimapRadius) , (playerPosition.y - playerMinimapRadius) );
	playerDirMinimap.setPosition(((playerPosition.x + cos(playerVisionAngle * PI/180) * offsetPlayerDirMinimap) -playerDirMinimapRadius) , ((playerPosition.y + sin(playerVisionAngle * PI / 180) * offsetPlayerDirMinimap ) - playerDirMinimapRadius) );

	LinesDirVisionMinimap[0] = sf::Vector2f {playerPosition.x, playerPosition.y};
	LinesDirVisionMinimap[1] = sf::Vector2f{ playerDirMinimap.getPosition().x + playerDirMinimapRadius, playerDirMinimap.getPosition().y + playerDirMinimapRadius };

	window->draw(LinesDirVisionMinimap, 2, sf::Lines);
	window->draw(playerDirMinimap);
	window->draw(playerMinimap);
	window->draw(WallsLines, 2, sf::Lines);

	

	window->draw(LinesDirVisionTransformedMinimap, 2, sf::Lines);
	window->draw(playerTransformedDirMinimap);
	window->draw(playerTransformedMinimap);
	window->draw(WallsTransformedLines, 2, sf::Lines);
	
	

	
}

void Engine::Render() {
	window->clear(sf::Color::Black);
	
	for (auto i = 0; i < xWidth; i++) {
		for (auto j = 0; j < yHeight; j++) {
			pixelTab[i * yHeight + j] = sf::Color::Black;
		}
	}

	RenderAllSectorWalls();

	for (auto i = 0; i < xWidth; i++) {
		for (auto j = 0; j < yHeight; j++) {
			imageRender.setPixel(i, j, pixelTab[i * yHeight + j]);
		}
	}
	if (bDebugRenderOn)
	{
		return;
	}
	textureRender.update(imageRender);
	spriteRender.setTexture(textureRender);
	spriteRender.setScale(sf::Vector2f{ (float)resolutionFactor,(float)resolutionFactor });
	window->draw(spriteRender);
	//RenderMinimaps();
	window->display();
	
}


void Engine::vline(int x, int y1, int y2, int top, int middle, int bottom,sf::Color col,sf::Color portalColor)
{
	y1 = clamp(y1, 0, yHeight - 1);
	y2 = clamp(y2, 0, yHeight - 1);

	for (int y = y1 ; y < y2; ++y) {
		if(pixelTab[x * yHeight + y] == portalColor)
		pixelTab[x * yHeight + y] = col;
	}
}

void Engine::movePlayerOnInput(sf::Vector2i dir) {
	sf::Vector2f movement = { 0,0 };
	if (dir.y > 0) {
		movement.x = -cos(playerVisionAngle * PI / 180)/3;
		movement.y = -sin(playerVisionAngle * PI / 180)/3;
	}
	else if (dir.y < 0) {
		movement.x = cos(playerVisionAngle * PI / 180)/3;
		movement.y = sin(playerVisionAngle * PI / 180)/3;
	}
	if (dir.x > 0) {
		movement.x += cos((90.0 + (double)playerVisionAngle) * PI / 180)/3;
		movement.y += sin((90.0 + (double)playerVisionAngle) * PI / 180)/3;
	}
	else if (dir.x < 0) {
		movement.x += -cos((90.0 + (double)playerVisionAngle) * PI / 180)/3;
		movement.y += -sin((90.0 + (double)playerVisionAngle) * PI / 180)/3;
	}
	movement.x *= 3;
	movement.y *= 3;
	if (movement.x != 0 || movement.y != 0)updatePlayerSector(movement);
	playerPosition.x += movement.x;
	playerPosition.y += movement.y;
}
void Engine::updatePlayerSector(sf::Vector2f movement) {
	for (auto i = 0; i < myMap->mapSectors[playerCurrentSector].nbWalls;i++) {
		bool isClockWise = false;
		if (doIntersect(sf::Vector2f{ playerPosition.x,playerPosition.y }, sf::Vector2f{ playerPosition.x + movement.x,playerPosition.y + movement.y },
			myMap->mapSectors[playerCurrentSector].sectorWalls[i].Vertices[0], myMap->mapSectors[playerCurrentSector].sectorWalls[i].Vertices[1],isClockWise)) {
			if (myMap->mapSectors[playerCurrentSector].sectorWalls[i].neighboorValue != -1 && isClockWise) {
				int neighboorValue = myMap->mapSectors[playerCurrentSector].sectorWalls[i].neighboorValue;
				playerPosition.z = playerPosition.z - (myMap->mapSectors[playerCurrentSector].FloorHeight - myMap->mapSectors[neighboorValue].FloorHeight);
				playerCurrentSector = neighboorValue;
				
			}

			break;
		}
	}
}

void Engine::rotatePlayerOnMouse(sf::Vector2i mousePos, sf::RenderWindow& window) {
	sf::Vector2i centerScreenPos = { (int)xWidth * resolutionFactor / 2,(int)yHeight * resolutionFactor / 2 };
	if (mousePos.x != centerScreenPos.x) {
		if (mousePos.x > centerScreenPos.x) {
			playerVisionAngle = playerVisionAngle + float((mousePos.x - centerScreenPos.x)) / 10;
		}
		else {
			playerVisionAngle = playerVisionAngle + float((mousePos.x - centerScreenPos.x)) / 10;
		}		
	}

	if (mousePos.y != centerScreenPos.y) {
		if (mousePos.y > centerScreenPos.y) {
			playerYaw = playerYaw + float(float(mousePos.y - centerScreenPos.y) / 100);
		}
		else {
			playerYaw = playerYaw + float(float(mousePos.y - centerScreenPos.y) / 100);
		}
	}

	sf::Mouse::setPosition(centerScreenPos, window);
}
