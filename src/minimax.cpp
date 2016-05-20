#include "../inc/minimax.hh"


int MiniMax::f1(Board& board, const Color& color)
{
  // Wycena
  int value = 0, tmp_value;

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
	    if(ptr->isQueen()) tmp_value = 10;
	    else tmp_value = 1;

	    // Jeżeli pionek należy do obszaru III -- waga 3
	    if(((ptr->getPosition().x >= 3) && (ptr->getPosition().y >= 3)) &&
	       ((ptr->getPosition().x < (TILES_COUNT-3)) && (ptr->getPosition().y < (TILES_COUNT-3))))
	      tmp_value *= 3;

	    // Jeżeli pionek należy do obszaru II -- waga 2
	    else if(((ptr->getPosition().x >= 2) && (ptr->getPosition().y >= 2)) &&
	       ((ptr->getPosition().x < (TILES_COUNT-2)) && (ptr->getPosition().y < (TILES_COUNT-2))))
	      tmp_value *= 2;

	    // W przeciwnym wypadku, zostaje waga 1

	    // Jeżeli NIE jest to pionek należący do gracza zdefiniowanego kolorem color
	    // przemnażamy przez -1
	    if(ptr->getColor() != color) tmp_value *= -1;
	    
	    // Dodajemy tmp_value do wyceny
	    value += tmp_value;
	  }
      }

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
      for(auto& m: board.getPossibleMovements(color))
	{
	  // Tworzymy nowy stan gry
	  Board new_board(board);

	  // Wykonujemy ruch
	  new_board.movePawn(m);

	  // Pobieramy wartość MIN (czyli gracz minimalizuje zysk AI)
	  beta = std::min(beta, alphabeta(new_board, depth+1, alpha, beta, best_movement));	  
	  
	  // Jeżeli alfa >= beta odcinamy gałąź alpha
	  if(alpha >= beta) break;
	}
    }

  // Jeśli jest teraz ruch AI
  else
    
    // Dla każdego potomka 
    for(auto& m: board.getPossibleMovements(color))
      {
	// Tworzymy nowy stan gry
	Board new_board(board);
	
	// Wykonujemy ruch
	new_board.movePawn(m);

	// Pobieramy wartość MAX (czyli AI maksymalizuje własny zysk)
        alpha = std::max(alpha, alphabeta(new_board, depth+1, alpha, beta, best_movement));

	// Zwracamy w referencji ruch (dążymy do tego, aby na poziomie głębokości = 1 mieć
	// ruch, za pomocą którego doszliśmy do najlepszego rozwiązania według strategii minimax)
	best_movement = m;
	
	// Jeżeli alfa >= beta odcinamy gałąź beta
	if(alpha >= beta) break;
      }

  // Zwracamy wartość najlepszego ruchu
  return alpha;
}

Movement MiniMax::minimax(Board board)
{
  // Tworzymy bufor na ruch
  Movement best_movement;

  // Pobieramy algorytmem minimax z cięciem alfa-beta najlepszy ruch
  alphabeta(board, 1, -INF, INF, best_movement);

  // Zwracamy najlepszy ruch
  return best_movement;
}
