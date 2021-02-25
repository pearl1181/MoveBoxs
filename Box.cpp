#include "Box.h"

Box::Box()
{
	this->m_Posx = -1;
	this->m_Posy = -1;

	this->m_IsOnDestination = false;
}

Box::Box(int Posy, int Posx, bool IsOnDestination)
{
	this->m_Posx = Posx;
	this->m_Posy = Posy;
	this->m_IsOnDestination = IsOnDestination;
}

Box::~Box()
{
}

int Box::getPosY()
{
	return m_Posy;
}

int Box::getPosX()
{
	return m_Posx;
}

void Box::setPos(int y, int x)
{
	this->m_Posy = y;
	this->m_Posx = x;
}

void Box::goUP()
{
	--m_Posy;
}

void Box::goLeft()
{
	--m_Posx;
}

void Box::goDown()
{
	++m_Posy;
}

void Box::goRight()
{
	++m_Posx;
}


bool Box::getIsOnDestinationB()
{
	return m_IsOnDestination;
}

void Box::setOnDestinationB()
{
	m_IsOnDestination = true;
}

void Box::setNoDestinationB()
{
	m_IsOnDestination = false;
}
