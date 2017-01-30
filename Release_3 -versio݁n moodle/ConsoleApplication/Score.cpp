#include "Score.h"

Score::Score()
{
	_name[0] = 'X';
	for (int i = 1; i < 100; i++)
	{
		_name[i] = ' ';
	}
	_score = 0;
}

Score::Score(char name[100], int score) {
	name[100] = _name[100];
	score = _score;
}

Score::~Score()
{
}

int Score::getScore()
{
	return _score;
}

void Score::setScore(int Newscore)
{
	_score = Newscore;
}

std::string Score::getName()
{
	std::string str = std::string(_name);
	return str;
}

void Score::setName(std::string name)
{
	strcpy(_name, name.c_str());
}

