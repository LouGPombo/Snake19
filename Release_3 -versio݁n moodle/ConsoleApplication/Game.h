#pragma once

//Third-party libraries
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>			//OpenGL Mathematics 
#include <iostream>
#include <time.h>
#include "GameConstants.h"
#include "SDLInterface.h"
#include "InputManager.h"
#include "Sprite.h"
#include "Cell.h"
#include "Map.h"
#include "bar.h"
#include <iostream>
#include <time.h>
#include <rapidxml.hpp>
#include <rapidxml_iterators.hpp>
#include <rapidxml_print.hpp>
#include <rapidxml_utils.hpp>
#include "Score.h"
using namespace rapidxml;
using namespace std;
/*
* Maneja la ejecución del juego
*/
class Game {
public:
	Game(std::string windowTitle, int screenWidth, int screenHeight);	//Constructor
	~Game();															//Destructor
	void run();
	//Game execution	

private:
	//Attributes	
	string playerName;
	bool writeRanking1, writeRanking2, writeRakning3;
	int result1, result2, result3;
	bool activa;
	bool writeName;
	bool easy, medium, hard;
	bool pause = false;
	std::string _windowTitle;		//SDLInterface Title
	int _screenWidth;				//Screen width in pixels				
	int _screenHeight;				//Screen height in pixels				
	GameState _gameState;			//It describes the game state	
	SDLInterface _graphic;			//Manage the SDL graphic library		
	Sprite hero;
	Sprite hello;
	Snake snake;
	Map _map;
	int _level;
	movement _nextMovement;
												//Internal methods for the game execution
	void init();
	void gameLoop();
	void executePlayerCommands();
	void executeMenuCommands();
	void executeGameMenuCommands();
	void controlTime();
	void chooseRanking();
	void renderGame();
	void drawMenu();
	void drawGameMenu();
	void drawGame();
	void drawRanking();
	void readEasyXML();
	void readMediumXML();
	void readHardXML();
	void gameOver();
	void drawSprite(Sprite & e);

	void createRankingFile(char filename[100]);

	void setNameFile();

	string getNameFile();

	void fileBusinessEndGame();

	void quickSortScore(Score arr[], int left, int right);

	void quickSort(int arr[], int left, int right);


	//time:
	float timer = 0; //Tiempo en segundos del nivel
	float crono = 0; // se le resta al tiempo del nivel el valor de timer para dar el valor del crono
	float snakeTimer;
	float snakeCrono;
	float snakeSpeed  =0.5;
	int snakeSize = 0;
	int minutes = 0; //Conversion en minutos
	int seconds = 0; //Conversion en segundos
	bool timeOne = false, timeTwo = false, timeThree = false;
};

