
#include "GUI.hh"
#include "System.hh"
#include "Logger.hh"
#include "MenuScene.h"
#include "GameScene.hh"
using namespace Logger;

#define CELL_WIDTH 80
#define CELL_HEIGHT 80

MenuScene::MenuScene(void) {
	m_background = { { 0, 0, W.GetWidth(), W.GetHeight() }, ObjectID::BG_00 };
}

MenuScene::~MenuScene(void) {
}

void MenuScene::OnEntry(void) {
}

void MenuScene::OnExit(void) {
}

void MenuScene::Update(void) {
	static MouseCoords mouseCoords(0, 0);
	if (IM.IsMouseDown<MOUSE_BUTTON_LEFT>()) {
		Println("===============");
		Println("mxp: ", mouseCoords);
		mouseCoords = IM.GetMouseCoords();
	}
	else if (IM.IsMouseUp<MOUSE_BUTTON_LEFT>()) {
		Println("mxn: ", IM.GetMouseCoords());
	}

	if (IM.IsMouseDown<MOUSE_BUTTON_LEFT>() && IM.GetMouseCoords().x > 456 && IM.GetMouseCoords().x < 567 && IM.GetMouseCoords().y > 268 && IM.GetMouseCoords().y < 344) {  //Apretar el boto de play
		SM.SetCurScene <GameScene>();
		mouseCoords = IM.GetMouseCoords();
	}

	if (IM.IsMouseDown<MOUSE_BUTTON_LEFT>() && IM.GetMouseCoords().x > 463 && IM.GetMouseCoords().x < 559 && IM.GetMouseCoords().y > 421 && IM.GetMouseCoords().y < 498) {  //Apretar el boto de exit
		IM.SetQuit();
		mouseCoords = IM.GetMouseCoords();
	}

	// Test InputManager key methods
	if (IM.IsKeyHold<'a'>()) Println("a hold");
	if (IM.IsKeyDown<'0'>()) Println("0 down");
	if (IM.IsKeyUp<KEY_BUTTON_DOWN>()) Println("down arrow up");

}

void MenuScene::Draw(void) {
	
	GUI::DrawTextShaded<FontID::FACTORY>("Snake",
	{ W.GetWidth() >> 1, int(W.GetHeight()*.1f), 1, 1 },
	{ 190, 0, 160 }, { 50, 200, 230 }); // Render score that will be different when updated
	GUI::DrawTextShaded<FontID::FACTORY>("Easy",
	{ W.GetWidth() >> 1, int(W.GetHeight()*.4f), 1, 1 },
	{ 190, 0, 160 }, { 50, 200, 230 }); // Render score that will be different when updated
	GUI::DrawTextShaded<FontID::FACTORY>("Medium",
	{ W.GetWidth() >> 1, int(W.GetHeight()*.4f), 1, 1 },
	{ 190, 0, 160 }, { 50, 200, 230 }); // Render score that will be different when updated
	GUI::DrawTextShaded<FontID::FACTORY>("Hard",
	{ W.GetWidth() >> 1, int(W.GetHeight()*.4f), 1, 1 },
	{ 190, 0, 160 }, { 50, 200, 230 }); // Render score that will be different when updated
	GUI::DrawTextShaded<FontID::FACTORY>("Exit",
	{ W.GetWidth() >> 1, int(W.GetHeight()*.6f), 1, 1 },
	{ 190, 0, 160 }, { 50, 200, 230 }); // Render score that will be different when updated
}
