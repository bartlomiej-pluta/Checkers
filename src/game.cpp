#include "../inc/game.hh" 

Game::Game()
  :
  window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32), "Warcaby", sf::Style::Close),
  selected(NULL),
  player_color(CL_WHITE)
{
  // Kod inicjalizujący
  // Pętla główna
  loop();
}

void Game::killPawn(Vector position)
{
}

Player Game::getPlayer(Vector position)
{
  //
  return PL_HUMAN;
}

bool Game::movePawn(Vector position, Vector target)
{
  //
  return true;
}

void Game::loop()
{
}
