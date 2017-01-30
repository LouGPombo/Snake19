#include "Snake.h"
#include "Game.h"

Snake::Snake()
{
	Cell _snake;
	Cell _bodySprite;
	Cell _tail;
	int _snakeSize = 0;
	int _lives = 3;
	int n=1;
	int _headXPos = -1;
	int _headYPos = -1;
	int _tailXPos = -1;
	int _tailYPos = -1;
	int _direction = 1;
	float _snakeSpeed = 0.5;

}

Snake::Snake(Cell snake, int headXPos, int headYPos, int direction)
{
	this->_snake = snake; _headXPos = headXPos; _headYPos = headYPos; _direction = direction;
}


Snake::~Snake()
{
}



void Snake::setSprite() {
	_snake.setMaterial(SPRITE_SNAKE);
	_bodySprite.setMaterial(SPRITE_SNAKE);
}



void Snake::setArrayPosition(int x, int y) {
	//for (int i = 0; i < 10; i++) {
	
		_body[n][0] = x;
		_body[n][1] = y;
		std::cout << "X  " << n << " : "<< x << std::endl;
		std::cout << "Y  " << n <<" : " << y << std::endl;
	//}
		n++;
		if (n == _snakeSize) {
			n = 1;
		}
}


/*void Snake::setTailXPosition(int x) {
	if(_snakeSize>0)
	_tailXPos = x;
}

void Snake::setTailYPosition(int y) {
	if (_snakeSize>0)
	_tailYPos = y;
}*/
void Snake::setLive(int l) {
	_lives = l;
}
void Snake::setXPosition(int x)
{
	_headXPos = x;
}

void Snake::setYPosition(int y)
{
	_headYPos = y;
}

void Snake::setDirection(int d)
{
	_direction = d;
}

void Snake::setSize(int s)
{
	_snakeSize = s;
}

void Snake::changeSpeed(float s)
{
	_snakeSpeed = s;

}


int Snake::getLive() {
	return _lives;
}

int Snake::getSize()
{
	return _snakeSize;
}

int Snake::getDirection()
{
	return _direction;
	//If 1 Up, 2 Down, 3 Right, 4 Left!
}

int Snake::getSnakeSprite()
{
	return _snake.getMaterial();
	return _bodySprite.getMaterial();
//	return _tail.getMaterial();

}

int Snake::getXPosition()
{
	return _headXPos;
}

int Snake::getYPosition()
{
	return _headYPos;
}

float Snake::getSpeed() {
	return _snakeSpeed;
}

/*int Snake::getLastX() {
	//return getXPosition();
	//return getXPosition();
	return _tailXPos;
}

int Snake::getLastY() {
	//return getYPosition();
	return _tailYPos;
}*
void Snake::changeNext() {

}*/