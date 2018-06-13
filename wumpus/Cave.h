#pragma once
#include "Chamber.h"
#include <vector>
#include <string>

#define CATAPULTES 5
#define HOLES 3
#define ARROWS 5


class Cave
{

private:
	
	std::vector<Chamber*> vchambers;
	std::vector<Chamber*> saved;
	int arrows;

public:

	Cave();
	void play();
	void debug();
	void connect_all();
	void set_map();
	void set_catapultes(int number);
	void set_holes(int number);
	void set_wumpus();
	void set_player();
	void move(int number);
	int where_am_i();
	void show_position();
	void check_dangers();
	bool is_it_over();
	void shoot_or_move();
	void where_can_i_shoot();
	void shoot(int n1, int n2, int n3);
	void pick_up_arrows();
	void move_wumpus();
	int wumpus_place();

	int get_arrows();
	void set_arrows(int i);

	void save();
	void load();
	void jump();
	~Cave();
};