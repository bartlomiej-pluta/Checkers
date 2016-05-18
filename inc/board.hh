#ifndef BOARD_HH
#define BOARD_HH

/* Plik zawiera implementację planszy(board) do gry w warcaby. */

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "pawn.hh"

class Board
{
private:

  // Plansza (czyli dwuwymiarowa tablica wskaźników na pionki)
  Pawn* board[TILES_COUNT][TILES_COUNT];
public:

  // Konstruktor inicjujący planszę
  Board();

  // Utwórz nowy pionek na zadanej pozycji
  Pawn* createPawn(Vector position, Color color);
  
  // Pobierz pionek z określonej pozycji
  Pawn* getPawn(Vector position);

  // Przesuń pionek na określoną pozycję
  bool movePawn(Vector position, Vector target);

  // Czy ruch jest możliwy (czy dana pozycja jest osiągalna)
  bool isMovementPossible(Vector position, Vector target);
  
  // Usuń pionek z określonej pozycji
  Pawn deletePawn(Vector position);

  // Rysuj planszę wraz z pionkami
  void draw(sf::RenderWindow& window);

  // Zaznacz pionek o zadanej pozycji
  Pawn* selectPawn(Vector position);

  // Destruktor
  ~Board() {}
  
};

#endif
