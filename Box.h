#pragma once

#ifndef __BOX_H__
#define __BOX_H__


#define BOXMAXMUN 4
class Box
{
public:
	Box();
	Box(int Posy, int Posx, bool IsOnDestination);
	~Box();

	int getPosY();
	int getPosX();
	void setPos(int y, int x);

	void goUP();
	void goLeft();
	void goDown();
	void goRight();

	//status
	bool getIsOnDestinationB();
	void setOnDestinationB();
	void setNoDestinationB();

private:
	int m_Posx;
	int m_Posy;

	bool m_IsOnDestination;

};

#endif