#include "../inc/game.hh" 

Game::Game(Color player, int ai)
:
game_state(GS_RUNNING),                        // Stan gry
selected(TILES_COUNT+1, TILES_COUNT+1),        // Brak zaznaczenia
player_color(player),                          // Kolor gracza
round(CL_WHITE),                               // Pierwszy ruch mają białe pionki
player_score(0),                               // Wyzerowana ilość punktów gracza
ai_score(0),                                   // Wyzerowana ilość punktów AI
minimax(ai, getAIColor())                      // Poziom AI oraz kolor AI

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
	// Lista możliwych ruchów
	std::list<Movement> possible_movements = board.getPossibleGlobalMovements(round);

	// Jeżeli ruch jest niemożliwy, zwróć false
	if(find(possible_movements.begin(), possible_movements.end(), movement) == possible_movements.end()) return false;

	// Jeżeli jest to bicie
	if((movement.getVector() == Vector(-2, -2)) || 		// Możliwości bicia zwykłego pionka
			(movement.getVector() == Vector(-2, 2))  ||
			(movement.getVector() == Vector(2, -2))  ||
			(movement.getVector() == Vector(2, 2)))
		killPawn(movement.begin + movement.getVector()/2); // zbij zabijanego pionka

	// Wykonaj ruch i zwróć sukces, jeśli się powiodło
	return board.movePawn(movement);
}

void Game::executePlayerRound(sf::Vector2f mouse_position)
{
	// Konwersja pozycji myszy na współrzędne kafelka
	Vector position(mouse_position);

	// Pobieramy informacje o pionku(lub jego braku) z interesującego nas pola
	Pawn* ptr = board.getPawn(position);

	// Jeżeli tura należy do gracza, pionek istnieje i należy do gracza
	if((round == getPlayerColor()) && ptr && (ptr->getColor() == getPlayerColor()))
	{
		// Odznaczamy wszystkie zaznaczenia
		board.deselectTiles();

		// Zaznaczamy pionek i pobieramy do niego wskaźnik
		ptr = board.selectPawn(Vector(position));

		// Pobieramy jego pozycję i zapisujemy do zmiennej przechowującej zaznaczony pionek
		selected = ptr->getPosition();

		// Jeżeli nie ma możliwości bicia, zaznacz dozwolone kafelki na mapie
		if(!board.arePossibleGlobalBeatings(getPlayerColor()))
		{
			std::list<Vector> possible_tiles; // Lista dozwolonych kafelków
			for(const auto& m: board.getPossibleMovements(selected)) // Pobieramy dozwolone kafelki docelowe z dozwolonych ruchów
				possible_tiles.push_back(m.end);
			board.selectTiles(possible_tiles); // Zaznaczamy je na planszy
		}

		// W przeciwnym wypadku zaznacz tylko bicia
		else
		{
			std::list<Vector> possible_tiles; // Lista dozwolonych kafelków
			for(const auto& m: board.getPossibleGlobalBeatings(getPlayerColor())) // Pobieramy dozwolone kafelki docelowe z dozwolonych bić
				possible_tiles.push_back(m.end);
			board.selectTiles(possible_tiles); // Zaznaczamy je na planszy
		}

	}

	// Jeżeli pionek nie istnieje w danym miejscu (czyli kliknięto na puste pole),
	// to znaczy, że jest to ruch docelowy (czyli należy pionek przesunąć):
	if(!ptr)
	{
		// Tworzymy ruch z zaznaczonych pozycji
		Movement m(selected, position);

		// Jeżeli pionek jest poprawnie zaznaczony
		if(board.getPawn(selected))
		{
			// Przesuwamy pionek o ile to możliwe (kliknięte miejsce = position jest naszym docelowym kafelkiem)
			if(movePawn(m))
			{
				// Jeżeli się udało, to aktualizujemy pozycję zaznaczonego pionka
				selected = position;

				// Odznaczamy pionek
				board.getPawn(selected)->deselect();

				// Odznaczamy kafelki
				board.deselectTiles();

				// Dorzucamy ruch na stos
				movements_list.push_back(m);

				// i kończymy turę
				round = getAIColor();
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
			{
				// Jeżeli gra jest "w trakcie gry", wykonaj turę gracza
				if(game_state == GS_RUNNING) executePlayerRound(sf::Vector2f(event.mouseButton.x, event.mouseButton.y));

				// W przeciwnym wypadku zamknij okno
				else window.close();
			}
		}
	}
}

void Game::loop()
{
	// Nieskończona pętla główna gry
	while(window.isOpen())
	{
		// Jeżeli gra jest "w trakcie gry"
		if(game_state == GS_RUNNING)
		{
			// Jeżeli teraz tura należy do AI
			if(round == getAIColor())
			{
				// Pobieramy najlepszy ruch AI
				Movement ai_movement = minimax.getBestMovement(board);

				// Wykonujemy go
				movePawn(ai_movement);

				// I zaznaczamy na mapie (ułatwienie dla gracza)
				board.selectMovement(ai_movement);

				// Ustaw turę na gracza
				round = getPlayerColor();

			}

			// Aktualizuj stan gry
			gameUpdate();
		}

		// Przechwytywanie zdarzeń
		eventHandler();

		// Czyszczenie okna
		window.clear(sf::Color::Black);

		// Rysowanie planszy
		board.draw(window);

		// Rysuj HUD
		drawHUD();

		// Jeżeli gra się zakończyła ...
		if(game_state == GS_WIN || game_state == GS_LOSS) displayTheEnd(); // ... wyświetlamy ekran końcowy

		// Wyświetlenie ekranu
		window.display();
	}
}

void Game::drawHUD()
{
	// Ilość punktów gracza i AI

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

void Game::gameUpdate()
{
	// Promuj odpowiednie pionki na damki
	board.upgrade();

	// Sprawdź stan gry
	if(getPlayerColor() == CL_WHITE)
	{
		if(!board.getNumberOfBlackPawns()) game_state = GS_WIN;
		if(!board.getNumberOfWhitePawns()) game_state = GS_LOSS;
	}
	else
	{
		if(!board.getNumberOfBlackPawns()) game_state = GS_LOSS;
		if(!board.getNumberOfWhitePawns()) game_state = GS_WIN;
	}

	// Jeżeli jest to już koniec gry
	if(game_state == GS_WIN || game_state == GS_LOSS)
	{
		// to odznacz wszystkie pola
		board.deselectTiles();

		// i zapisz stan gry do pliku
		saveState(DEFAULT_STATE_FILE);
	}
}

void Game::displayTheEnd()
{
	// Przyciemniony ekran
	sf::RectangleShape shadow(sf::Vector2f(TILES_COUNT*TILE_SIZE, TILES_COUNT*TILE_SIZE));
	shadow.setFillColor(sf::Color(0, 0, 0, 140));
	shadow.setPosition(0, 0);
	window.draw(shadow);

	// Napis "Zwycięstwo"/"Porażka"
	sf::Font font; font.loadFromFile("res/arial.ttf");
	sf::Text text = (game_state == GS_WIN)?sf::Text(L"Zwycięstwo", font):sf::Text(L"Porażka", font);
	text.setCharacterSize(60);
	text.setColor(sf::Color::White);
	text.setPosition(WINDOW_WIDTH/2-140, WINDOW_HEIGHT/2-60);
	window.draw(text);

}

bool Game::saveState(std::string filename)
{
	// Otwieramy plik
	std::fstream file(filename, std::ios::out);

	// Jeżeli się nie udało - false;
	if(!file.good()) return false;

	// Zapisujemy całą liste dotychczasowych ruchów
	int i = 0;
	for(auto m: movements_list)
		file << ++i << "# " << (!(i%2)?"Biały":"Czarny") << ":\t(" << m.begin.x << ", " << m.begin.y << ")\t->\t(" << m.end.x << ", " << m.end.y << ")" << std::endl;
	return true;
}
