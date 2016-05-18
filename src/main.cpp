#include <iostream>
#include <SFML/Window.hpp>

#include "../inc/def.hh"
#include "../inc/misc.hh"
#include "../inc/object.hh"
#include "../inc/pawn.hh"
#include "../inc/board.hh"
#include "../inc/game.hh"

int main()
{
  /*  sf::ContextSettings settings;
  settings.antialiasingLevel = 8;
  sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32), "Warcaby",  sf::Style::Close, settings);  
  Board board;
  Pawn* selected;
  while(window.isOpen())
    {
      sf::Event event;
      while(window.pollEvent(event))
	{
	  if(event.type == sf::Event::Closed) window.close();
	  if(event.type == sf::Event::MouseButtonPressed)
	    {
	      if(event.mouseButton.button == sf::Mouse::Left)
		{
		  Pawn* tmp = board.selectPawn(Vector(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)));
		  if(tmp) selected = tmp;
		  else board.movePawn(selected->getPosition(), Vector(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)));
		}
	    }
	}
      window.clear(sf::Color(255, 255, 255));
      board.draw(window);
      window.display();
      }*/
  return 0;
}
