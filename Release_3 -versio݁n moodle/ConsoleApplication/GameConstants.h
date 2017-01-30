#pragma once

//Game general information
#define GAME_SPEED 0.1f
#define GAME_TEXTURES 4 //Max número de texturas
#define MAX_MONSTERS 10
#define MONSTER_REFRESH_FREQUENCY 1000

//Sprite information
#define SPRITE_SPEED 0.01f
#define SPRITE_DEFAULT_WIDTH 20
#define SPRITE_DEFAULT_HEIGHT 20
#define SPRITE_SNAKE 0
#define SPRITE_APPLE 1
#define SPRITE_GRID 2
#define SPRITE_OBSTACLE 3

//Color information
#define GAME_BASIC_COLORS 8
#define RED 0
#define GREEN 1
#define BLUE 2
#define BLACK 3
#define WHITE 4
#define MAX_ROW 35
#define MAX_COLUMN 20
enum class GameState { INIT, PLAY, EXIT, MENU, GAMEMENU };
enum movement {
	UP,
	DOWN,
	LEFT,
	RIGHT,
	NOMOVE
};