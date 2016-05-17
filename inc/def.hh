#ifndef DEF_HH
#define DEF_HH

#include <SFML/Window.hpp>

/* Plik zawiera definicje stałych globalnych oraz przedefiniowanie istniejących typów. */

// Długość boku pojedynczego kafelka(który jest kwadratem)
const int TILE_SIZE = 64;

// Przedefiniowanie sf::Vector2f na RealVector
typedef sf::Vector2f RealVector;

#endif
