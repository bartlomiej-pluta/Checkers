#include <iostream>
#include <SFML/Window.hpp>

#include "../inc/def.hh"
#include "../inc/misc.hh"
#include "../inc/object.hh"
#include "../inc/pawn.hh"

int main()
{
  sf::ContextSettings settings;
  settings.antialiasingLevel = 8;
  sf::RenderWindow window(sf::VideoMode(800, 600, 32), "Warcaby",  sf::Style::Default, settings);  
  Pawn pawn(Vector(0, 0), CL_BLACK);
  while(window.isOpen())
    {
      sf::Event event;
      while(window.pollEvent(event))
	{
	  if(event.type == sf::Event::Closed) window.close();	  
	}
      window.clear(sf::Color(255, 255, 255));
      pawn.draw(window);
      window.display();
    }
  return 0;
}
