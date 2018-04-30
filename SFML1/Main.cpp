#include <iostream>
#include "Game.h"

int main()
{
	try
	{
		Game game;
		game.run();
	}
	catch (std::exception& e)
	{
		std::cerr << "\nEXCEPTION: " << e.what() << std::endl;

		//Laisser le temps de lire la console
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cin.get();

		return 1;
	}
	return 0;
}