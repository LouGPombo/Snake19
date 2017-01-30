#pragma once
#pragma once
#include "Cell.h"
#include "GameConstants.h"
#include <stdio.h>     
#include <stdlib.h> 
#include <time.h>
class Apple
{
	/*La clase apple contendrá básicamente las posiciones x e y de Apple y su cell. Más adelante los getter & setter methods para que
	sus atributos privados se puedan acceder desde el grid (Map)*/
private:
	
	Cell _apple;
	int _appleX;
	int _appleY;

public:
	Apple();
	~Apple();

	
	void setXApplePosition();
	void setYApplePosition();
	int getAppleSprite();
	int getXApplePosition();
	int getYApplePosition();
	

};