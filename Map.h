#pragma once

#ifndef __MAP_H__
#define __MAP_H__

#include <graphics.h>
#include <Windows.h>
#include <iostream>
#include <fstream>
#include <vector>
#include "Player.h"
#include "Box.h"

using namespace std;

#define MAPX 10
#define MAPY 10
#define MAPSIZE 10

//0: area
//1: wall
//2: box
//3: people
//4: destination
//5: the box overlaps with the destination
//6: people + destination

enum obj {
	AREA,
	WALL,
	BOX,
	PLAYER,
	DESTINATION,
	BOXDESTINATION,
	PLAYERDESTINATION
};
class Map
{
public:
	Map();
	~Map();

	void Initdestination(int destination[BOXMAXMUN][2]);	


	bool openFile(int map[MAPY][MAPX], int *custom);

	bool goingGame(int map[MAPY][MAPX]);
	
	void printMap(int gameMap[MAPY][MAPX],int num);

	int getCommand(Player *player, vector<Box> &boxs, int map[MAPY][MAPX]);

	bool GameOver(int map[MAPY][MAPX], vector<Box> &boxs);

private:

};

#endif