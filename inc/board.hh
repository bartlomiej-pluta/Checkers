#ifndef BOARD_HH
#define BOARD_HH

/* Plik zawiera implementację planszy(board) do gry w warcaby. */

class Board
{
private:

  // Tablica pionków
  // Pawn*** board
public:

  // Konstruktor inicjujący planszę
  Board() {}

  // Utwórz nowy pionek na zadanej pozycji
  Pawn& createPawn(Vector position);
  
  // Pobierz pionek z określonej pozycji
  Pawn& getPawn(Vector position);

  // Przesuń pionek na określoną pozycję(target)
  void setPawnPosition(Vector position, Vector target);
  
  // Przesuń pionek o określony wektor
  void movePawn(Vector position, Vector vector);

  // Czy ruch jest możliwy (czy dana pozycja jest osiągalna)
  bool isMovementPossible(Vector position, Vector target);
  
  // Usuń pionek z określonej pozycji
  Pawn deletePawn(Vector position);

  // Rysuj planszę wraz z pionkami
  void draw(sf::RenderWindow window);

  // Destruktor
  ~Board();
  
};

#endif
