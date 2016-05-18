#ifndef DEF_HH
#define DEF_HH

#include <SFML/Window.hpp>

/* Plik zawiera definicje stałych globalnych oraz przedefiniowanie istniejących typów. */

// Ilość pól w każdym wymiarze
const int TILES_COUNT = 10;

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
const int WINDOW_HEIGHT = TILES_COUNT * TILE_SIZE;

// Przedefiniowanie sf::Vector2f na RealVector
typedef sf::Vector2f RealVector;

#endif
