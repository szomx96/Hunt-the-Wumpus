#include "stdafx.h"
#include "Chamber.h"


Chamber::Chamber()
{
}

Chamber::Chamber(int number)
{
	this->number = number;
	this->catapult = 0;
	this->hole = 0;
	this->player = 0;
	this->wumpus = 0;
	this->arrow = 0;

	for (int i = 0; i < 3; i++) {

		this->neighbours[i] = nullptr;	

	}

}


Chamber::~Chamber()
{
}
