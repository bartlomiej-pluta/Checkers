#ifndef MISC_HH
#define MISC_HH

#include <iostream>
#include <cmath>
#include <SFML/Window.hpp>

#include "def.hh"

/* Struktura reprezentująca wektor w układzie odniesienia planszy do gier (a nie według rzeczywistych współrzędnych - pikseli). */
struct Vector
{
public:
  int x;
  int y;

public:
  
  // Konstruktor tworzący parę (_x, _y)
  Vector(int _x, int _y) : x(_x), y(_y) {}
  
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

  // Dzielenie wektora przez liczbę
  Vector operator/(int a) { return Vector(x/a, y/a); }
  Vector operator/(float a) { return Vector(x/a, y/a); }
  Vector operator/=(int a) { return *this = *this/a; }
  Vector operator/=(float a) { return *this = *this/a; }

  // Porównanie wektorów
  bool operator==(Vector v) { return ((x == v.x) && (y == v.y)); }
  
  // Norma w przestrzeni Manhattan
  int manhattanNorm() const { return abs(x) + abs(y); }

  // Wyświetl wektor
  void display() const { std::cout << "(" << x << ", " << y << ")"; }
  
};



#endif
