#pragma once
class Cell
{
	/*Clase celda para rellenar las casillas con los materiales. (Se seleccionar� m�s adelante una posici�n [x][y] desde map y se 
	le dar� un int desde Cell*/
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