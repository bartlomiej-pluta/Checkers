#include "../inc/pawn.hh" 

void Pawn::draw(sf::RenderWindow& window)
{
  // Tworzymy nowy kształt koła o promieniu równym połowie długości boku kafelka i odjęciu dwóch marginesów 
  sf::CircleShape pawn(TILE_SIZE/2 - PAWN_MARGIN*2);

  // Ustawiamy jego pozycję na pozycję zwróconą przez getPosition() uwzględniając marginesy
  pawn.setPosition(getPosition().getRealVector() + sf::Vector2f(PAWN_MARGIN, PAWN_MARGIN));

  // Wypełniamy odpowiednim kolorem
  pawn.setFillColor((color==CL_WHITE)?sf::Color::White:sf::Color::Black);

  // Rysujemy na obiekcie window
  window.draw(pawn);
}
