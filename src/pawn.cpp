#include "../inc/pawn.hh" 

void Pawn::draw(sf::RenderWindow& window)
{
  // Tworzymy nowy kształt koła o promieniu równym połowie długości boku kafelka i odjęciu dwóch marginesów 
  sf::CircleShape pawn(TILE_SIZE/2 - PAWN_MARGIN);

  // Ustawiamy jego pozycję na pozycję zwróconą przez getPosition() uwzględniając marginesy
  pawn.setPosition(getPosition().getRealVector() + sf::Vector2f(PAWN_MARGIN, PAWN_MARGIN));

  // Jeżeli nie jest zaznaczony,
  // wypełniamy odpowiednim kolorem w zależności od pionka(czy biały, czy czarny)
  if(!selected)
    pawn.setFillColor((color==CL_WHITE)?sf::Color(225, 223, 212):sf::Color(41, 0, 0));
  
  // w przeciwnym razie wypełniamy nieco jaśniejszymi kolorami
  else
    pawn.setFillColor((color==CL_WHITE)?sf::Color(255, 255, 250):sf::Color(71, 30, 30));

  // Ustawiamy odpowiedni kontur
  if(!queen) // W zależności od pionka(czy biały, czy czarny)
    {
      pawn.setOutlineThickness(PAWN_OUTLINE_THICKNESS);
      pawn.setOutlineColor((color==CL_WHITE)?sf::Color(133, 116, 38):sf::Color(10, 0, 0));
    }
  else // Dla królowej zawsze złoty
    {
      pawn.setOutlineThickness(QUEEN_PAWN_OUTLINE_THICKNESS);
      pawn.setOutlineColor(sf::Color(255, 200, 0));
    }  
  
  // Rysujemy na obiekcie window
  window.draw(pawn);
}
