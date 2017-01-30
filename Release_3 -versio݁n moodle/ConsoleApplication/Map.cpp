#include "Map.h"
#include "Game.h"


Map::Map() {

	_arrayCells = 0;
}

Map::Map(Cell **arrayCells, int _xElements, int _yElements)
{
	this->_arrayCells = arrayCells;
}


Map::~Map()
{
	for (int i = 0; i < _xElements; i++) {
		delete[] _arrayCells[i];
	}
	delete[] _arrayCells;
}

void Map::initMap(SDLInterface  *graphicGame) {
	_graphic = graphicGame;
	
	if (_init == false) {
		apple.setXApplePosition();
		apple.setYApplePosition();
		_init = true;
	}

	_xElements = MAX_ROW;
	_yElements = MAX_COLUMN;
	
	_arrayCells = new Cell*[_xElements];

	if (_arrayCells == 0)
		throw std::exception("System was not able to allocate memory");

	for (int i = 0; i < _xElements; i++) {
		_arrayCells[i] = new Cell[_yElements];
		if (_arrayCells[i] == 0)
			throw std::exception("System was not able to allocate memory");
	}
	


	

	//Poner a cada casilla del map un ID de la textura
	for (int a = 0; a < MAX_ROW; a++) {
		for (int b = 0; b < MAX_COLUMN; b++) {
			_arrayCells[a][b].setMaterial(SPRITE_GRID);
		}
	}
	if (_easy == true) {
		for (int a = 0; a < MAX_COLUMN; a++) {
			_arrayCells[0][a].setMaterial(SPRITE_OBSTACLE);
			_arrayCells[34][a].setMaterial(SPRITE_OBSTACLE);
		}
	}
	if (_medium == true) {
		for (int a = 0; a < MAX_COLUMN; a++) {
			_arrayCells[0][a].setMaterial(SPRITE_OBSTACLE);
			_arrayCells[33][a].setMaterial(SPRITE_OBSTACLE);
		}
	}
	if(_hard == true){
		for (int a = 0; a < MAX_COLUMN; a++) {
			_arrayCells[0][a].setMaterial(SPRITE_OBSTACLE);
			_arrayCells[32][a].setMaterial(SPRITE_OBSTACLE);
		}
	}

	for (int a = 0; a < MAX_ROW; a++) {
		_arrayCells[a][0].setMaterial(SPRITE_OBSTACLE);
		_arrayCells[a][19].setMaterial(SPRITE_OBSTACLE);
	}


}





void Map::drawMap() {
	if (_easy == true) {
		int numColumnas = MAX_ROW;
		int numFilas = MAX_COLUMN;
		for (int x = 0; x < numColumnas; x++) {
			for (int y = 0; y < numFilas; y++) {
				_graphic->drawTexture(_arrayCells[x][y].getMaterial(), 0, 0, 20, 20, x*SPRITE_DEFAULT_HEIGHT, y*SPRITE_DEFAULT_WIDTH, 20, 20);
			}

		}

		if (snake.getXPosition() == 0 || snake.getYPosition() == 0 || snake.getXPosition() == MAX_ROW - 1 || snake.getYPosition() == MAX_COLUMN - 1) {
			//if (getLevel() == 1)
				snakeDeath();

			//else
			//	snakeDeath2();
		}
	}
	if (_medium == true) {
		int numColumnas = MAX_ROW-1;
		int numFilas = MAX_COLUMN;
		for (int x = 0; x < numColumnas; x++) {
			for (int y = 0; y < numFilas; y++) {
				_graphic->drawTexture(_arrayCells[x][y].getMaterial(), 0, 0, 20, 20, x*SPRITE_DEFAULT_HEIGHT, y*SPRITE_DEFAULT_WIDTH, 20, 20);
			}

		}

		if (snake.getXPosition() == 0 || snake.getYPosition() == 0 || snake.getXPosition() == MAX_ROW - 2 || snake.getYPosition() == MAX_COLUMN - 1) {
			snakeDeath();
		}
	}
	if (_hard == true) {
		int numColumnas = MAX_ROW-2;
		int numFilas = MAX_COLUMN;
		for (int x = 0; x < numColumnas; x++) {
			for (int y = 0; y < numFilas; y++) {
				_graphic->drawTexture(_arrayCells[x][y].getMaterial(), 0, 0, 20, 20, x*SPRITE_DEFAULT_HEIGHT, y*SPRITE_DEFAULT_WIDTH, 20, 20);
			}

		}

		if (snake.getXPosition() == 0 || snake.getYPosition() == 0 || snake.getXPosition() == MAX_ROW - 3 || snake.getYPosition() == MAX_COLUMN - 1) {
			snakeDeath();
		}
	}


	

	for (int i = 1; i <= snake.getSize(); i++) {
		if (snake._body[snake.n - i][0] == snake.getXPosition() && snake._body[snake.n - i][1] == snake.getYPosition()) { snakeDeath(); }
	}
}

void Map::change(int direction) {
	
}

void Map::moveSnake(int x, int y)
{
	initMap(_graphic);
	_arrayCells[apple.getXApplePosition()][apple.getYApplePosition()].setMaterial(SPRITE_APPLE);
	_arrayCells[x][y].setMaterial(snake.getSnakeSprite());
	printSnakeInMap();

	
}


int i = 0;
float Map::eatApple(float speed) {
	//No pudimos obtener la misma implementación que teníamos en el antiguo proyecto de candy ya que utilizabamos parte de la base del candy
	//Utilizamos una función nada ótpima para poder seguir la fórmula de las manzanas en la que, según el if, varia el número de 
	//manzanas que ha de comer el usuario y el score dependiendo de la manzana que haya comido.
	if (getLevel() == 1) {
		setScore(getScore()+100);
		snake.setSize(snake.getSize()+1);
		if (speed >= 0.01) {
			speed -= 0.01;
			apple.setXApplePosition();
			apple.setYApplePosition();
		}
		setLevel(2);
		snake.n = snake.n++; return speed;
	}
	if (getLevel() == 2) {
		
		if (i == 0) {
			setScore(getScore() + 100);
			snake.setSize(snake.getSize()+1);

			if (speed >= 0.01) {
				speed -= 0.01;
				apple.setXApplePosition();
				apple.setYApplePosition();
			}
			i = 1;
			snake.n = snake.n++; return speed;
		}
		if (i == 1) {
			setScore(getScore() + 200);
			snake.setSize(snake.getSize()+1);

			if (speed >= 0.01) {
				speed -= 0.01;
				apple.setXApplePosition();
				apple.setYApplePosition();
			}
			i = 2;
			setLevel(3);
			snake.n = snake.n++; return speed;
		}
	}
	if (getLevel() >= 3) {
		
		if (i == 2) {
			setScore(getScore() + 100);
			snake.setSize(snake.getSize() + 1);
			if (speed >= 0.01) {
				speed -= 0.01;
				apple.setXApplePosition();
				apple.setYApplePosition();
			}
			i = 3;
			snake.n = snake.n++; return speed;
		}
		if (i == 3) {
			setScore(getScore() + 200);
			snake.setSize(snake.getSize() + 1);
			if (speed >= 0.01) {
				speed -= 0.01;
				apple.setXApplePosition();
				apple.setYApplePosition();
			}
			i = 4;
			snake.n = snake.n++; return speed;
		}
		if (i == 4) {
			setScore(getScore() + 300);
			snake.setSize(snake.getSize() + 1);
			if (speed >= 0.01) {
				speed -= 0.01;
				apple.setXApplePosition();
				apple.setYApplePosition();
			}
			setLevel(4);
			//i = 5;
			snake.n = snake.n++; return speed;
		}
	}

	if (getLevel() == 4) {
		
			setScore(getScore() + 100);
			snake.setSize(snake.getSize() + 1);
			if (speed >= 0.01) {
				speed -= 0.01;
				apple.setXApplePosition();
				apple.setYApplePosition();
			}
			snake.n = snake.n++; return speed;
		
		
		
	}

}

bool Map::checkApple(int appleX, int appleY, int snakeX, int snakeY) {
	if (appleX == snakeX && appleY == snakeY) {

		return true;
	}
	
}


void Map::snakeDeath()
{
	//setTime(0);
	changeLevel(getLevel());
	snake.setLive(snake.getLive()-1);
	snake.setXPosition(2); 
	snake.setYPosition(2);
	snake.setDirection(3);
	snake.changeSpeed(snake.getSpeed());
	apple.setXApplePosition(); 
	apple.setYApplePosition();
	snake.n = 1;
	snake.setSize(0);
	setScore(0);
	//snake.beginT = clock()*CLK_TCK;

}

void Map::snakeDeath2() {
	changeLevel(getLevel());
	snake.setLive(snake.getLive() - 1);
	snake.setXPosition(2);
	snake.setYPosition(2);
	snake.setDirection(3);
	snake.changeSpeed(snake.getSpeed());
	apple.setXApplePosition();
	apple.setYApplePosition();
	snake.n = 1;
	setScore(0);
}

void Map::setScore(int s)
{
	_score = s;
}

int Map::getScore()
{
	return _score;
}


void Map::printSnakeInMap() {

	for (int i = 1; i <= snake.getSize(); i++) {
		_arrayCells[snake._body[snake.n - i][0]][snake._body[snake.n - i][1]].setMaterial(snake.getSnakeSprite());
		
	}
}

void Map::setLevel(int l) {
	_level = l;
}

int Map::getLevel() {
	return _level;
}


void Map::setTime(int t) {
	_levelTime = t;
}
void Map::changeLevel(int a) {
	_level = a;
}