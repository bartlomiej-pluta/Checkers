#ifndef PAWN_HH
#define PAWN_HH

/* Plik implementuje klasę pionka(kamienia) jako pochodną klasy Object */

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "def.hh"
#include "object.hh"

// Typ wyliczeniowy definiujący możliwe kolory
enum Color
  {
    CL_WHITE,
    CL_BLACK
  };

// Klasa reprezentująca pionek
class Pawn : public Object
{
private:

  // Kolor pionka
  Color color;
public:

  // Konstruktor tworzący pionek na zadanej pozycji startowej i o określonym kolorze
  Pawn(Vector _position, Color _color) : Object(_position), color(_color) {}

  // Pobierz kolor
  Color getColor() const { return color; }

  // Rysuj pionek na obiekcie window
  void draw(sf::RenderWindow& window);

  // Destruktor
  ~Pawn() {}
};

#endif
