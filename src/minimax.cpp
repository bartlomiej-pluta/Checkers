#include "../inc/minimax.hh"


int MiniMax::evaluate(Board& board, const Color& color)
{
	// Wycena
	int value = 0, pawn_value;

	// Wskaźnik na aktualnie oceniany pionek
	Pawn* ptr = NULL;


	// Przeglądamy całą planszę
	for(int x = 0; x<TILES_COUNT; ++x)
		for(int y = 0; y<TILES_COUNT; ++y)
		{
			// Jeżeli pionek na tym polu istnieje
			ptr = board.getPawn(Vector(x, y));
			if(ptr)
			{
				// Jeżeli pionek jest damką:
				if(ptr->isQueen()) pawn_value = 10;
				else pawn_value = 1;

				/*** SPRAWDZAMY MOŻLIWE BICIA ***/
				if(board.isPossibleBeating(Vector(x, y))) pawn_value *= 5;

				/*** ZASADA TRZECH OBSZARÓW ***/
				{
					// Jeżeli pionek należy do obszaru III (środkowego) -- waga 1
					if(((ptr->getPosition().x >= 3) && (ptr->getPosition().y >= 3)) &&
							((ptr->getPosition().x < (TILES_COUNT-3)) && (ptr->getPosition().y < (TILES_COUNT-3))))
						pawn_value *= 1; // więc nie ruszamy

					// Jeżeli pionek należy do obszaru II -- waga 2
					else if(((ptr->getPosition().x >= 2) && (ptr->getPosition().y >= 2)) &&
							((ptr->getPosition().x < (TILES_COUNT-2)) && (ptr->getPosition().y < (TILES_COUNT-2))))
						pawn_value *= 2;

					// Jeżeli pionek należy do obszaru I (skrajnego) -- waga 3
					else
						pawn_value *= 3;

				}

				// Jeżeli NIE jest to pionek należący do gracza zdefiniowanego kolorem color
				// przemnażamy przez -1
				if(ptr->getColor() != color) pawn_value *= -1;

				// Dodajemy pawn_value do wyceny
				value += pawn_value;


			}
		}

	// TODO wykrywanie bicia w heurystyce

	// Zwracamy wycenę
	return value;
}

Color MiniMax::getColorFromDepth(int depth)
{
	// Dla parzystych głębokości ruch należy do AI
	if(depth%2) return AI_COLOR;

	// Dla nieparzystych -- do gracza
	else
	{
		if(AI_COLOR == CL_WHITE) return CL_BLACK;
		else return CL_WHITE;
	}
}

int MiniMax::alphabeta(Board board, int depth, int alpha, int beta, Movement& best_movement)
{
	// Kolor aktualnego gracza
	Color color = getColorFromDepth(depth);

	// Jeżeli jest to liść lub korzeń
	if((depth == DEPTH_MAX) || (depth == 0)) return evaluate(board, color);

	// Jeżeli jest teraz ruch przeciwnika
	if(color != AI_COLOR)
	{
		// Dla każdego potomka
		for(auto& m: board.getPossibleGlobalMovements(color))
		{
			// Tworzymy nowy stan gry
			Board new_board(board);

			// Wykonujemy ruch
			new_board.movePawn(m);

			// Pobieramy wartość MIN (czyli gracz minimalizuje zysk AI)
			beta = std::min(beta, alphabeta(new_board, depth+1, alpha, beta, best_movement));

			// Jeżeli alfa >= beta odcinamy gałąź alfa
			if(alpha >= beta) break;
		}

		// Zwracamy wartość najlepszego ruchu
		return beta;
	}

	// Jeśli jest teraz ruch AI
	else
	{
		// Dla każdego potomka
		for(auto& m: board.getPossibleGlobalMovements(color))
		{
			// Tworzymy nowy stan gry
			Board new_board(board);

			// Wykonujemy ruch
			new_board.movePawn(m);

			// Pobieramy wartość stanu gry dla potomka
			int temp = alphabeta(new_board, depth+1, alpha, beta, best_movement);

			// Liczymy MAX (czyli AI maksymalizuje własny zysk)
			// oraz jednocześnie warunek najlepszego ruchu
			if(temp > alpha)
			{
				// Jeśli temp > alpha, przypisujemy alpha a= temp (z definicji MAX(a, b))
				alpha = temp;

				// Na poziomie rekurencji = 1 zwracamy w referencji
				// ruch, za pomocą którego doszliśmy do najlepszego rozwiązania według strategii minimax
				if(depth==1) best_movement = m;
			}

			// Jeżeli alfa >= beta odcinamy gałąź beta
			if(alpha >= beta) break;

		}

		// Zwracamy wartość najlepszego ruchu
		return alpha;
	}
}

Movement MiniMax::getBestMovement(Board board)
{
	// Tworzymy bufor na ruch
	Movement best_movement;

	// Pobieramy algorytmem minimax z cięciem alfa-beta najlepszy ruch
	alphabeta(board, 1, -INF, INF, best_movement);

	// Zwracamy najlepszy ruch
	return best_movement;
}

