#ifndef GAME_HH
#define GAME_HH

/* Plik implementuje klasę gry, w której znajduje się m.in. główna pętla gry oraz która determinuje całą rozgrywkę. */

#include <iostream>
#include <sstream>
#include <string>
#include <list>
#include <algorithm>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "def.hh"
#include "misc.hh"
#include "object.hh"
#include "pawn.hh"
#include "board.hh"
#include "minimax.hh"

// Typ wyliczeniowy rozróżniający gracza od sztucznej inteligencji
enum Player
  {
    PL_HUMAN,
    PL_AI
  };


// Klasa gry
class Game
{
  // Okno naszego programu
  sf::RenderWindow window;

  // Plansza do gry w warcaby
  Board board;

  // Zaznaczony pionek
  Vector selected;

  // Kolor gracza
  Color player_color;

  // Tura(czy gracz, czy AI)
  Color round;

  // Flaga oznaczająca sekwencję ruchów(aby gracz nie mógł zmienić pionka w trakcie gry)
  bool movements_sequence;
  
  // Punkty gracza
  int player_score;

  // Punkty AI
  int ai_score;  

  // AI
  MiniMax minimax;

private:
  
  // Zabij pionka (doliczając do tego punkty)
  void killPawn(Vector position);

  // Do kogo należy pionek
  Player getPlayer(Vector position);

  // Zwróć kolor gracza
  Color getPlayerColor() const { return player_color; }

  // Zwróć kolor przeciwnika
  Color getAIColor() const { return (player_color==CL_WHITE)?CL_BLACK:CL_WHITE; }
  
  // Przesuń pionek na określoną pozycję uwzględniając już
  // przy tym zasady gry w warcaby
  bool movePawn(Movement movement);
  
  // Wykonaj turę gracza (argumentem jest jedyny możliwy sposób interakcji gracza z programem
  // czyli pozycja myszy w momencie kliknięcia lewego przycisku)
  void executePlayerRound(sf::Vector2f mouse_position);
  
  // Przechwytywanie zdarzeń
  void eventHandler();

  // Rysuje HUD (czyli ilość punktów etc.)
  void drawHUD();
  
  // Główna pętla gry
  void loop();
  
public:

  // Konstruktor inicjalizujący parametry gry i wyzwalający pętlę główną gry
  Game();
  
};

#endif
