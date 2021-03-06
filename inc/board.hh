#ifndef BOARD_HH
#define BOARD_HH

/* Plik zawiera implementację planszy(board) do gry w warcaby. */

#include <iostream>
#include <list>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "pawn.hh"

// Struktura przechowująca informacje o ruchu
struct Movement
{
  // Początek ruchu
  Vector begin;

  // Koniec ruchu
  Vector end;

  Movement() : begin(0, 0), end(0, 0) {}
  
  // Prosty konstruktor
  Movement(Vector b, Vector e) : begin(b), end(e) {}

  // Operator porównania
  bool operator==(const Movement& b) { return ((begin == b.begin) && (end == b.end)); }

  // Wypisywanie ruchu do terminala
  void display() { begin.display(); std::cout<< "\t->\t"; end.display(); std::cout << std::endl; }

  // Zwraca wektor ruchu
  Vector getVector() { return end-begin; }
};

// Klasa implementująca planszę
class Board
{
private:

  // Plansza (czyli dwuwymiarowa tablica wskaźników na pionki)
  Pawn* board[TILES_COUNT][TILES_COUNT];

  // Zaznaczone kafelki na mapie(ułatwienie dla gracza)
  std::list<Vector> selected_tiles;
  
  // Zaznaczony ruch na mapie
  bool is_selected_movement;

public:

  // Konstruktor inicjujący planszę
  Board();

  // Konstruktor kopiujący
  Board(const Board& original);

  // Tworzy pionki i układa je w początkowym ułożeniu
  // według zasad gry w warcaby
  void initBoard();
  
  // Usuwa wszystkie pionki z planszy
  void clearBoard();

  // Utwórz nowy pionek na zadanej pozycji
  Pawn* createPawn(Vector position, Color color);
  
  // Pobierz pionek z określonej pozycji
  Pawn* getPawn(Vector position);

  // Przesuń pionek na określoną pozycję
  bool movePawn(Movement movement);

  // Pobierz ilość białych pionków
  unsigned int getNumberOfWhitePawns() const;

  // Pobierz ilość czarnych pionków
  unsigned int getNumberOfBlackPawns() const;

  // Promuj na damki te pionki, które doszły na linię promocji
  void upgrade();
  
  // Czy pionek jest zagrożony biciem
  bool isEndangered(Vector position);

  // Czy bicie z danej pozycji jest możliwe
  bool isPossibleBeating(Vector position);

  // Czy istnieje możliwe bicie dla danego koloru
  bool arePossibleGlobalBeatings(Color color);

  // Kontener możliwych bić
  std::list<Movement> getPossibleBeatings(Vector position);

  // Pobierz możliwe ruchy pionka
  std::list<Movement> getPossibleMovements(Vector position);

  // Pobierz możliwe ruchy wszystkich pionków danego koloru
  std::list<Movement> getPossibleGlobalMovements(Color color);

  // Pobierz możliwe bicia wszystkich pionków danego koloru
  std::list<Movement> getPossibleGlobalBeatings(Color color);
  
  // Usuń pionek z określonej pozycji
  Pawn deletePawn(Vector position);

  // Rysuj planszę wraz z pionkami
  void draw(sf::RenderWindow& window);

  // Zaznacz pionek o zadanej pozycji
  Pawn* selectPawn(Vector position);  

  // Zaznacz wybrane kafelki na mapie
  void selectTiles(std::list<Vector> tiles) { selected_tiles = tiles; }

  // Zaznacz ruch na mapie
  void selectMovement(Movement movement);

  // Odznacz kafelki na mapie
  void deselectTiles() { is_selected_movement = false; selected_tiles.clear(); }

  // Wyświetl zawartość planszy na standardowym wyjściu
  void display();
  
  // Destruktor
  ~Board() {}
  
};

#endif
