#pragma once

class Chamber
{
public:
	int number;
	bool hole, catapult, wumpus, player, arrow;
	Chamber* neighbours[3];



	Chamber();
	Chamber(int number);
	~Chamber();
};


