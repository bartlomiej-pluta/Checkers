#include <iostream>
#include <SFML/Window.hpp>

#include "../inc/def.hh"
#include "../inc/misc.hh"
#include "../inc/object.hh"
#include "../inc/pawn.hh"
#include "../inc/board.hh"
#include "../inc/game.hh"
#include "../inc/minimax.hh"


// Punkt startowy programu
int main(int argc, char *argv[])
{
	// Kolor gracza
	Color color;

	// Poziom AI
	int ai;

	// Obsługa błędów i wartości domyślne
	if(argc != 3)
	{
		std::cout << "Użycie: checkers COLOR AI\n\tCOLOR - kolor gracza\n\tAI - poziom AI" << std::endl;
		color = CL_WHITE;
		ai = 6;
	}
	else
	{
		// Obsługa wejścia
		// Konwersja std::string na Color
		color = (std::string(argv[1]) == "black")?CL_BLACK:CL_WHITE;

		// Konwersja std::string na int
		std::stringstream ai_ss; ai_ss << argv[2]; ai_ss >> ai;

	}

	// Zabezpieczenie przed zbyt małym lub dużym poziomem AI
	if(ai < 2 || ai > 8)
	{
		std::cout << "Poziom AI powinien być z przedziału [2, 8]." << std::endl;
		return 1;
	}

	// Informacja o grze
	std::cout << "Grasz jako " << ((color==CL_WHITE)?"białe":"czarne") << " z poziomem AI = " << ai << std::endl;

	// Start gry
	Game game(color, ai);

	return 0;
}
