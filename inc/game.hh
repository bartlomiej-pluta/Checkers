#ifndef GAME_HH
#define GAME_HH

/* Plik implementuje klasę gry, w której znajduje się m.in. główna pętla gry oraz która determinuje całą rozgrywkę. */

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "def.hh"
#include "misc.hh"
#include "object.hh"
#include "pawn.hh"
#include "board.hh"

// Typ wyliczeniowy rozróżniający gracza od sztucznej inteligencji
enum Player
  {
    PL_HUMAN,
    PL_AI
  };

// Klasa gry
class Game
{
private:
  // Okno naszego programu
  sf::RenderWindow window;

  // Plansza do gry w warcaby
  Board board;

  // Zaznaczony pionek
  Pawn* selected; // może lepiej Vector???

  // Kolor gracza
  Color player_color;
  
  // Tura(czy gracz, czy komputer)

  // punkty gracza i komputera

  // stan gry
  
public:

  // Konstruktor inicjalizujący parametry gry i wyzwalający pętlę główną gry
  Game();
  
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
  bool movePawn(Vector position, Vector target);

  // Główna pętla gry
  void loop();
  
};

#endif
