#include "../inc/game.hh" 

Game::Game()
  :
  selected(TILES_COUNT+1, TILES_COUNT+1),        // Brak zaznaczenia
  player_color(CL_WHITE),                        // Domyślny kolor gracza
  round(CL_WHITE),                               // Pierwszy ruch mają białe pionki
  movements_sequence(false),                     // Ciąg kolejnych ruchów
  player_score(0),                               // Wyzerowana ilość punktów gracza
  ai_score(0),                                   // Wyzerowana ilość punktów AI
  minimax(7, getAIColor())                       // Poziom AI oraz kolor AI 
{
  // Ustawienia antyaliasingu
  sf::ContextSettings settings;
  settings.antialiasingLevel = 8;
    
  // Utworzenie okna
  window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32), GAME_TITLE, sf::Style::Close, settings);

  // Wygenerowanie planszy startowej
  board.initBoard();  
  
  // Pętla główna
  loop();
}

void Game::killPawn(Vector position)
{
  // Dodaj odpowiednio punkty
  if(board.getPawn(position)->getColor() == getPlayerColor()) ++ai_score;
  else ++player_score;

  // Usuń pionek
  board.deletePawn(position);
}

Player Game::getPlayer(Vector position)
{
  if(board.getPawn(position)->getColor() == getPlayerColor()) return PL_HUMAN;
  else return PL_AI;
}

bool Game::movePawn(Movement movement)
{
  // Pomocnicze wektory
  Vector& position = movement.begin;
  Vector& target = movement.end;
  
  // Jeżeli pionek startowy nie istnieje
  if(!board.getPawn(position)) return false;
  
  // Jeżeli ruch należy do drugiego gracza
  if(board.getPawn(position)->getColor() != round) return false;
  
  // Jeżeli kafelek jest zajęty
  if(board.getPawn(target)) return false;

  // Jeżeli to ruch czarnego pionka
  if(board.getPawn(position)->getColor() == CL_BLACK)
    {
      // Jeżeli jest to zwykły ruch na ukos
      if((target-position == Vector(1, 1)) || // Jeżeli jest to ruch o wektor [1, 1]
	 (target-position == Vector(-1, 1)))     // --//--
	return board.movePawn(Movement(position, target)); // Rusz pionek
    }

  // Jeżeli to ruch białego pionka
  if(board.getPawn(position)->getColor() == CL_WHITE)
    {
      // Jeżeli jest to zwykły ruch na ukos
      if((target-position == Vector(-1, -1)) || // Jeżeli jest to ruch o wektor [1, 1]
	 (target-position == Vector(1, -1)))     // --//--
	return board.movePawn(Movement(position, target)); // Rusz pionek
    }
     
  // Jeżeli jest to przeskok nad drugim graczem
  if((target-position == Vector(-2, -2)) &&      // Jeżeli jest to ruch o wektor [-2, -2]
     (board.getPawn(position+Vector(-1, -1))) && // Jeżeli istnieje pionek na polu przesuniętym o [-1, -1]
     (board.getPawn(position+Vector(-1, -1))->getColor() != board.getPawn(position)->getColor())) // Jeżeli jest to gracz o innym kolorze
    {
      // Zabij zbijanego pionka
      killPawn(position+Vector(-1, -1));

      // Przesuń pionek
      return board.movePawn(Movement(position, target));
    }

  if((target-position == Vector(-2, 2)) &&      // Jeżeli jest to ruch o wektor [-2, -2]
     (board.getPawn(position+Vector(-1, 1))) && // Jeżeli istnieje pionek na polu przesuniętym o [-1, -1]
     (board.getPawn(position+Vector(-1, 1))->getColor() != board.getPawn(position)->getColor())) // Jeżeli jest to gracz o innym kolorze
    {
      // Zabij zbijanego pionka
      killPawn(position+Vector(-1, 1));

      // Przesuń pionek
      return board.movePawn(Movement(position, target));
    }

  if((target-position == Vector(2, -2)) &&      // Jeżeli jest to ruch o wektor [-2, -2]
     (board.getPawn(position+Vector(1, -1))) && // Jeżeli istnieje pionek na polu przesuniętym o [-1, -1]
     (board.getPawn(position+Vector(1, -1))->getColor() != board.getPawn(position)->getColor())) // Jeżeli jest to gracz o innym kolorze
    {
      // Zabij zbijanego pionka
      killPawn(position+Vector(1, -1));

      // Przesuń pionek
      return board.movePawn(Movement(position, target));
    }

  if((target-position == Vector(2, 2)) &&      // Jeżeli jest to ruch o wektor [-2, -2]
     (board.getPawn(position+Vector(1, 1))) && // Jeżeli istnieje pionek na polu przesuniętym o [-1, -1]
     (board.getPawn(position+Vector(1, 1))->getColor() != board.getPawn(position)->getColor())) // Jeżeli jest to gracz o innym kolorze
    {
      // Zabij zbijanego pionka
      killPawn(position+Vector(1, 1));

      // Przesuń pionek
      return board.movePawn(Movement(position, target));
    }
     
  return false;
}

void Game::executePlayerRound(sf::Vector2f mouse_position)
{
  // Konwersja pozycji myszy na współrzędne kafelka
  Vector position(mouse_position);

  // Pobieramy informacje o pionku(lub jego braku) z interesującego nas pola
  Pawn* ptr = board.getPawn(position);

  // Jeżeli tura należy do gracza, pionek istnieje i należy do gracza oraz ruch nie został jeszcze rozpoczęty:
  if((round == getPlayerColor()) && ptr && (ptr->getColor() == getPlayerColor()) && (!movements_sequence))
    {
      // Zaznaczamy pionek i pobieramy do niego wskaźnik
      ptr = board.selectPawn(Vector(position));

      // Pobieramy jego pozycję i zapisujemy do zmiennej przechowującej zaznaczony pionek
      selected = ptr->getPosition();

      // Zaznacz dozwolone kafelki na mapie
      std::list<Vector> possible_tiles; // Lista dozwolonych kafelków
      for(const auto& m: board.getPossibleMovements(selected)) // Pobieramy dozwolone kafelki docelowe z dozwolonych ruchów
	possible_tiles.push_back(m.end);
      board.selectTiles(possible_tiles); // Zaznaczamy je na planszy
    }
	      
  // Jeżeli pionek nie istnieje w danym miejscu (czyli kliknięto na puste pole),
  // to znaczy, że jest to ruch docelowy (czyli należy pionek przesunąć):
  if(!ptr)
    {
      // Jeżeli pionek jest poprawnie zaznaczony
      if(board.getPawn(selected))
	{
	  // Pomocnicza flaga
	  bool move_is_possible = false;
	  
	  // Jeżeli możliwe jest bicie
	  if(board.isPossibleBeating(selected))
	    {
	      // Pobieramy listę możliwych bić
	      std::list<Movement> beatings = board.getPossibleBeatings(selected);

	      // Jeżeli gracz próbuje bić, zezwól na ruch (czyli bicie jest obowiązkowe)
	      if(find(beatings.begin(), beatings.end(), Movement(selected, position)) != beatings.end()) move_is_possible = true;
	    }

	  // Jeżeli nie jest możliwe bicie, to zezwól na ruch
	  else move_is_possible = true;
	    
	  // Jeżeli zezwolono na ruch
	  // przesuwamy pionek o ile to możliwe (kliknięte miejsce = position jest naszym docelowym kafelkiem)
	  if(move_is_possible && movePawn(Movement(selected, position)))
	    {
	      // Ustaw sekwencję ruchów
	      movements_sequence = true;
	      
	      // Jeżeli się udało, to aktualizujemy pozycję zaznaczonego pionka
	      selected = position;
	      
	      // Jeżeli już nie ma możliwości bicia (bicie obowiązkowe), kończymy turę
	      if(!board.isPossibleBeating(selected))
		{
		  // Kończymy sekwencję ruchów
		  movements_sequence = false;
		  
		  // Odznaczamy pionek
		  board.getPawn(selected)->deselect();

		  // Odznaczamy kafelki (EXPERIMENTAL)
		  board.deselectTiles();
		  
		  // i kończymy turę
		  round = getAIColor();
		}

	      // W przeciwnym razie zaznaczamy na mapie dozwolone kafelki
	      else
		{
		  board.deselectTiles();
		  std::list<Vector> possible_tiles; // Lista dozwolonych kafelków
		  for(const auto& m: board.getPossibleMovements(selected)) // Pobieramy dozwolone kafelki docelowe z dozwolonych ruchów
		    possible_tiles.push_back(m.end);
		  board.selectTiles(possible_tiles); // Zaznaczamy je na planszy
		}
			      
	    }
	}
    }
}

void Game::eventHandler()
{
  // Kontener na zdarzenia
  sf::Event event;

  // Kolejka zdarzeń
  while(window.pollEvent(event))
    {
      // Obsługa zamykania okna gry
      if(event.type == sf::Event::Closed) window.close();

      // Obsługa myszy
      if(event.type == sf::Event::MouseButtonPressed)
	{
	  // Lewy klawisz
	  if(event.mouseButton.button == sf::Mouse::Left)

	    // Wykonaj turę gracza
	    executePlayerRound(sf::Vector2f(event.mouseButton.x, event.mouseButton.y));
	    
	}
    }
}

void Game::loop()
{
  // Nieskończona pętla główna gry
  while(window.isOpen())
    {
      // Przechwytywanie zdarzeń
      eventHandler();

      // Czyszczenie okna
      window.clear(sf::Color::Black);

      // Rysowanie planszy
      board.draw(window);

      // Rysuj HUD
      drawHUD();
      
      // Wyświetlenie ekranu
      window.display();
      
      // Jeżeli teraz tura należy do AI
      if(round == getAIColor())
	{
	  // Ruch AI
	  movePawn(minimax.minimax(board));
	  	  
	  // Ustaw turę na gracza
	  round = getPlayerColor();
	}
    }
}

void Game::drawHUD()
{
  sf::Font font; font.loadFromFile("res/arial.ttf");
  
  std::stringstream player_score_ss; player_score_ss << "Gracz: " << player_score;
  std::stringstream ai_score_ss; ai_score_ss << "AI: " << ai_score;
  
  sf::Text player_score_text(player_score_ss.str(), font);
  sf::Text ai_score_text(ai_score_ss.str(), font);
  
  player_score_text.setCharacterSize(24);
  player_score_text.setColor(sf::Color::White);
  player_score_text.setPosition(sf::Vector2f(10, TILES_COUNT*TILE_SIZE));

  ai_score_text.setCharacterSize(24);
  ai_score_text.setColor(sf::Color::White);
  ai_score_text.setPosition(sf::Vector2f(TILES_COUNT*TILE_SIZE - 70, TILES_COUNT*TILE_SIZE));
  
  window.draw(player_score_text);
  window.draw(ai_score_text);
}

