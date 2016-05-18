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

  // Czy pionek jest zaznaczony
  bool selected;

  // Czy pionek jest królową
  bool queen;
public:

  // Konstruktor tworzący pionek na zadanej pozycji startowej i o określonym kolorze
  Pawn(Vector _position, Color _color) : Object(_position), color(_color), selected(false), queen(false) {}  
  
  // Pobierz kolor
  Color getColor() const { return color; }

  // Rysuj pionek na obiekcie window
  void draw(sf::RenderWindow& window);

  // Czy jest zaznaczony
  bool isSelected() const { return selected; }

  // Czy jest królową
  bool isQueen() const { return queen; }
  
  // Zaznacz pionek
  void select() { selected = true; }

  // Odznacz pionek
  void deselect() { selected = false; }

  // Zamień na królową
  void upgrade() { queen = true; }

  // Zamień spowrotem w zwykłego pionka
  void downgrade() { queen = false; }
  
  // Destruktor
  ~Pawn() {}
};

#endif
