
#include "Game.h"

Game::Game(std::string windowTitle, int screenWidth, int screenHeight) :
	_windowTitle(windowTitle),
	_screenWidth(screenWidth),
	_screenHeight(screenHeight),
	_gameState(GameState::INIT) {}

Game::~Game()
{
}


void Game::run() {
	//Prepare the game components
	init();
	//Start the game if everything is ready
	gameLoop();
}

/*
* Initialize all the components
*/
void Game::init() {
	
	_map.snake.setLive(3);
	//std::cout << _map.snake.getLive();
	
	_map.snake.setSize(0);
	_map.snake.changeSpeed(0.5);
	_map.snake.setDirection(3);
	//std::cout << _map.getSpeed() << std::endl;
	_map.snake.setXPosition(2);
	_map.snake.setYPosition(2);
	_map.snake.setLive(3);
	srand((unsigned int)time(NULL));
	//Create a window
	_graphic.createWindow(_windowTitle, _screenWidth, _screenHeight, false);
	_graphic.setWindowBackgroundColor(255, 255, 255, 255);
	
	_graphic.loadTexture(SPRITE_SNAKE, "../sharedResources/images/characters/snake.png");
	_graphic.loadTexture(SPRITE_OBSTACLE, "../sharedResources/images/terrain/obstacle.bmp");

	_graphic.loadTexture(SPRITE_GRID, "../sharedResources/images/terrain/grid.bmp");
	_graphic.loadTexture(SPRITE_APPLE, "../sharedResources/images/terrain/apple.bmp");


	_graphic.setFontStyle(TTF_STYLE_NORMAL);

	//init map
	_map.initMap(&_graphic);

}


/*
* Game execution: Gets input events, processes game logic and draws sprites on the screen
*/
void Game::gameLoop() {

	_gameState = GameState::MENU;

	while (_gameState != GameState::EXIT) {
		//Detect keyboard and/or mouse events
		_graphic.detectInputEvents();

		if (_gameState == GameState::MENU && _gameState != GameState::GAMEMENU && _gameState != GameState::PLAY) {
			executeMenuCommands();
		}
		else if (_gameState == GameState::GAMEMENU && _gameState != GameState::MENU && _gameState != GameState::PLAY) {
			executeGameMenuCommands();
		}
		else if (_gameState == GameState::PLAY && _gameState != GameState::MENU && _gameState != GameState::GAMEMENU) {
			//Execute the player commands 

			executePlayerCommands();
			//Update the game physics
			
		}//Render game
		renderGame();
	}

}

void Game::executeMenuCommands() {
	glm::ivec2 mouseCoords;

	if (_graphic.isKeyPressed(SDL_BUTTON_LEFT)) {
		mouseCoords = _graphic.getMouseCoords();
		//::cout << "Screen (" << mouseCoords.x << ", " << mouseCoords.y << ")" << std::endl;

		if (mouseCoords.x >= 300 && mouseCoords.x <= 350 && mouseCoords.y >= 250 && mouseCoords.y <= 270) {
			_gameState = GameState::GAMEMENU;
		}
		if (mouseCoords.x >= 300 && mouseCoords.x <= 350 && mouseCoords.y >= 350 && mouseCoords.y <= 370) {
			_gameState = GameState::EXIT;
		}
	}
}

void Game::executeGameMenuCommands() {
	glm::ivec2 mouseCoords;

	if (_graphic.isKeyPressed(SDL_BUTTON_LEFT)) {
		mouseCoords = _graphic.getMouseCoords();
		//std::cout << "Screen (" << mouseCoords.x << ", " << mouseCoords.y << ")" << std::endl;

		if (mouseCoords.x >= 300 && mouseCoords.x <= 350 && mouseCoords.y >= 250 && mouseCoords.y <= 270) {
			
			_map._easy = true;
			_map._medium = false;
			_map._hard = false;
			_map.snake.changeSpeed(0.5);
			_map.setLevel(1);
			//cout << "GOLASDASD" << _map._levelTime << endl;
			//Utilizamos la fórmula del tiempo para los niveles dónde t = 60, aunque lo integramos directamente ya que son números "pequeños" y así nos ahorramos un integer en Map o global.
			//_map.setTime(240);
			_map.setTime(240);
			_gameState = GameState::PLAY;
		}
		if (mouseCoords.x >= 300 && mouseCoords.x <= 395 && mouseCoords.y >= 300 && mouseCoords.y <= 319) {
			_map._easy = false;
			_map._medium = true;
			_map._hard = false;
			_map.snake.changeSpeed(0.25);
			_map.setLevel(1);
			//_map.setTime(120);
			_map.setTime(120);
			_gameState = GameState::PLAY;
		}
		if (mouseCoords.x >= 300 && mouseCoords.x <= 350 && mouseCoords.y >= 350 && mouseCoords.y <= 370) {
			_map._easy = false;
			_map._medium = false;
			_map._hard = true;
			_map.snake.changeSpeed(0.125);
			_map.setLevel(1);
			//_map.setTime(60);
			_map.setTime(60);
			_gameState = GameState::PLAY;
		}
	}
}


void Game::executePlayerCommands() {
	controlTime();
	//std::cout << "x: " << hero.getXAtWorld() << std::endl;
	//std::cout << "y: " << hero.getYAtWorld() << std::endl;
	glm::ivec2 mouseCoords;


	if (_graphic.isKeyPressed(SDL_BUTTON_LEFT)) {
		mouseCoords = _graphic.getMouseCoords();
		std::cout << "Screen (" << mouseCoords.x << ", " << mouseCoords.y << ")" << std::endl;
	}
	

	if (_graphic.isKeyPressed(SDLK_ESCAPE) ) {
		pause = !pause;
		
	}

	if (_graphic.isKeyDown(SDLK_UP) && _map.snake.getDirection()!=2) {
		
		_map.snake.setDirection(1);
	}

	if (_graphic.isKeyDown(SDLK_LEFT) && _map.snake.getDirection() != 3) {
		_map.snake.setDirection(4);
		
	}
	if (_graphic.isKeyDown(SDLK_DOWN) && _map.snake.getDirection() != 1) {
		_map.snake.setDirection(2);
	}

	if (_graphic.isKeyDown(SDLK_RIGHT) && _map.snake.getDirection() != 4) {
		_map.snake.setDirection(3);
	}


	
}


/**
* Render the game on the screen
*/


void Game::gameOver() {
	//std::cout << _map.snake.getLive();
	if (_map.snake.getLive() == 0) {
		_gameState = GameState::GAMEMENU;
		_map.snake.setLive(3);
	}
}

clock_t snakeBegin = clock()*CLK_TCK;

void Game::controlTime() {

	clock_t t(clock() * CLK_TCK);
	clock_t snakeEnd(clock() * CLK_TCK);
	snakeTimer = (snakeEnd - snakeBegin) / (1000);
	timer = (t - _map.snake.beginT) / (1000 * 1000);

	crono = _map._levelTime - (timer);
	minutes = (int)crono / 60;
	seconds = (int)crono % 60;
	//cout <<" AAAA " << timer << endl;
	//cout << " BBBB " << seconds << endl;
	if (_map._easy == true) {
		if (seconds <= 0) {
			crono = crono + 240;
		}
		if (seconds == 0 && timeOne == false) {
			_map.snakeDeath();
			timeOne = true;
		}
		if (seconds <= -240) {
			crono = crono + 480;
		}
		if (seconds == -240 && timeOne == false) {
			_map.snakeDeath();
			timeOne = true;
		}
		if (seconds <= -480) {
			crono = crono + 960;
		}
		if (seconds == -480 && timeOne == false) {
			_map.snakeDeath();
			timeOne = true;
		}
	}
	if (_map._medium == true) {
		if (seconds <= 0) {
			crono = crono + 120;
		}
		if (seconds == 0 && timeOne == false) {
			_map.snakeDeath();
			timeOne = true;
		}
		if (seconds <= -120) {
			crono = crono + 240;
		}
		if (seconds == -120 && timeOne == false) {
			_map.snakeDeath();
			timeOne = true;
		}
		if (seconds <= -240) {
			crono = crono + 480;
		}
		if (seconds == -240 && timeOne == false) {
			_map.snakeDeath();
			timeOne = true;
		}
	}
	if (_map._hard == true) {
		if (seconds <= 0) {
			crono = crono + 60;
		}
		if (seconds == 0 && timeOne == false) {
			_map.snakeDeath();
			timeOne = true;
		}
		if (seconds <= -60) {
			crono = crono + 120;
		}
		if (seconds == 0 && timeOne == false) {
			_map.snakeDeath();
			timeOne = true;
		}
		if (seconds <= -120) {
			crono = crono + 240;
		}
		if (seconds == -120 && timeOne == false) {
			_map.snakeDeath();
			timeOne = true;
		}
	}
	//if (seconds == 0 || seconds == -30 || seconds == -60) {
	//	_map.snake.setLive(_map.snake.getLive() - 1);
	//}
}

void Game::renderGame() {
	
	
	//Clear the screen
	_graphic.clearWindow();
	//Draw the screen's content based on the game state
	if (_gameState == GameState::MENU) {
		drawMenu();
	}

	if (_gameState == GameState::GAMEMENU) {
		drawGameMenu();
	}

	if (_gameState == GameState::PLAY) {
		if (pause == false) {
			gameOver();
			
			

			if (_map.checkApple(_map.apple.getXApplePosition(), _map.apple.getYApplePosition(), _map.snake.getXPosition(), _map.snake.getYPosition()) == true) {
				_map.snake.changeSpeed(_map.eatApple(_map.snake.getSpeed()));
			}

			if (snakeTimer > _map.snake.getSpeed() * 1000) {
				snakeBegin = clock()*CLK_TCK;

				if (_map.snake.getDirection() == 1) {//arriba

					_map.snake.setArrayPosition(_map.snake.getXPosition(), _map.snake.getYPosition());

					_map.snake.setYPosition(_map.snake.getYPosition() - 1);
					
		
				}
				if (_map.snake.getDirection() == 2) {//abajo

					_map.snake.setArrayPosition(_map.snake.getXPosition(), _map.snake.getYPosition());
					_map.snake.setYPosition(_map.snake.getYPosition() + 1);
					//snakeTimer = 0;

					//std::this_thread::sleep_for(dura);
				}
				if (_map.snake.getDirection() == 3) {//derecha

					_map.snake.setArrayPosition(_map.snake.getXPosition(), _map.snake.getYPosition());

					_map.snake.setXPosition(_map.snake.getXPosition() + 1);
					//snakeTimer = 0;
					//std::this_thread::sleep_for(dura);
				}
				if (_map.snake.getDirection() == 4) {//izquierda
								//_map.snake.setTailXPosition(_map.snake.getXPosition());
								//_map.snake.setTailYPosition(_map.snake.getYPosition());
					_map.snake.setArrayPosition(_map.snake.getXPosition(), _map.snake.getYPosition());

					_map.snake.setXPosition(_map.snake.getXPosition() - 1);
					//snakeTimer = 0;
					//	std::this_thread::sleep_for(dura);
				}
			}


			//_map.moveSnake(snake);
			drawGame();
		}
		else if (pause == true) {
			drawGame();
			_graphic.drawText("PAUSE", BLACK, WHITE, 300, 250);
		}
	}
	//Refresh screen
	_graphic.refreshWindow();
}

/*
* Draw the game menu
*/
void Game::drawMenu() {
	
	_graphic.drawText(" ¡¡SNAKE!!", RED, WHITE, 280, 20);
	_graphic.drawText("PLAY", BLACK, WHITE, 300, 250);
	_graphic.drawText("EXIT", BLACK, WHITE, 300, 350);
	
}

void Game::drawGameMenu() {

	_graphic.drawText(" ¡¡SNAKE!!", RED, WHITE, 276, 20);
	_graphic.drawText("EASY", BLACK, WHITE, 300, 250);
	_graphic.drawText("MEDIUM", BLACK, WHITE, 300, 300);
	_graphic.drawText("HARD", BLACK, WHITE, 300, 350);

}

/*
* Draw the game, winner or loser screen
*/
void Game::drawGame() {
	//_map.initMap(&_graphic);
	_map.drawMap();
	
		//std::cout << "x " << _map.getXPosition() << std::endl;
		//std::cout << "y" << _map.getYPosition() << std::endl;
	//std::cout<<" TIME "<< seconds << seconds << std::endl;
	_map.moveSnake(_map.snake.getXPosition(), _map.snake.getYPosition());
	_graphic.drawText("SCORE:" + std::to_string(_map.getScore()), BLACK, WHITE, 0, 600);
	_graphic.drawText("LEVEL:" + std::to_string(_map.getLevel()), BLACK, WHITE, 0, 550);
	_graphic.drawText("LIVES:" + std::to_string(_map.snake.getLive()), BLACK, WHITE, 0, 500);
	
	_graphic.drawRectangle(BLACK,77,448,crono,30);
	_graphic.drawText("TIME: " , BLACK, WHITE, 0, 450);
	
	
	//drawSprite(hero);
	
}

void Game::drawSprite(Sprite & sprite) {
	_graphic.drawTexture(sprite.getSpriteId(), SPRITE_DEFAULT_WIDTH*sprite.getCurrentFrame(), 0, SPRITE_DEFAULT_WIDTH, SPRITE_DEFAULT_HEIGHT
		, sprite.getXAtWorld(), sprite.getYAtWorld(), SPRITE_DEFAULT_WIDTH, SPRITE_DEFAULT_HEIGHT);
}

