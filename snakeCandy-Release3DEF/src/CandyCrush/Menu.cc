/******************************************************************
* Copyright (C) 2017 Grupo18                                     *
* This can not be copied, modified and/or distributed without    *
* express permission of the copyright owner.                     *
******************************************************************/

#include "GUI.hh"
#include "System.hh"
#include "Logger.hh"
#include "Menu.hh"
#include "GameScene.hh"

using namespace Logger;

Menu::Menu(void) : m_grid("lvl/testLvl.dat", 0, 0) {
	m_background = { { 0, 0, W.GetWidth(), W.GetHeight() }, ObjectID::BG_MENU }; //fondo menú
}

Menu::~Menu(void) {
}

void Menu::OnEntry(void) {
}

void Menu::OnExit(void) {
}

void Menu::Update(void) {
	static MouseCoords mouseCoords(0, 0);
	if (IM.IsMouseDown<MOUSE_BUTTON_LEFT>()) {
		Println("===============");
		Println("mxp: ", mouseCoords);
		mouseCoords = IM.GetMouseCoords();
	}
	else if (IM.IsMouseUp<MOUSE_BUTTON_LEFT>()) {
		Println("mxn: ", IM.GetMouseCoords());
		//m_grid.CheckMouseSwift(mouseCoords, IM.GetMouseCoords());
	}
	//m_grid.Update(m_score); // Update grid
							// Test InputManager key methods
	if (IM.IsKeyHold<'a'>()) { 
		//SM.AddScene<GameScene>;
		
		Println("a hold"); }
	if (IM.IsKeyDown<'0'>()) Println("0 down");
	if (IM.IsKeyUp<KEY_BUTTON_DOWN>()) Println("down arrow up");

	if (mouseCoords.x > 455 && mouseCoords.x < 569 && mouseCoords.y > 209 && mouseCoords.y <240) {
		SM.SetCurScene<GameScene>();
	}
	else if (mouseCoords.x > 429 && mouseCoords.x < 595 && mouseCoords.y > 363 && mouseCoords.y <396) {
		SM.SetCurScene<GameScene>();
	}

	else if (mouseCoords.x > 455 && mouseCoords.x < 567 && mouseCoords.y > 517 && mouseCoords.y <547) {
		SM.SetCurScene<GameScene>();
	}

	else if (mouseCoords.x > 461 && mouseCoords.x < 569 && mouseCoords.y > 670 && mouseCoords.y <703) {
		SM.SetCurScene<GameScene>();
	}
}

void Menu::Draw(void) {
	m_background.Draw(); // Render background
	//m_grid.Draw(); // Render grid
	GUI::DrawTextShaded<FontID::FACTORY>("Snake",
	{ W.GetWidth() >> 1, int(W.GetHeight()*.1f), 1, 1 },
	{ 190, 0, 160 }, { 50, 200, 230 }); // Render score that will be different when updated
	
	GUI::DrawTextBlended<FontID::CANDY>("EASY",
	{ W.GetWidth() >> 1, int(W.GetHeight()*.3f), 1, 1 },
	{ 115, 0, 180 });

	GUI::DrawTextBlended<FontID::CANDY>("MEDIUM",
	{ W.GetWidth() >> 1, int(W.GetHeight()*.5f), 1, 1 },
	{ 115, 0, 180 });

	GUI::DrawTextBlended<FontID::CANDY>("HARD",
	{ W.GetWidth() >> 1, int(W.GetHeight()*.7f), 1, 1 },
	{ 115, 0, 180 });
	
	GUI::DrawTextBlended<FontID::CANDY>("EXIT",
	{ W.GetWidth() >> 1, int(W.GetHeight()*.9f), 1, 1 },
	{ 29, 113, 53 });//color

}