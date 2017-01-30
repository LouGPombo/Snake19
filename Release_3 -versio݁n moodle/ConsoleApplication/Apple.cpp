#include "Apple.h"



Apple::Apple()
{
	_apple = 0;
	_appleX = 0;
	_appleY = 0;
}


Apple::~Apple()
{
}


void Apple::setXApplePosition()
{

		srand(time(NULL));
		_appleX = (int)rand() % 30 + 1;
	
}

void Apple::setYApplePosition()
{
	srand(time(NULL));
	_appleY = (int)rand() % 15 + 1;
}

int Apple::getAppleSprite()
{
	return SPRITE_APPLE;
}

int Apple::getXApplePosition()
{
	return _appleX;
}

int Apple::getYApplePosition()
{
	return _appleY;
}
