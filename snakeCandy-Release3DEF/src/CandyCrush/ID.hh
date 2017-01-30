/******************************************************************
* Copyright (C) 2017 Grupo 18                                    *
* This can not be copied, modified and/or distributed without    *
* express permission of the copyright owner.                     *
******************************************************************/

#pragma once
#include <iostream>

// Enum ID used to identify each Game Object in the Game
enum class ObjectID : const int {
	CANDY_BLUE, CANDY_GREEN, CANDY_YELLOW, CANDY_RED, CANDY_PURPLE, CANDY_ORANGE, CANDY_MAX, CANDY_EMPTY, // Candies IDs
	CELL_EMPTY, // Cell IDs
	BG_00, BG_MENU  // Background IDs

};
inline std::ostream &operator<<(std::ostream &os, const ObjectID &id) { return os << int(id); };
inline std::istream &operator>>(std::istream &is, ObjectID &id) { return is >> reinterpret_cast<int&>(id); };

// Enum ID used to store each true type font for text rendering
enum class FontID : int {
	ARIAL,
	CANDY,
	FACTORY, 
	MAX 
};