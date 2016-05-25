#ifndef DEF_HH
#define DEF_HH

#include <SFML/Window.hpp>
#include <string>

/* Plik zawiera definicje stałych globalnych oraz przedefiniowanie istniejących typów. */

// Tytuł gry (widoczny m.in. na pasku z tytułem okna)
const std::string GAME_TITLE = "Warcaby";

// Ilość pól w każdym wymiarze
const int TILES_COUNT = 8;

// Długość boku pojedynczego kafelka(który jest kwadratem)
const int TILE_SIZE = 64;

// Odpowiednie przeskalowanie pionka, aby zachowany był margines względem krawędzi kafelka
const int PAWN_MARGIN = 10;

// Grubość konturu zwykłego pionka
const int PAWN_OUTLINE_THICKNESS = 2;

// Grubość konturu pionka-królowej
const int QUEEN_PAWN_OUTLINE_THICKNESS = 4;

// Szerokość okna
const int WINDOW_WIDTH = TILES_COUNT * TILE_SIZE;

// Wysokość okna
const int WINDOW_HEIGHT = TILES_COUNT * TILE_SIZE + 30;

// Wartość nieskończoności
const int INF = 9999;

// Przedefiniowanie sf::Vector2f na RealVector
typedef sf::Vector2f RealVector;

#endif
