#include "../inc/board.hh"

Board::Board()
{
  // Czyścimy całą tablicę
  for(int i=0; i<TILES_COUNT; ++i) for(int j=0; j<TILES_COUNT; ++j) board[i][j] = NULL;
}

void Board::initBoard()
{
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

bool Board::movePawn(Movement movement)
{
  // Pomocnicze wektory
  Vector& position = movement.begin;
  Vector& target = movement.end;
  
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

bool Board::isMovementPossible(Movement movement)
{
  /** TODO **/
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
  
  // Zaznacz kafelki przeznaczone do zaznaczenia
  for(auto selected_tile: selected_tiles)
    {
      // Pobieramy współrzędne
      int x = selected_tile.x;
      int y = selected_tile.y;
      
      // Tworzymy pojedynczy kafelek o wymiarach TILE_SIZE x TILE_SIZE
      sf::RectangleShape tile(sf::Vector2f(TILE_SIZE, TILE_SIZE));

      // Ustawiamy pozycję na i*TILE_SIZE, j*TILE_SIZE -- czyli np. dla TILE_SIZE = 64:  (0,0), (0,64), (0,128), ...
      tile.setPosition(x*TILE_SIZE, y*TILE_SIZE);

      // Ustawiamy kolor wypełnienia co drugiego kafelka na jasny
      tile.setFillColor(((x+y)%2)?sf::Color(200, 124, 50):sf::Color(255, 255, 220));

      // Rysujemy kafelki
      window.draw(tile);

      // Jeżeli istnieją na danym polu pionki, to je rysujemy
      if(board[x][y]) board[x][y]->draw(window);
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


bool Board::isPossibleBeating(Vector position)
{
  // Pobieramy wskaźnik do pionka znajdującego się na zadanej pozycji
  Pawn* position_pawn = getPawn(position);

  // Jeżeli go tam nie ma, zwracamy false
  if(!position_pawn) return false;
  
  // Zabezpieczenie przed przekroczeniem indeksów
  if((getPawn(position)->getPosition().x > 1 &&
     getPawn(position)->getPosition().y > 1) &&
     (getPawn(position)->getPosition().x < TILES_COUNT-1 &&
      getPawn(position)->getPosition().y < TILES_COUNT-1))

    // Jeżeli na polu przesuniętym o wektor [1,1] jest pionek, i jest on koloru przeciwnego
    // a za pole zanim jest puste, zwracamy true
    if(getPawn(position+Vector(1, 1)) &&
       (getPawn(position+Vector(1, 1))->getColor() != position_pawn->getColor()) &&
       (!getPawn(position+Vector(2, 2)))) return true;

  // ... analogicznie w pozostałych kierunkach
  
  // Zabezpieczenie przed przekroczeniem indeksów
  if((getPawn(position)->getPosition().x > 1 &&
     getPawn(position)->getPosition().y > 1) &&
     (getPawn(position)->getPosition().x < TILES_COUNT-1 &&
      getPawn(position)->getPosition().y < TILES_COUNT-1))
    
    if(getPawn(position+Vector(1, -1)) &&
       (getPawn(position+Vector(1, -1))->getColor() != position_pawn->getColor()) &&
       (!getPawn(position+Vector(2, -2)))) return true;

  // Zabezpieczenie przed przekroczeniem indeksów
  if(getPawn(position)->getPosition().x > 1 &&
     getPawn(position)->getPosition().y > 1)
    
    if(getPawn(position+Vector(-1, 1)) &&
       (getPawn(position+Vector(-1, 1))->getColor() != position_pawn->getColor()) &&
       (!getPawn(position+Vector(-2, 2)))) return true;

  // Zabezpieczenie przed przekroczeniem indeksów
  if(getPawn(position)->getPosition().x > 1 &&
     getPawn(position)->getPosition().y > 1)
   
    if(getPawn(position+Vector(-1, -1)) &&
     (getPawn(position+Vector(-1, -1))->getColor() != position_pawn->getColor()) &&
     (!getPawn(position+Vector(-2, -2)))) return true;

  return false;
    
}

std::list<Movement> Board::getPossibleBeatings(Vector position)
{
  // Tworzymy nowy kontener na pozycje
  std::list<Movement> beatings;
  
  // Pobieramy wskaźnik do pionka znajdującego się na zadanej pozycji
  Pawn* position_pawn = getPawn(position);

  // Jeżeli go tam nie ma, zwracamy pusty kontener
  if(!position_pawn) return beatings;

  // Jeżeli na polu przesuniętym o wektor [1,1] jest pionek, i jest on koloru przeciwnego
  // a za pole zanim jest puste, dorzucamy tą pozycję do kontenera
  if(position.x < TILES_COUNT-1 && position.y < TILES_COUNT-1)
  if(getPawn(position+Vector(1, 1)) &&
     (getPawn(position+Vector(1, 1))->getColor() != position_pawn->getColor()) &&
     (!getPawn(position+Vector(2, 2)))) beatings.push_back(Movement(position, position+Vector(2, 2)));

  // ... analogicznie w pozostałych kierunkach
  if(position.x < TILES_COUNT-1 && position.y > 1)
  if(getPawn(position+Vector(1, -1)) &&
     (getPawn(position+Vector(1, -1))->getColor() != position_pawn->getColor()) &&
     (!getPawn(position+Vector(2, -2)))) beatings.push_back(Movement(position, position+Vector(2, -2)));

  if(position.x > 1 && position.y < TILES_COUNT-1)
  if(getPawn(position+Vector(-1, 1)) &&
     (getPawn(position+Vector(-1, 1))->getColor() != position_pawn->getColor()) &&
     (!getPawn(position+Vector(-2, 2)))) beatings.push_back(Movement(position, position+Vector(-2, 2)));

  if(position.x > 1 && position.y > 1)
  if(getPawn(position+Vector(-1, -1)) &&
     (getPawn(position+Vector(-1, -1))->getColor() != position_pawn->getColor()) &&
     (!getPawn(position+Vector(-2, -2)))) beatings.push_back(Movement(position, position+Vector(-2, -2)));

  // Zwracamy kontener
  return beatings;
    
}

std::list<Movement> Board::getPossibleMovements(Vector position)
{
  // Jeżeli są możliwe bicia, zwróć je
  if(isPossibleBeating(position)) return getPossibleBeatings(position);

  std::list<Movement> movements;
  
  // Jeżeli pionek nie istnieje, zwróć pustą listę
  if(!getPawn(position)) return movements;

  // Jeżeli to ruch czarnego pionka
  if(getPawn(position)->getColor() == CL_BLACK)
    {
      // Zabezpieczenie przed przekroczeniem indeksów
      if(getPawn(position)->getPosition().x > 0 &&
	 getPawn(position)->getPosition().y > 0)
	
	// Jeżeli miejsce 1 jest wolne, wrzuć do listy
	if(!getPawn(position+Vector(1, 1))) movements.push_back(Movement(position, position+Vector(1, 1)));

      // Zabezpieczenie przed przekroczeniem indeksów
      if(getPawn(position)->getPosition().x > 0 &&
	 getPawn(position)->getPosition().y > 0)
	
	// Jeżeli miejsce 2 jest wolne, wrzuć do listy
	if(!getPawn(position+Vector(-1, 1))) movements.push_back(Movement(position, position+Vector(-1, 1)));
    }

  // Jeżeli to ruch białego pionka
  if(getPawn(position)->getColor() == CL_WHITE)
    {
      // Zabezpieczenie przed przekroczeniem indeksów
      if(getPawn(position)->getPosition().x > 1 &&
	 getPawn(position)->getPosition().y > 1)
	
	// Jeżeli miejsce 1 jest wolne, wrzuć do listy
	if(!getPawn(position+Vector(-1, -1))) movements.push_back(Movement(position, position+Vector(-1, -1)));

      // Jeżeli miejsce 2 jest wolne, wrzuć do listy
      if(position.y > 1)
	if(!getPawn(position+Vector(1, -1))) movements.push_back(Movement(position, position+Vector(1, -1)));
    }
  return movements;
}

std::list<Movement> Board::getPossibleMovements(Color color)
{
  std::list<Movement> movements;

  // Dla każdych pionków
  for(int x = 0; x < TILES_COUNT; ++x)
    for(int y = 0; y < TILES_COUNT; ++y)
      {
	// Jeżeli to jest pionek
	if(board[x][y])
	  {
	    // Jeżeli jest to pionek o który nam chodzi
	    if(board[x][y]->getColor() == color)

	      // Dodaj wszystkie jego możliwe ruchy do listy ruchów
	      for(auto m: getPossibleMovements(Vector(x, y))) movements.push_back(m);
	  }
      }
      
  return movements;
}

void Board::display()
{
  // Wyświetl poziomą linię
  for(int i=0; i<TILES_COUNT; ++i) std::cout << "+---";
  std::cout << "+" << std::endl;

  // Wyświetl całą planszę
  for(int y = 0; y<TILES_COUNT; ++y)
    {
      // Pojedynczy wiersz
      for(int x = 0; x<TILES_COUNT; ++x)
	{
	  std::cout << "|";
	  if(board[x][y])
	    {
	      if(board[x][y]->getColor() == CL_WHITE) std::cout << " O ";
	      else std::cout << " @ ";
	    } else std::cout << "   ";
	}
      std::cout << "|" << std::endl;

      // Pozioma linia
      for(int i=0; i<TILES_COUNT; ++i) std::cout << "+---";
      std::cout << "+" << std::endl;            
    }
}

Board::Board(const Board& original)
{
  // Czyścimy całą tablicę
  for(int i=0; i<TILES_COUNT; ++i) for(int j=0; j<TILES_COUNT; ++j) board[i][j] = NULL;

  // Kopiujemy wszystko...
  for(int x = 0; x<TILES_COUNT; ++x)
    for(int y = 0; y<TILES_COUNT; ++y)

      // Jeżeli istnieje pionek na tym polu...
      if(original.board[x][y])

	// ... to w nowotworzonej planszy tworzymy identyczny pionek
        createPawn(Vector(x, y), original.board[x][y]->getColor());
  
}
