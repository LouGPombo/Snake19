#pragma once
#include "Cell.h"
#include "SDLInterface.h"
#include "GameConstants.h"
#include "Snake.h"
#include "Apple.h"
class Map 
{
private:
	
	int _needToEat;
	int _score;
	bool _init;
	int _xElements;
	int _yElements;

	SDLInterface *_graphic;
	Cell * * _arrayCells;
	
	
public:
	int _levelTime;

	Snake snake;
	Apple apple;
	int _level; //Hare los niveles directamente desde map ya que tengo aquí la mayoría de funciones y me gustaría mantener en Game solo los bucles para correr el juego
	bool _easy, _medium, _hard;//haré las modificaciones de grid,velocidad, tiempo y alimentos directamente en sus funcioes en lugar de crear un enum en GameConstant.

	Map();		
	Map(Cell ** arrayCells, int _xElements, int _yElements);
	~Map();
	//Hay setters o getters de algunas clases que actualmente están en público ya que previamente estaban en privada y fueron modificadas
	//por la comodidad de ser utilizadas varias veces en Game.cpp
	void initMap(SDLInterface *_graphic);
	void drawMap();
	void change(int direction);
	void moveSnake(int x, int y);
	void snakeDeath();
	void snakeDeath2();
	void setScore(int s);
	void printSnakeInMap();
	void setLevel(int l);
	void changeLevel(int a);
	void setTime(int t);
	float eatApple(float speed);
	bool checkApple(int appleX, int appleY, int snakeX, int snakeY);
	int getScore();
	int getLevel();
};

