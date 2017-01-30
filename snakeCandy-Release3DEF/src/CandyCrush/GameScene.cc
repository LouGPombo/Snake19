/******************************************************************
* Copyright (C) 2017 Grupo18                                     *
* This can not be copied, modified and/or distributed without    *
* express permission of the copyright owner.                     *
******************************************************************/
#include "GUI.hh"
#include "System.hh"
#include "Logger.hh"
#include "GameScene.hh"
#include <time.h>



using namespace Logger;

#define CELL_WIDTH 80
#define CELL_HEIGHT 80
#define GRID_HEIGHT 268 //definimos como constantes tamaño escenario
#define GRID_WIDTH 224


clock_t begin = clock()*CLK_TCK; //time
clock_t snakeBegin = clock()*CLK_TCK;

enum class MoveType { UP, LEFT, DOWN, RIGHT };

GameScene::GameScene(void) : m_grid() {
	m_grid = { { 10, 10, 20,20 }, ObjectID::CANDY_BLUE };//Sprite de la serpiente!								
	apple = { { 10, 10, 20, 20 }, ObjectID::CANDY_RED }; //sprite manzana
	tail = { { 40, 40, 20,20 }, ObjectID::CANDY_PURPLE };//Sprite tail
	body = { { 60, 60, 20,20 }, ObjectID::CANDY_YELLOW };//Sprite body
	m_background = { { 0, 0, W.GetWidth() - GRID_WIDTH, W.GetHeight() - GRID_HEIGHT }, ObjectID::BG_00 }; //Fondo azul //TODO cambiar el fondo .jpg por por sprites pintados 40x40
	bordeSuperior = new Sprite[(W.GetWidth() - GRID_WIDTH) / 20];//Sprite obstáculo que forman los límites escenario
	bordeInferior = new Sprite[(W.GetWidth() - GRID_WIDTH) / 20];
	bordeIzquierdo = new Sprite[(W.GetHeight() - GRID_HEIGHT) / 20];
	bordeDerecho = new Sprite[(W.GetHeight() - GRID_HEIGHT) / 20];
	for (int i = 0; i < (W.GetWidth() - GRID_WIDTH) / 20; i++)
	{
		bordeSuperior[i] = { { i * 20, 0, 20, 20 }, ObjectID::CANDY_GREEN };
		bordeInferior[i] = { { i * 20, W.GetHeight() - GRID_HEIGHT, 20, 20 }, ObjectID::CANDY_GREEN };
	}
	for (int i = 0; i <= (W.GetHeight() - GRID_HEIGHT) / 20; i++) {
		bordeIzquierdo[i] = { { 0, i * 20, 20, 20 }, ObjectID::CANDY_GREEN };
		bordeDerecho[i] = { { (W.GetWidth() - GRID_WIDTH) , i * 20, 20, 20 }, ObjectID::CANDY_GREEN };
	}
}

GameScene::~GameScene(void) {
}

void GameScene::OnEntry(void) {
	srand(time(NULL));//iniciamos random para la manzana
	applePos.x = (int)rand() % 39 + 1;
	applePos.y = (int)rand() % 24 + 1;
	std::cout << applePos.x << std::endl;
	std::cout << applePos.y << std::endl;
	apple.transform.x = applePos.x * 20; //Posición x random para la manzana
	apple.transform.y = applePos.y * 20; //Posición y random para la manzana
	mapGrid[applePos.x][applePos.y] = 2;
}

void GameScene::OnExit(void) {
}


void  GameScene::eatApple() {
	mapGrid[applePos.x][applePos.y] = 0;
	applePos.x = (int)rand() % 39 + 1;
	applePos.y = (int)rand() % 24 + 1;
	apple.transform.x = applePos.x * 20; //Posición x random para la manzana
	apple.transform.y = applePos.y * 20; //Posición y random para la manzana
	mapGrid[applePos.x][applePos.y] = 2;
	m_score += 100; //Añadimos puntuacion
	if (snakeSpeed >= 0.01) {
		snakeSpeed -= 0.01;
	}
	body.transform.x = snake.x + 20;//transform cambia la posición del cuerpo//TODO QUITAR SI NO RULA GOOD
	body.transform.y = snake.y + 20;
	snakeSize++;
	tmpsnake.x = snake.x;
	tmpsnake.y = snake.y;
	snakes.push_back(tmpsnake);
}

void GameScene::snakeDeath() {
	//Volvemos a poner a la serpiente en su posición inicial, reiniciamos la puntuación a 0. Desactivamos todas las direcciones.
	mapGrid[applePos.x][applePos.y] = 0;
	applePos.x = (int)rand() % 39 + 1;
	applePos.y = (int)rand() % 24 + 1;
	memset(mapGrid, 0, sizeof(mapGrid));
	snakes.clear();
	snakeSize = 0;
	apple.transform.x = applePos.x * 20; //Posición x random para la manzana
	apple.transform.y = applePos.y * 20; //Posición y random para la manzana
	mapGrid[applePos.x][applePos.y] = 2;
	snake.x = 3;
	snake.y = 3;
	m_score = 0; //reiniciamos!
	up = false;
	down = false;
	right = false;
	left = false;
	begin = clock()*CLK_TCK;
}

void GameScene::resetSnakeCrono() {
	snakeBegin = clock()*CLK_TCK;
}

void GameScene::Update(void) {

	//time:
	clock_t t(clock() * CLK_TCK);
	clock_t snakeEnd(clock() * CLK_TCK);
	snakeTimer = (snakeEnd - snakeBegin) / (1000);
	timer = (t - begin) / (1000 * 1000);
	crono = levelTime - (timer);
	minutes = (int)crono / 60;
	seconds = (int)crono % 60;



	if (snake.x < 1 || snake.y < 1 || snake.x >= 40 || snake.y >= 25 || mapGrid[snake.x][snake.y] == 4) {
		snakeDeath(); //muerte snake
	}

	if (IM.IsKeyDown<KEY_BUTTON_ESCAPE>()) {//pause game
		pause = !pause; //Invertimos el bool
	}


	if (!pause) {
		if (IM.IsKeyUp<KEY_BUTTON_DOWN>()) {
			if (up == false) {
				down = true;
				left = false;
				right = false;
			}
		};

		if (IM.IsKeyUp<KEY_BUTTON_UP>()) {
			if (down == false) {
				up = true;
				left = false;
				right = false;
			}
		};

		if (IM.IsKeyUp<KEY_BUTTON_LEFT>()) {
			if (right == false) {
				left = true;
				up = false;
				down = false;
			}
		};

		if (IM.IsKeyUp<KEY_BUTTON_RIGHT>()) {
			if (left == false) {
				right = true;
				up = false;
				down = false;
			}
		};

		m_grid.transform.x = snake.x * 20;//transform cambia la posición de la serpiente
		m_grid.transform.y = snake.y * 20;

		if (snakeTimer > snakeSpeed * 1000) {
			resetSnakeCrono();
			for (int i = 0; i < 40; i++) {
				for (int j = 0; j < 25; j++) {
					std::cout << mapGrid[j][i];
				}
				std::cout << std::endl;
			}
			if (snakeSize > 0) {
				for (int i = 0; i < snakes.size(); i++) {
					mapGrid[snakes[i].x][snakes[i].y] = 0;
				}
				for (int i = snakes.size() - 1; i != 0; i--) {
					snakes[i].body = body;
					snakes[i].x = snakes[i - 1].x;
					snakes[i].y = snakes[i - 1].y;
				}
				snakes.front().body = body;
				snakes.back().body = tail;
				snakes.front().x = snake.x;
				snakes.front().y = snake.y;
				for (int i = 0; i < snakes.size(); i++) {
					mapGrid[snakes[i].x][snakes[i].y] = 4;
				}
			}
			if (down == true && up == false) {
				snake.y++;
			}

			if (up == true && down == false) {
				snake.y--;
			}

			if (right == true && left == false) {
				snake.x++;
			}

			if (left == true && right == false) {
				snake.x--;
			}
			if (mapGrid[snake.x][snake.y] == 2) {  //Si el centro de la serpiente se situa entre los bordes de la manzana
				eatApple();
			}
		}
	}
}


void GameScene::Draw(void) {
	m_background.Draw(); // Render background
	m_grid.Draw();//Render head snake
	apple.Draw();//render manzana
				// tail.Draw();//render tail snake
				// body.Draw();//render body snake


	for (int i = 0; i < (W.GetWidth() - GRID_WIDTH) / 20; i++)//pintamos bordes
	{
		bordeSuperior[i].Draw();
		bordeInferior[i].Draw();
	}
	for (int i = 0; i <= (W.GetHeight() - GRID_HEIGHT) / 20; i++) {
		bordeIzquierdo[i].Draw();
		bordeDerecho[i].Draw();
	}

	for (int i = 0; i < snakes.size(); i++) {
		snakes[i].body.transform.x = snakes[i].x * 20;
		snakes[i].body.transform.y = snakes[i].y * 20;
		snakes[i].body.Draw();
	}


	GUI::DrawTextBlended<FontID::CANDY>("Score: " + std::to_string(m_score),
	{ W.GetWidth() >> 1, int(W.GetHeight()*.9f), 1, 1 },
	{ 115, 0, 180 }); // Render score that will be different when updated

	GUI::DrawTextBlended<FontID::CANDY>("Time: " + std::to_string(minutes) + ", " + std::to_string(seconds),//TODO situar abajo
	{ W.GetWidth() >> 1, int(W.GetHeight()*.8f), 1, 1 },
	{ 115, 0, 180 }); // Render score that will be different when update

}