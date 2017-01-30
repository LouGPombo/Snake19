#include "Cell.h"



Cell::Cell()
{
	_material = 0;
}

Cell::Cell(int material) {
	this->_material = material;
}

Cell::~Cell()
{

}

int Cell::getMaterial() {
	return _material;
}

void Cell::setMaterial(int newMaterial) {
	_material = newMaterial;
}