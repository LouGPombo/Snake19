#pragma once
#include <iostream>
using namespace std;
#include <string>

class Score
{
	char _name[100];
	int _score;
public:
	Score();
	Score(char name[100], int score);
	~Score();
	int getScore();
	void setScore(int score);

	string getName();
	void setName(string name);
 
	float timer = 0; //calcula el tiempo que ha transcurrido desde que se ha iniciado el game

};

