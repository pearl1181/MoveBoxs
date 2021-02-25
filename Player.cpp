#include "Player.h"

Player::Player()
{
	this->m_Posx = -1;
	this->m_Posy = -1;

	this->IsOnDestination = false;
}

Player::Player(int m_Posx, int m_Posy, bool IsOnDestination)
{
	this->m_Posx = m_Posx;
	this->m_Posy = m_Posy;
	this->IsOnDestination = IsOnDestination;
}

Player::~Player()
{
}

int Player::getPosY()
{
	return m_Posy;
}

int Player::getPosx()
{
	return m_Posx;
}

void Player::setPos(int y, int x)
{
	this->m_Posy = y;
	this->m_Posx = x;
}

void Player::goUP()
{
	--m_Posy;	
}

void Player::goLeft()
{
	--m_Posx;
}

void Player::goDown()
{
	++m_Posy;
}

void Player::goRight()
{
	++m_Posx;
}

void Player::pushBoxUp(Box &boxs)
{
	goUP();
	boxs.goUP();

}

void Player::pushBoxLeft(Box &boxs)
{
	goLeft();
	boxs.goLeft();
}

void Player::pushBoxRight(Box& boxs)
{
	goRight();
	boxs.goRight();
}

void Player::pushBoxDown(Box& boxs)
{
	goDown();
	boxs.goDown();
}

bool Player::getIsOnDestinationP()
{
	return IsOnDestination;
}

void Player::setOnDestinationP()
{
	IsOnDestination = true;
}

void Player::setNoDestinationP()
{
	IsOnDestination = false;
}






