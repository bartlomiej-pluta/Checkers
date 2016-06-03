#include "../inc/minimax.hh"

int MiniMax::evaluate(Board& board, const Color& color)
{
	// Wycena
	int value = 0, pawn_value = 0;

	// Wskaźnik na aktualnie oceniany pionek
	Pawn* ptr = NULL;

	// Ilość pionków gracza
	int player_pawns = 0;

	// Ilość pionków przeciwnika
	int opponent_pawns = 0;

	// Przeglądamy całą planszę
	for(int x = 0; x<TILES_COUNT; ++x)
		for(int y = 0; y<TILES_COUNT; ++y)
		{
			// Jeżeli pionek na tym polu istnieje
			ptr = board.getPawn(Vector(x, y));
			if(ptr)
			{
				// Zerujemy wartość tymczasową
				pawn_value = 0;

				/*** DAMKA / PIONEK ***/
				if(ptr->isQueen()) pawn_value += 50;
				else pawn_value += 1;

				/*** SPRAWDZAMY MOŻLIWE BICIA ***/
				if(board.isPossibleBeating(Vector(x, y))) pawn_value += 1000;

				///*** SPRAWDZAMY, CZY PIONEK MOŻE BYĆ ZBITY ***/
				//if(board.isEndangered(Vector(x, y))) pawn_value -= 10;

				/*** ZASADA TRZECH OBSZARÓW ***/
				{
					// Jeżeli pionek należy do obszaru III (środkowego) -- waga 1
					if(((ptr->getPosition().x >= 3) && (ptr->getPosition().y >= 3)) &&
							((ptr->getPosition().x < (TILES_COUNT-3)) && (ptr->getPosition().y < (TILES_COUNT-3))))
						pawn_value += 0; // więc nie ruszamy

					// Jeżeli pionek należy do obszaru II -- waga 2
					else if(((ptr->getPosition().x >= 2) && (ptr->getPosition().y >= 2)) &&
							((ptr->getPosition().x < (TILES_COUNT-2)) && (ptr->getPosition().y < (TILES_COUNT-2))))
						pawn_value += 100;

					// Jeżeli pionek należy do obszaru I (skrajnego) -- waga 3
					else
						pawn_value += 500;

				}

				// Jeżeli NIE jest to pionek należący do gracza zdefiniowanego kolorem color
				// przemnażamy przez -1
				// Do tego zliczamy ilość pionków
				if(ptr->getColor() != color) { pawn_value *= -1; ++opponent_pawns; }
				else ++player_pawns;

				// Dodajemy pawn_value do wyceny
				value += pawn_value;


			}
		}


	// Jeżeli nie ma już pionków przeciwnika na planszy, zwracamy INF (gdyż jest to wygrana)
	if(!opponent_pawns) return INF;

	// Jeżeli nie ma już pionków gracza na planszy, zwracamy -INF (przegrana)
	if(!player_pawns) return -INF;

	// Zwracamy wycenę
	return value;
}

int MiniMax::alphabeta(Board board, int depth, int alpha, int beta, const Color& player, Movement& best_movement)
{
	// Jeżeli jest to liść, zwróć wartość funkcji heurystycznej
	if(depth == DEPTH_MAX) return evaluate(board, player);

	// Jeżeli jest teraz ruch przeciwnika
	if(player != AI_COLOR)
	{
		// Dla każdego potomka
		for(auto& m: board.getPossibleGlobalMovements(player))
		{
			// Tworzymy nowy stan gry
			Board new_board(board);

			// Wykonujemy ruch
			new_board.movePawn(m);

			// Pobieramy wartość MIN (czyli gracz minimalizuje zysk AI) -- ruch AI
			beta = std::min(beta, alphabeta(new_board, depth+1, alpha, beta, AI_COLOR, best_movement));

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
		for(auto& m: board.getPossibleGlobalMovements(player))
		{
			// Tworzymy nowy stan gry
			Board new_board(board);

			// Wykonujemy ruch
			new_board.movePawn(m);

			// Pobieramy wartość stanu gry dla potomka (ruch przeciwnika)
			int temp = alphabeta(new_board, depth+1, alpha, beta, getOpposedColor(AI_COLOR), best_movement);

			// Liczymy MAX (czyli AI maksymalizuje własny zysk)
			// oraz jednocześnie warunek najlepszego ruchu
			if(temp > alpha)
			{
				// Jeśli temp > alpha, przypisujemy alpha a= temp (z definicji MAX(a, b))
				alpha = temp;

				// Na poziomie rekurencji = 1 zwracamy w referencji
				// ruch, za pomocą którego doszliśmy do najlepszego rozwiązania według strategii minimax
				if(depth == 0) best_movement = m;
			}

			// Jeżeli ruch najlepszy nie został wybrany, to wybieramy ruch, który nie jest optymalny, ale jest...
			//else if((depth == 0) && (best_movement == Movement())) best_movement = m;

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
	alphabeta(board, 0, -INF, INF, AI_COLOR, best_movement);

	// Zwracamy najlepszy ruch
	return best_movement;
}

