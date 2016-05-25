#ifndef MINIMAX_HH
#define MINIMAX_HH

/* Plik implementuje klasę reprezentującą strategię Minimaks */

#include <algorithm>
#include "def.hh"
#include "board.hh"

class MiniMax
{
private:

  // Maksymalny poziom zagłębienia algorytmu MiniMax
  const int DEPTH_MAX;

  // Kolor komputera
  const Color AI_COLOR;

private:

  // Funkcja zwraca kolor kolejnego gracza z drzewa minimaks
  Color getColorFromDepth(int depth);
public:
  // Funkcja heurystyczna
  int evaluate(Board& board, const Color& color);
public:

  // Konstruktor przyjmuje parametry: maksymalna głębokość algorytmu MiniMaks oraz kolor pionków
  // sztucznej inteligencji
  MiniMax(int depth_max, Color ai_color) : DEPTH_MAX(depth_max), AI_COLOR(ai_color) {}

  // Algorytm MiniMax z cięciem alfa-beta (funkcja zwraca wartość najlepszego ruchu, natomiast
  // poprzez referencję zwraca najlepszy ruch best_movement
  int alphabeta(Board board, int depth, int alpha, int beta, Movement& best_movement);

  // Funkcja startowa algorytmu minimax z cięciem alfa-beta
  Movement getBestMovement(Board board);
  
};

#endif
