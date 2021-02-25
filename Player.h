#pragma once

#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <conio.h>
#include <vector>
#include "Box.h"


class Player
{
public:
	Player();
	Player(int m_Posx, int m_Posy, bool IsOnDestination);
	~Player();

	int getPosY();
	int getPosx();
	void setPos(int y, int x);

	void goUP();
	void goLeft();
	void goDown();
	void goRight();

	void pushBoxUp(Box &boxs);
	void pushBoxLeft(Box &boxs);
	void pushBoxRight(Box &boxs);
	void pushBoxDown(Box &boxs);

	//status
	bool getIsOnDestinationP();
	void setOnDestinationP();
	void setNoDestinationP();

private:
	int m_Posx;
	int m_Posy;

	bool IsOnDestination;


};

#endif