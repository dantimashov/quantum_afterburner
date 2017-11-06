#pragma once
#include <SFML/Graphics.hpp>
#include "spacecraft.h"
#include "obstaclesAndBonuses.h"
#include <sstream>
#include <search.h>
using namespace sf;
using  namespace std;

const int SIZE = 1280;
const int HEIGHT_WINDOW = 600;
const int WIDTH_WINDOW = 800;
View view;


float distance(float x0, float y0, float x1, float y1);

void setView(float x, float y);

void gameStart();

void showMenu(RenderWindow& window);

void showResults(RenderWindow& window, int finalScore);
