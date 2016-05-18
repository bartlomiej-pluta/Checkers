#include "../inc/board.hh"

Board::Board()
{
  // Czyścimy całą tablicę
  for(int i=0; i<TILES_COUNT; ++i) for(int j=0; j<TILES_COUNT; ++j) board[i][j] = NULL;

  // Tworzymy czarne pionki
  for(int i=1; i<TILES_COUNT; i=i+2)  createPawn(Vector(i, 0), CL_BLACK);
  for(int i=0; i<TILES_COUNT; i=i+2)  createPawn(Vector(i, 1), CL_BLACK);
  for(int i=1; i<TILES_COUNT; i=i+2)  createPawn(Vector(i, 2), CL_BLACK);

  // Tworzymy białe pionki
  for(int i=0; i<TILES_COUNT; i=i+2) createPawn(Vector(i, TILES_COUNT-1), CL_WHITE);
  for(int i=1; i<TILES_COUNT; i=i+2) createPawn(Vector(i, TILES_COUNT-2), CL_WHITE);
  for(int i=0; i<TILES_COUNT; i=i+2) createPawn(Vector(i, TILES_COUNT-3), CL_WHITE);
}

Pawn* Board::createPawn(Vector position, Color color)
{
  // Jeżeli nie istnieje w tym miejscu pionek, to go tworzymy
  if(!board[position.x][position.y])
    board[position.x][position.y] = new Pawn(position, color);

  // Zwracamy istniejący w tym miejscu pionek (dopiero co utworzony, lub isntiejący wcześniej)
  return board[position.x][position.y];
}

Pawn* Board::getPawn(Vector position)
{
  return board[position.x][position.y];
}

bool Board::movePawn(Vector position, Vector target)
{
  // Jeżeli na pozycji startowej nie ma pionka
  if(!getPawn(position)) return false;

  // Jeżeli na pozycji docelowej jest pionek(miejsce zajęte)
  if(getPawn(target)) return false;

  // Przesuwamy pionek na planszy
  board[target.x][target.y] = board[position.x][position.y];
  board[position.x][position.y] = NULL;

  // Aktualizujemy informację o pozycji w pionku
  board[target.x][target.y]->setPosition(target);

  // Zwracamy prawdę, że się udało
  return true;
}

bool Board::isMovementPossible(Vector position, Vector target)
{
  // TODO
  return true;
}

Pawn Board::deletePawn(Vector position)
{
  Pawn deleted_pawn = *board[position.x][position.y];
  delete board[position.x][position.y];
  board[position.x][position.y] = NULL;
  return deleted_pawn;
}

void Board::draw(sf::RenderWindow& window)
{
  // Wymiar X
  for(int x=0; x<TILES_COUNT; ++x)
    {
      // Wymiar Y
      for(int y=0; y<TILES_COUNT; ++y)
	{
	  // Tworzymy pojedynczy kafelek o wymiarach TILE_SIZE x TILE_SIZE
	  sf::RectangleShape tile(sf::Vector2f(TILE_SIZE, TILE_SIZE));

	  // Ustawiamy pozycję na i*TILE_SIZE, j*TILE_SIZE -- czyli np. dla TILE_SIZE = 64:  (0,0), (0,64), (0,128), ...
	  tile.setPosition(x*TILE_SIZE, y*TILE_SIZE);

	  // Ustawiamy kolor wypełnienia co drugiego kafelka na jasny
	  tile.setFillColor(((x+y)%2)?sf::Color(150, 74, 0):sf::Color(248, 246, 184));

	  // Rysujemy kafelki
	  window.draw(tile);

	  // Jeżeli istnieją na danym polu pionki, to je rysujemy
	  if(board[x][y]) board[x][y]->draw(window);
	  
	}
    }
}

Pawn* Board::selectPawn(Vector position)
{
  // Jeżeli pionek na tym polu istnieje
  if(board[position.x][position.y])
    {
      // Odznaczamy wszystkie pionki
      for(int x = 0; x<TILES_COUNT; ++x)
	for(int y = 0; y<TILES_COUNT; ++y)
	  if(board[x][y]) board[x][y]->deselect();

      // Zaznaczamy właściwy
      board[position.x][position.y]->select();

      // Zwracamy zaznaczony
      return board[position.x][position.y];
    }

  // Zwracamy NULL, bo pionek nie istnieje
  return NULL;
}
