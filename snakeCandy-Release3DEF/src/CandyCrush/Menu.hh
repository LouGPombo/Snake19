/******************************************************************
* Copyright (C) 2017 Grupo18                                     *
* This can not be copied, modified and/or distributed without    *
* express permission of the copyright owner.                     *
******************************************************************/

#pragma once
#include "Grid.hh"
#include "Scene.hh"

// GameScene class with the main gameplay mode
class Menu : public Scene {
public:
	explicit Menu();
	~Menu() override;
	void OnEntry(void) override;
	void OnExit(void) override;
	void Update(void) override;
	void Draw(void) override;
private:
	Grid m_grid;
	Sprite m_background;
	Sprite menu;
	int m_score{ 0 };
};