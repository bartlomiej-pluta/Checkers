#ifndef OBJECT_HH
#define OBJECT_HH

/* Klasa object będąca interfejsem po którym dziedziczą pionki.
 * Klasa ta deklaruje podstawowe elementy obiektów znajdujących się
 * na planszy, takie jak wyświetlanie, przesuwanie czy odczytywanie pozycji.
 * Nie definiuje ona jeszcze żadnych kształtów czy kolorów, jest więc zatem klasą
 * w zasadzie czysto abstrakcyjną. */

#include <SFML/Window.hpp>

#include "def.hh"
#include "misc.hh"

class Object
{
private:

  // Pozycja obiektu
  Vector position;
public:

  // Pobierz pozycję obiektu
  Vector getPosition() const { return position; }

  // Ustaw pozycję obiektu
  void setPosition(const Vector& _position) { position = _position }

  // Przesuń obiekt o wektor
  void move(const Vector& vector) {}

  // Rysuj obiekt
  void draw(sf::RenderWindow window) = 0;
};

#endif
