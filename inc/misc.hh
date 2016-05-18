#ifndef MISC_HH
#define MISC_HH

#include <SFML/Window.hpp>

#include "def.hh"

/* Struktura reprezentująca wektor w układzie odniesienia planszy do gier (a nie według rzeczywistych współrzędnych - pikseli). */
struct Vector
{
  unsigned int x;
  unsigned int y;

  // Konstruktor tworzący parę (_x, _y)
  Vector(unsigned int _x, unsigned int _y) : x(_x), y(_y) {}
  
  // Konstruktor tworzący parę (x, y) na podstawie rzeczywistych współrzędnych
  Vector(const RealVector& real_position) : x(real_position.x/TILE_SIZE), y(real_position.y/TILE_SIZE) {}
  
  // Pobierz rzeczywistą pozycję górnego, lewego narożnika kafelka o współrzędnych (x, y)
  RealVector getRealVector() const { return RealVector(x*TILE_SIZE, y*TILE_SIZE); }

  // Pobierz rzeczywistą pozycję środka kafelka o współrzędnych (x, y)
  RealVector getCenterRealVector() const { return  RealVector(x*TILE_SIZE + 0.5*TILE_SIZE, y*TILE_SIZE + 0.5*TILE_SIZE); }

  // Operator dodawania wektorów
  Vector operator+(const Vector& v) { return Vector(x+v.x, y+v.y); }
  Vector& operator+=(const Vector& v) { return *this = *this + v; }

  // Operator odejmowania wektorów
  Vector operator-(const Vector& v) { return Vector(x-v.x, y-v.y); }
  Vector& operator-=(const Vector& v) { return *this = *this - v; }

  // Mnożenie wektora przez liczbę
  Vector operator*(int a) { return Vector(a*x, a*y); }
  Vector operator*(float a) { return Vector(a*x, a*y); }
  Vector operator*=(int a) { return *this = *this*a; }
  Vector operator*=(float a) { return *this = *this*a; }
  
};

#endif
