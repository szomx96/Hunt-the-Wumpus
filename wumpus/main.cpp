// wumpus3.cpp: Okre�la punkt wej�cia dla aplikacji konsoli.
//

#include "stdafx.h"
#include "Chamber.h"
#include "Cave.h"
#include <iostream>
#include <cstdlib>
#include <ctime>


int main()
{
	srand(time(NULL));

	Cave *c1 = new Cave();

	c1->play();

	delete c1;
	

    return 0;
}

