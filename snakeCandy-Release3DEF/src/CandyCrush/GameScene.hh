/******************************************************************
* Copyright (C) 2017 Grupo18                                     *
* This can not be copied, modified and/or distributed without    *
* express permission of the copyright owner.                     *
******************************************************************/

#pragma once
#include "Grid.hh"
#include "Scene.hh"
#include <vector>

// GameScene class with the main gameplay mode
class GameScene : public Scene {
public:
	explicit GameScene();
	~GameScene() override;
	void OnEntry(void) override;
	void OnExit(void) override;
	void Update(void) override;
	void Draw(void) override;
	void eatApple();
	void snakeDeath();//muerte snake
	void resetSnakeCrono();
	

private:
	Sprite m_grid; //cabeza snake
	Sprite m_background; //fondo game
	Sprite apple; //manzana
	Sprite *bordeSuperior;//limites escenario creado con sprite obstáculo
	Sprite *bordeInferior;
	Sprite *bordeIzquierdo;
	Sprite *bordeDerecho;

	Sprite tail;//cola snake
	Sprite body;//cuerpo snake
	

		//time:
	float levelTime = 500; //Tiempo en segundos del nivel
	float timer = 0; //calcula el tiempo que ha transcurrido desde que se ha iniciado el game
	float crono = 0; // se le resta al tiempo del nivel el valor de timer para dar el valor del crono
	float snakeTimer;
	float snakeCrono;
	float snakeSpeed = 0.5; //tiempo que transcurre entre movimiento y movimiento (puesto en 0.5segs y cada manzana disminuye ese tiempo en 0.01)
	int snakeSize = 0;
	int minutes = 0; //Conversion en minutos
	int seconds = 0; //Conversion en segundos

	int mapGrid[40][25];


	bool pause = false; //pausa de la partida

	struct position {
		int x = 3;
		int y = 3;
	};

	struct Snake {
		Sprite body = { { 60, 60, 20,20 }, ObjectID::CANDY_YELLOW };//Sprite body
		int x = 0;
		int y = 0;
	};

	position snake;
	position applePos;

	Snake tmpsnake;
	std::vector<Snake> snakes;

	int m_score{ 0 };
	bool up = false, down = false, left = false, right = false;
};