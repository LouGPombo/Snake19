
#include "Game.h"
#include <fstream>

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
	activa = false;
	writeName = false;
	//Start the game if everything is ready
	gameLoop();
}

/*
* Initialize all the components
*/
Score scores[13];

void Game::init() {
	writeRanking1 = false;
	writeRanking2 = false;
	writeRakning3 = false;
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

		if (_gameState == GameState::MENU) {
			executeMenuCommands();
		}
		else if (_gameState == GameState::RANKING) {
			drawRanking();
		}
		else if (_gameState == GameState::GAMEMENU) {
			executeGameMenuCommands();
		}
		else if (_gameState == GameState::PLAY) {
			//Execute the player commands 

			executePlayerCommands();
			//Update the game physics
			
		}//Render game
		renderGame();
	}

}

void Game::executeMenuCommands() {
	glm::ivec2 mouseCoords;
	if (activa == true) {
		createRankingFile("ranking");

		setNameFile();


		activa = false;
		writeName = false;
		//hero.setPositionAtScreen(hero.getXAtScreen() + 100, hero.getYAtScreen() + 100);
		_gameState = GameState::GAMEMENU;
	}
	if (_graphic.isKeyPressed(SDL_BUTTON_LEFT)) {
		mouseCoords = _graphic.getMouseCoords();
		std::cout << "Screen (" << mouseCoords.x << ", " << mouseCoords.y << ")" << std::endl;

		if (mouseCoords.x >= 300 && mouseCoords.x <= 350 && mouseCoords.y >= 250 && mouseCoords.y <= 270) {
			//_gameState = GameState::GAMEMENU;
			writeName = true;
		}
		if (mouseCoords.x >= 300 && mouseCoords.x <= 409 && mouseCoords.y >= 300 && mouseCoords.y <= 326) {
			fileBusinessEndGame();
			_gameState = GameState::RANKING;
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
		std::cout << "Screen (" << mouseCoords.x << ", " << mouseCoords.y << ")" << std::endl;

		if (mouseCoords.x >= 300 && mouseCoords.x <= 350 && mouseCoords.y >= 250 && mouseCoords.y <= 270) {
			readEasyXML();
			_map._easy = true;
			_map._medium = false;
			_map._hard = false;
			_gameState = GameState::PLAY;
		}
		if (mouseCoords.x >= 300 && mouseCoords.x <= 395 && mouseCoords.y >= 300 && mouseCoords.y <= 319) {
			readMediumXML();
			_map._easy = false;
			_map._medium = true;
			_map._hard = false;
			_gameState = GameState::PLAY;
		}
		if (mouseCoords.x >= 300 && mouseCoords.x <= 350 && mouseCoords.y >= 350 && mouseCoords.y <= 370) {
			readHardXML();
			_map._easy = false;
			_map._medium = false;
			_map._hard = true;
			_gameState = GameState::PLAY;
		}
	}
}


void Game::executePlayerCommands() {
	controlTime();
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
		_gameState = GameState::MENU;
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

void Game::chooseRanking() {
	
	if (_map.snake.getLive() == 2 && writeRanking1 == false) {
		result1 = _map._finalScore;
		//fileBusinessEndGame();
		//std::cout << "SSSCOORE 1 " << _map._finalScore << endl;
		writeRanking1 = true;
	}
	if (_map.snake.getLive() == 1 && writeRanking2 == false) {
		result2 = _map._finalScore;
		//fileBusinessEndGame();
		writeRanking2 = true;
	}
	if (_map.snake.getLive() == 0 && writeRakning3 == false) {
		result3 = _map._finalScore;
		//fileBusinessEndGame();
		writeRakning3 = true;
	}
}

void Game::renderGame() {
	
	
	//Clear the screen
	_graphic.clearWindow();
	//Draw the screen's content based on the game state
	if (_gameState == GameState::MENU) {
		drawMenu();
	}
	if (_gameState == GameState::RANKING) {
		drawRanking();
	}

	if (_gameState == GameState::GAMEMENU) {
		drawGameMenu();
	}
	
	if (_gameState == GameState::PLAY) {
		if (pause == false) {
			gameOver();
			chooseRanking();
			

			if (_map.checkApple(_map.apple.getXApplePosition(), _map.apple.getYApplePosition(), _map.snake.getXPosition(), _map.snake.getYPosition()) == true) {
				_map.snake.changeSpeed(_map.eatApple(_map.snake.getSpeed()));
			}
			
			if (snakeTimer > _map.snake.getSpeed() * 1000) {
				snakeBegin = clock()*CLK_TCK;
				std::cout << "HOLA" << endl;
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
	if (writeName == true) {
		activa = true;
		_graphic.drawText("Please, write your name on console", BLUE, WHITE, 150, 210);
	}
	_graphic.drawText(" ¡¡SNAKE!!", RED, WHITE, 280, 20);
	_graphic.drawText("PLAY", BLACK, WHITE, 300, 250);
	_graphic.drawText("RANKING", BLACK, WHITE, 300, 300);
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


void Game::createRankingFile(char filename[100])
{
	Score s;
	int sizeScore = sizeof(Score);
	ofstream rankingsFile;

	//Create the file with a random population
	rankingsFile.open(filename, std::ios::out | std::ios::trunc | std::ios::binary);

	if (!rankingsFile.is_open()) {
		throw std::exception("[CreateAPopulationFile] System was not able to open the file");
	}
	for (int id = 0; id <= 13; id++) { //We print 10 Scores
		rankingsFile.write((char *)(&s), sizeScore);
	}
	rankingsFile.close();
}

void Game::setNameFile() {

	cout << "\n\nInsert name please: " << endl;
	cin >> playerName;
}
string Game::getNameFile() {
	return playerName;
}
void Game::fileBusinessEndGame()
{
	
	//int score = _map.getScore();
	int score;
	if ((result1 >= result2) && (result1 >= result2))
		score = result1;
	else if ((result2 >= result1) && (result2 >= result3))
		score = result2;
	else if ((result3 >= result1) && (result3 >= result2))
		score = result3;
	
	cout << "SCORE: " << score << endl;
	char filename[100] = "rankings.bin";

	std::ifstream inputRankings;
	inputRankings.open(filename, std::ios::in | std::ios::binary);

	if (!inputRankings.is_open())
	{
		//create one
		createRankingFile(filename);
		cout << "There wasn't a ranking file, now there is" << endl;
	}

	//NOW THERE IS A FILE WITH 10 SCORES FOR SURE, IF IT'S THE FIRST GAME PLAYED, THEN IT'S FULL OF 0s


	Score s;
	int sizeScore = sizeof(Score);

	//See how long the file is
	std::streampos fileSize;
	inputRankings.seekg(0, std::ios::end);
	fileSize = inputRankings.tellg();
	inputRankings.seekg(0, std::ios::beg);


	//Create array where you store the scores -
	//Score scores[13];

	//Read content
	Score playerScore;
	int numElements = fileSize / sizeScore; //it's supposed to be 10
	for (int i = 0; i <= 12; i++) {
		inputRankings.read((char *)(&s), sizeScore);
		std::cout << s.getName() << s.getScore() << std::endl;
		scores[i] = s;
	}
	inputRankings.close();

	playerScore.setName(getNameFile());
	playerScore.setScore(score);

	scores[13] = playerScore;


	//SORT THE NUMBERS
	int scoresToQuickSort[13];
	for (int i = 0; i <= 12; i++)
	{
		scoresToQuickSort[i] = scores[i].getScore();
	}

	quickSort(scoresToQuickSort, 0, 12);

	for (int i = 0; i <= 12; i++)
	{
		cout << scoresToQuickSort[i] << " " << scores[i].getScore() << endl;
	}

	//sort the original array

	//This will help us protect the scores that are well positioned

	bool isScoreWhereItShouldBe[13];

	for (int i = 0; i < 10; i++)
	{
		for (int i = 0; i <= 12; i++)
		{
			isScoreWhereItShouldBe[i] = false;
		}

		for (int i = 0; i <= 12; i++)
		{
			for (int y = 0; y <= 12; y++)
			{
				if (isScoreWhereItShouldBe[y] == false)
				{
					if (scoresToQuickSort[i] == scores[y].getScore())
					{
						Score temp = scores[i];
						scores[i] = scores[y];
						scores[y] = temp;
						isScoreWhereItShouldBe[y] = true;
						break;
					}
				}
			}
		}
	}


	quickSortScore(scores, 0, 13);

	//lets see if the scores array is correctly ordered:

	for (int i = 0; i <= 12; i++)
	{
		cout << scoresToQuickSort[i] << " " << scores[i].getScore() << endl;
	}


	//NOW LETS UPDATE THE FILE!

	std::ofstream outputStream;
	outputStream.open(filename, std::ios::out | std::ios::trunc | std::ios::binary);

	if (!outputStream.is_open()) {
		throw std::exception("[outputStream] System was not able to open the file");
	}
	for (int id = 0; id <= 12; id++) {
		s = scores[id];
		outputStream.write((char *)(&s), sizeScore);
	}
	outputStream.close();
}

void Game::quickSortScore(Score arr[], int left, int right) {
	int i = left, j = right;
	Score tmp;
	Score pivot = arr[(left + right) / 2];

	//partition
	while (i <= j) {
		while (arr[i].getScore() > pivot.getScore())
			i++;
		while (arr[j].getScore() < pivot.getScore())
			j--;
		if (i <= j) {
			tmp = arr[i];
			arr[i] = arr[j];
			arr[j] = tmp;
			i++;
			j--;
		}
	};
	//recursion
	if (left < j)
		quickSortScore(arr, left, j);
	if (i < right)
		quickSortScore(arr, i, right);
}
void Game::quickSort(int arr[], int left, int right) {
	int i = left, j = right;
	int tmp;
	int pivot = arr[(left + right) / 2];

	// partition /
	while (i <= j) {
		while (arr[i] > pivot)
			i++;
		while (arr[j] < pivot)
			j--;
		if (i <= j) {
			tmp = arr[i];
			arr[i] = arr[j];
			arr[j] = tmp;
			i++;
			j--;
		}
	};

	// recursion /
	if (left < j)
		quickSort(arr, left, j);
	if (i < right)
		quickSort(arr, i, right);
}


void Game::drawRanking() {
	char filename[100] = "rankings.bin";

	std::ifstream inputRankings;
	inputRankings.open(filename, std::ios::in | std::ios::binary);

	Score s;
	int sizeScore = sizeof(Score);
	//See how long the file is
	std::streampos fileSize;
	inputRankings.seekg(0, std::ios::end);
	fileSize = inputRankings.tellg();
	inputRankings.seekg(0, std::ios::beg);

	//Read content

	int numElements = fileSize / sizeScore; //it's supposed to be 10
	for (int i = 0; i <= 10; i++) {
		inputRankings.read((char *)(&s), sizeScore);
		//std::cout << s.getName() << s.getScore() << std::endl;
		scores[i] = s;
	}
	inputRankings.close();
	int heightIncrease = 0; //eachscore has to be rendered at a different height, so we increment this value

							//PRINT TOP 10 SCORES
	for (int i = 0; i <= 9; i++)
	{
		_graphic.drawText(scores[i].getName(), BLACK, WHITE, _screenWidth / 4, _screenHeight / 8 + heightIncrease);
		_graphic.drawText(std::to_string(scores[i].getScore()), BLACK, WHITE, _screenWidth / 4 + 300, _screenHeight / 8 + heightIncrease);

		heightIncrease += 40;
	}
	
	_graphic.drawText("Press ESC to exit", BLUE, WHITE, 700 / 2 - 700 / 10, 700 / 2 + 700 / 4);
	if (_graphic.isKeyDown(SDLK_ESCAPE)) {

		_gameState = GameState::EXIT;
	}
}

void Game::readEasyXML() {
	
	
		xml_document<> doc;
		xml_node<> * root_node;
		// Read the xml file into a vector
		ifstream theFile("easyXML.xml");
		vector<char> buffer((istreambuf_iterator<char>(theFile)), istreambuf_iterator<char>());
		buffer.push_back('\0');
		// Parse the buffer using the xml file parsing library into doc 
		doc.parse<0>(&buffer[0]);
		// Find our root node
		root_node = doc.first_node("LevelOptions");

		
		for (xml_node<> * brewery_node = root_node->first_node("Level1"); brewery_node; brewery_node = brewery_node->next_sibling())
		{
			auto speedA = brewery_node->first_attribute("Speed")->value();
			double speedB = atof(speedA);
			cout << speedB << endl;
			_map.snake.changeSpeed(speedB);
			auto levelA = brewery_node->first_attribute("Level")->value();
			int levelB = atof(levelA);
			_map.setLevel(levelB);
			auto timeA = brewery_node->first_attribute("Time")->value();
			int timeB = atof(timeA);
			_map.setTime(timeB);
			
		}
	
}

void Game::readMediumXML() {
	
	
		xml_document<> doc;
		xml_node<> * root_node;
		// Read the xml file into a vector
		ifstream theFile("mediumXML.xml");
		vector<char> buffer((istreambuf_iterator<char>(theFile)), istreambuf_iterator<char>());
		buffer.push_back('\0');
		// Parse the buffer using the xml file parsing library into doc 
		doc.parse<0>(&buffer[0]);
		// Find our root node
		root_node = doc.first_node("LevelOptions");

		
		for (xml_node<> * brewery_node = root_node->first_node("Level1"); brewery_node; brewery_node = brewery_node->next_sibling())
		{
			auto speedA = brewery_node->first_attribute("Speed")->value();
			double speedB = atof(speedA);
			cout << speedB << endl;
			_map.snake.changeSpeed(speedB);
			auto levelA = brewery_node->first_attribute("Level")->value();
			int levelB = atof(levelA);
			_map.setLevel(levelB);
			auto timeA = brewery_node->first_attribute("Time")->value();
			int timeB = atof(timeA);
			_map.setTime(timeB);
			
		}
	
}

void Game::readHardXML() {


	xml_document<> doc;
	xml_node<> * root_node;
	// Read the xml file into a vector
	ifstream theFile("hardXML.xml");
	vector<char> buffer((istreambuf_iterator<char>(theFile)), istreambuf_iterator<char>());
	buffer.push_back('\0');
	// Parse the buffer using the xml file parsing library into doc 
	doc.parse<0>(&buffer[0]);
	// Find our root node
	root_node = doc.first_node("LevelOptions");


	for (xml_node<> * brewery_node = root_node->first_node("Level1"); brewery_node; brewery_node = brewery_node->next_sibling())
	{
		auto speedA = brewery_node->first_attribute("Speed")->value();
		double speedB = atof(speedA);
		cout << speedB << endl;
		_map.snake.changeSpeed(speedB);
		auto levelA = brewery_node->first_attribute("Level")->value();
		int levelB = atof(levelA);
		_map.setLevel(levelB);
		auto timeA = brewery_node->first_attribute("Time")->value();
		int timeB = atof(timeA);
		_map.setTime(timeB);

	}

}