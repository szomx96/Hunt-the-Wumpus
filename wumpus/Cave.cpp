#include "stdafx.h"
#include "Cave.h"
#include <iostream>


Cave::Cave()
{
	for (int i = 0; i < 20; i++) {
		Chamber * ch = new Chamber(i);
		this->vchambers.push_back(ch);
	}

}

void Cave::play()
{
	this->connect_all();
	this->set_map();
	this->set_arrows(ARROWS);
	this->save();
	
	while (this->is_it_over() != 1) {

		this->pick_up_arrows();
		this->show_position();
		this->check_dangers();
		this->shoot_or_move();
		
	}
	
	return;

}

void Cave::debug()
{
	
	for (auto i = this->vchambers.begin(); i != this->vchambers.end(); i++) {
		std::cout << (*i)->number << " k:" << (*i)->catapult << " dz:" << (*i)->hole << " w:" << (*i)->wumpus << " gr:" << (*i)->player <<" arr:"<<(*i)->arrow<< " ";
		std::cout << (*i)->neighbours[0]->number << " " << (*i)->neighbours[1]->number << " " << (*i)->neighbours[2]->number << "\n";
	}

}

void Cave::connect_all()
{
	for (auto i = this->vchambers.begin(); i != this->vchambers.end(); i++) {
	
		int numb = (*i)->number;

		(*i)->neighbours[0] = vchambers[19 - numb];

		if (numb % 4 == 0) {
			(*i)->neighbours[1] = vchambers[(numb + 2) % 20];
			if (numb - 2 >= 0) {
				(*i)->neighbours[2] = vchambers[(numb - 2) % 20];
			}
			else {
				(*i)->neighbours[2] = vchambers[20 + (numb - 2)];
			}
		}
		else if (numb % 4 == 1) {
			if (numb - 4 >= 0) {
				(*i)->neighbours[1] = vchambers[(numb - 4) % 20];
			}
			else {
				(*i)->neighbours[1] = vchambers[20 + (numb - 4)];
			}
			(*i)->neighbours[2] = vchambers[(numb + 4) % 20];
		}
		else if (numb % 4 == 2) {
			if (numb - 2 >= 0) {
				(*i)->neighbours[1] = vchambers[(numb - 2) % 20];
			}
			else {
				(*i)->neighbours[1] = vchambers[20 + (numb - 2)];
			}
			(*i)->neighbours[2] = vchambers[(numb + 2) % 20];
		}
		else if (numb % 4 == 3) {
			(*i)->neighbours[1] = vchambers[(numb + 4) % 20];

			if (numb - 4 >= 0) {
				(*i)->neighbours[2] = vchambers[(numb - 4) % 20];
			}
			else {
				(*i)->neighbours[2] = vchambers[20 + (numb - 4)];
			}
		}

	}
}

void Cave::set_map()
{
	this->set_catapultes(CATAPULTES);
	this->set_holes(HOLES);
	this->set_player();
	this->set_wumpus();
}

void Cave::set_catapultes(int number)
{
	int a = rand() % 20;

	for (int i = 0; i < number; i++) {

		while (this->vchambers[a]->catapult == 1 || this->vchambers[a]->hole == 1 || this->vchambers[a]->player == 1) {
			a = rand() % 20;
		}
		this->vchambers[a]->catapult = 1;
	}
	
}

void Cave::set_holes(int number)
{
	int a = rand() % 20;

	for (int i = 0; i < number; i++) {

		while (this->vchambers[a]->catapult == 1 || this->vchambers[a]->hole == 1 || this->vchambers[a]->player == 1) {
			a = rand() % 20;
		}
		this->vchambers[a]->hole = 1;
	}

}

void Cave::set_wumpus()
{
	int a = rand() % 20;

	while (this->vchambers[a]->player == 1) {
		a = rand() % 20;
	}
	this->vchambers[a]->wumpus = 1;

}

void Cave::set_player()
{
	int a = rand() % 20;

	while (this->vchambers[a]->catapult == 1 || this->vchambers[a]->hole == 1 || this->vchambers[a]->wumpus == 1) {
		a = rand() % 20;
	}
	this->vchambers[a]->player = 1;
	

}

void Cave::move(int number)
{
	int here = this->where_am_i();

	if (this->vchambers[here]->neighbours[0]->number != number && this->vchambers[here]->neighbours[1]->number != number && this->vchambers[here]->neighbours[2]->number != number) {
		std::cout << "\nNie mozesz tam isc\n";
	}
	else {
		this->vchambers[here]->player = 0;
		this->vchambers[number]->player = 1;
	}

}

int Cave::where_am_i()
{
	for (auto i = vchambers.begin(); i != vchambers.end(); i++) {
		if ((*i)->player == 1) {
			return (*i)->number;
		}
		
	}
	return -1;

}

void Cave::show_position()
{
	std::cout << "\nJestes w komorze numer " << this->where_am_i() << "\n";
	std::cout << "Mozesz isc do komor numer " << this->vchambers[this->where_am_i()]->neighbours[0]->number << ", " << this->vchambers[this->where_am_i()]->neighbours[1]->number<<", "<< this->vchambers[this->where_am_i()]->neighbours[2]->number << "\n";

}

void Cave::check_dangers()
{
	int where = this->where_am_i();

	if (vchambers[where]->neighbours[0]->catapult == 1 || vchambers[where]->neighbours[1]->catapult == 1 || vchambers[where]->neighbours[2]->catapult == 1) {
		std::cout << "Slysze katapulte!\n";
	}
	if (vchambers[where]->neighbours[0]->hole == 1 || vchambers[where]->neighbours[1]->hole == 1 || vchambers[where]->neighbours[2]->hole == 1) {
		std::cout << "Czuje przeciag!\n";
	}
	if (vchambers[where]->neighbours[0]->wumpus == 1 || vchambers[where]->neighbours[1]->wumpus == 1 || vchambers[where]->neighbours[2]->wumpus == 1) {
		std::cout << "Nieopodal grasuje WUMPUS!\n";
	}

}

bool Cave::is_it_over()
{
	int here = this->where_am_i();
	int there = this->wumpus_place();

	if (this->vchambers[here]->player == 1 && this->vchambers[here]->wumpus == 1) {
		
		std::cout << "\nZostales zjedzony przez WUMPUSA. Koniec gry.\n";
		return 1;
	
	}else if(this->vchambers[here]->player == 1 && this->vchambers[here]->hole == 1) {

		std::cout << "\nWpadles w dziure. Koniec gry.\n";
		return 1;
	}
	else if(this->vchambers[here]->catapult == 1) {
		this->jump();
		return 0;
	}
	else if (this->vchambers[there]->arrow == 1) {
		std::cout << "\nPOKONALES WUMPUSA - WYGRANA!\n";
		return 1;
	}
	else {
		return 0;
	}

}

void Cave::shoot_or_move()
{
	std::cout << "\nAby isc wpisz m[nr]\nAby strzelic wpisz s[nr1]-[nr2]-[nr3]\nAby wyswietlic mozliwosci strzalu wpisz ?\n";
	std::cout << "Pozostalo strzal: " << this->get_arrows() << "\n";
	
	std::string select;

	std::cin >> select;


	if (select[0] == 'm') {
		std::string substr = select.substr(1, select.length() - 1);
		int i = atoi(substr.c_str());
		this->move(i);
	
	}
	else if (select[0] == 's') {
		
		std::size_t ignore = select.find("-");
		std::size_t ignore2 = select.find("-", ignore + 1);

		std::string substr1 = select.substr(1, ignore-1);
		std::string substr2 = select.substr(ignore+1, ignore2-ignore-1);
		std::string substr3 = select.substr(ignore2+1, select.length()-1);

		int s0 = atoi(substr1.c_str());
		int s1 = atoi(substr2.c_str());
		int s2 = atoi(substr3.c_str());
		
		this->shoot(s0, s1, s2);

	}
	else if (select == "?") {
		
		this->where_can_i_shoot();

	}else {
	
		std::cout << "\nNie ma takiej komendy\n";

	}


}

void Cave::where_can_i_shoot()
{
	int here = this->where_am_i();

	std::cout << "Mozliwosci strzalu:\n";

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			for (int k = 0; k < 3; k++) {
				std::cout << this->vchambers[here]->neighbours[i]->number << "-" << this->vchambers[here]->neighbours[i]->neighbours[j]->number << "-" << this->vchambers[here]->neighbours[i]->neighbours[j]->neighbours[k]->number << "\n";
			}
		}
	}


}

void Cave::shoot(int n1, int n2, int n3)
{
	int arrows = this->get_arrows();

	
	std::cout << "\nObudziles wumpusa!\n";
	this->move_wumpus();
	int player = where_am_i();

	if (arrows > 0) {

		if ((this->vchambers[player]->neighbours[0]->number != n1 && this->vchambers[player]->neighbours[1]->number != n1 && this->vchambers[player]->neighbours[2]->number != n1) || (this->vchambers[n1]->neighbours[0]->number != n2 && this->vchambers[n1]->neighbours[1]->number != n2 && this->vchambers[n1]->neighbours[2]->number != n2) || (this->vchambers[n2]->neighbours[0]->number != n3 && this->vchambers[n2]->neighbours[1]->number != n3 && this->vchambers[n2]->neighbours[2]->number != n3)) {
			std::cout << "Trafiles w sciane.\n";
		}
		else {
			this->vchambers[n1]->arrow = 1;
			this->vchambers[n2]->arrow = 1;
			this->vchambers[n3]->arrow = 1;
		}

		arrows -= 1;
		this->set_arrows(arrows);

	}
	else {
	
		std::cout << "\nNie masz juz strzal :(\n";

	}
	


}

void Cave::pick_up_arrows()
{
	for (auto i = vchambers.begin(); i != vchambers.end(); i++) {
		(*i)->arrow = 0;
	}

}

void Cave::move_wumpus()
{
	int there = this->wumpus_place();
	int i = rand() % 3;

	this->vchambers[there]->wumpus = 0;
	this->vchambers[there]->neighbours[i]->wumpus = 1;


}

int Cave::wumpus_place()
{
	for (auto i = vchambers.begin(); i != vchambers.end(); i++) {
		if ((*i)->wumpus == 1) {
			return (*i)->number;
		}

	}
	return -1;
}

int Cave::get_arrows()
{
	return this->arrows;
}

void Cave::set_arrows(int i)
{
	this->arrows = i;
}

void Cave::save()
{
	for (auto i = vchambers.begin(); i != vchambers.end(); i++) {

		saved.push_back(*i);
	}

}

void Cave::load()
{
	vchambers.clear();

	for (auto i = saved.begin(); i != saved.end(); i++) {

		vchambers.push_back(*i);
	}

}

void Cave::jump()
{
	int here =  this->where_am_i();
	this->vchambers[here]->player = 0;
	this->set_player();

	int new_place = this->where_am_i();
	std::cout << "\nZostales katapultowany do komory numer " << this->vchambers[new_place]->number << "\n";
}


Cave::~Cave()
{
	for (int i = 0; i < vchambers.size(); i++)
		delete vchambers[i];
	vchambers.clear();

	for (int i = 0; i < saved.size(); i++)
		delete saved[i];
	saved.clear();

}
