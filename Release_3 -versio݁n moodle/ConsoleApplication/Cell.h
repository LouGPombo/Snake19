#pragma once
class Cell
{
	/*Clase celda para rellenar las casillas con los materiales. (Se seleccionará más adelante una posición [x][y] desde map y se 
	le dará un int desde Cell*/
private:

	int _material;
public:
	Cell(); //Constructor
	Cell(int material); //Overload Constructor
//	Cell(Cell & cell1); //Copy Constructor
	~Cell(); //Destructor
	void setMaterial(int newMaterial);
	int getMaterial();
};