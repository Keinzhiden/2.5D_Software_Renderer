#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>
#include <math.h>
#include <iostream>
#include <map>
#include <vector>

bool onSegment(sf::Vector2f p, sf::Vector2f q, sf::Vector2f r);
int clamp(int value, int a, int b);

// To find orientation of ordered triplet (p, q, r).
// The function returns following values
// 0 --> p, q and r are colinear
// 1 --> Clockwise
// 2 --> Counterclockwise
int orientation(sf::Vector2f p, sf::Vector2f q, sf::Vector2f r);

// The main function that returns true if line segment 'p1q1'
// and 'p2q2' intersect.
bool doIntersect(sf::Vector2f p1, sf::Vector2f q1, sf::Vector2f p2, sf::Vector2f q2, bool& clockWise);