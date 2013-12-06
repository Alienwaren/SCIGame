/*
 __________________________________
| CGame.cpp - class implementation |
| SCI - July 2012.                 |
|__________________________________|

*/

#include <iostream>
#include "CGame.h"

#include "../ResourceManager/CResourceManager.h"
#include "../ResourceManager/CFont.h"
#include "../Rendering/Animations/CAnimationManager.h"
#include "../Rendering/Drawable/CDrawableManager.h"
#include "../Rendering/Displayable/CDisplayable.h"
#include "../Weather/CWeather.h"
#include "../Factory/CEnemyTemplate.h"
#include "../Logic/CPhysicalManager.h"
#include "../Logic/CLogic.h"

using namespace resource;
using namespace rendering::displayable;
using namespace rendering::animation;
using namespace logic;
using namespace listener;
using namespace game;
using namespace weather;

template<> CGame* CSingleton<game::CGame>::m_singleton = 0;

namespace game
{
	//Konstruktor domy�lny
	CGame::CGame(void)
	:
		m_render_window	(0),
		m_clock			()
	{
		printf("CGame::CGame()\n");
		gGameProperties.Load("data/xml_data/game_config/game_config.xml");
		gGameProperties.UpdateWindow();
		
		m_clock.Reset();
		printf("m_clock.Reset()\n");
	}

	//Destruktor
	CGame::~CGame(void)
	{
		printf("CGame::~CGame()\n");
		Cleanup();
	}

	//Wirtualna metoda czyszcz�ca singleton
	void CGame::Cleanup()
	{
		m_render_window = NULL;
		printf("CGame::Cleanup() done...\n");
	}

	//Metoda zwraca wska�nik na okno gry
	sf::RenderWindow* CGame::GetRenderWindow()
	{
		return m_render_window;
	}

	//Metoda ustawia wska�nik na okno gry
	void CGame::SetRenderWindow(sf::RenderWindow * _render_window)
	{
		m_render_window = _render_window;
		printf("CGame::SetRenderWindow()\n");
	}

	//Metoda uruchamia g��wn� p�tl� gry
	void CGame::Run()
	{
		mainLoop();
	}

	//Metoda aktualizuje stan gry
	void CGame::Update(float dt)
	{
		//aktulizacja listener�w...
		std::set<IFrameListener*>::iterator i;
		for (i = m_frameListeners.begin(); i != m_frameListeners.end(); i++)
			(*i)->FrameStarted( dt );

		//rysujemy obiekty na scenie
		gDrawableManager.DrawFrame();

		//wyliczamy FPS
		FPS_Game.UpdateFPS();
		fps_text.setString("FPS: "+ stringutils::ToString<int>(FPS_Game.GetFPS()));
	}

	//Metoda zwraca referencj� do obiektu klasy sf::Event
	sf::Event& CGame::GetGameEvent()
	{
		return m_event;
	}


	//implementacja metod private:

	//p�tla g��wna gry
	void CGame::mainLoop()
	{
		//r�czna, bezpieczna inicjacja niekt�rych singleton
		initSingletons();

		//jaka� funkcja �aduj�ca na pocz�tku zasoby dla poprawy wydajno�ci...

		//bardzo �le napisane...mo�na poni�sze opakowa� do jakiej� klasy/metody?
		CFont font = *gResourceManager.GetFont("data/fonts/tahoma.ttf");
		fps_text.setString("Zaczynamy");
		fps_text.setFont(font);
		fps_text.setCharacterSize(20);
		fps_text.setColor(sf::Color::Green);
		fps_text.setPosition(10,10);


		//sf::View view(sf::FloatRect(0, 0, 400, 300));
		//sf::View view(sf::FloatRect(0, 0, 1600, 1200));
		//view.move(200,40);
		//view.setCenter(400,300);
		//view.zoom(0.25f);
		//view.rotate(45.f);
		//m_render_window->setView(view);
		
		//�adowanie danych z poziomu CResourceManager'a
		if(gResourceManager.LoadPhysicalTemplate("data/xml_data/units_enemy/gods.xml") == false)
			printf("Data not loaded...\n");
		//tworz� wzorzec fabryczny i inicjuj� go danymi pobramymi z CResourceManager'a uprzednio za�adowane
		CPhysicalTemplate *p_template = gResourceManager.GetPhysicalTemplate("data/xml_data/units_enemy/zombie.xml");
		//wrzorzec drugiego wroga - Alienwaren/Kejczor
		CPhysicalTemplate *p_template2 = gResourceManager.GetPhysicalTemplate("data/xml_data/units_enemy/zombie.xml");

		CPhysicalTemplate *bunnyTemplate = gResourceManager.GetPhysicalTemplate("data/xml_data/units_enemy/deadly_bunny.xml"); // wzorzec Deadly Bunny
		//ten kod jest testowy, bo tworzenie (respawn) obiekt�w b�dzie z poziomu �adowania mapy (level'a)
		CEnemy *p_enemy = gPhysicalManager.CreateEnemy(L"ID_enemy");

		CEnemy *p_enemy2 = gPhysicalManager.CreateEnemy(L"nowyPrzeciwnik"); //pr�ba utworzenia nowego wroga - Alienwaren/Kejczor - SUKCES!

		CEnemy *p_enemy3 = gPhysicalManager.CreateEnemy(L"Deadly Bunny"); /// Deadly bunny - Alienwaren/Kejczor
		//wzorzec wype�niam danymi utworzony obiekt (Physical'a)
		if(p_enemy)
			p_template->Fill(p_enemy);

		if(p_enemy2)
			p_template2->Fill(p_enemy2);

		if(p_enemy3)
			bunnyTemplate->Fill(p_enemy3);

		if(p_enemy)
			p_enemy->setSmoothing(true);

		if(p_enemy2)
			p_enemy->setSmoothing(true);

		if(p_enemy3)
			p_enemy3->setSmoothing(true);
		
		p_enemy->SetPosition(400, 300);
		p_enemy->SetRotationBody(0.f);
	//	p_enemy->SetRotationHead(310);
	//	p_enemy->setAltitude(12);
		p_enemy->SetScale(2.5f);
		p_enemy2->SetScale(1.5f);
		p_enemy2->SetPosition(200,300);
		p_enemy3->SetPosition(100,300);

		//testy...sprawdzi�...jak to dzia�a...
		//p_enemy->SetColorHead(sf::Color::Blue);	
		//p_enemy->SetColorBody(sf::Color::Red);	
		//p_enemy->RestoreColor();				//odzyskujemy oryginalny kolor body and head
		//p_enemy->RestoreColorBody();			//odzyskujemy oryginalny kolor body
		//p_enemy->RestoreColorHead();			//
		printf("CGame::Run()\n");

		while (m_render_window->isOpen())
		{
			//zegar
			float elapsedTime = m_clock.GetElapsedTime();
			m_clock.Reset();

			//mo�na te� skorzysta� z poni�szego zegara...
			//float elapsedTime = gClock.GetElapsedTime();
			//gClock.Update();

			while (m_render_window->pollEvent(m_event))
			{
				if (m_event.type == sf::Event::Closed) //zamykanie okna guziczkiem
				{	
					m_render_window->close();
				}

				else if(m_event.type == sf::Event::KeyPressed && m_event.key.code == sf::Keyboard::Escape) //zamykanie okna escapem
				{
					m_render_window->close();
				}
			}

			m_render_window->clear(sf::Color(255,255,255));

			Update(elapsedTime);				//aktualizacja gry
			m_render_window->draw(fps_text);	//statystyki...

			p_enemy->RotateHead(-0.62f);		//pokaz ku uciesze Ucznia SCI...
												//zobaczymy co Uczniowie SCI
												//zakoduj�...
			
			m_render_window->display();			//wy�wietlenie sceny w oknie
		}
	}

	//Metoda inicjuje singletny
	const void CGame::initSingletons()
	{
		gGame;
		gGameProperties;
		gResourceManager;
		gDrawableManager;
		gAnimationManager;
		gWeather;
		gPhysicalManager;
		gLogic;
	}

	//Metoda dodaje do zbioru wska�niki obiekt�w aktualizowanych aktualizuj�cych logik�
	void CGame::AddFrameListener(listener::IFrameListener* frameListener)
	{
		m_frameListeners.insert(frameListener);
	}

	//Metoda dodaje do zbioru wska�niki obiekt�w aktualizowanych zdarzenia klawiatury
	void CGame::AddKeyListener(listener::IKeyListener* keyListener)
	{
		m_keyListeners.insert(keyListener);
	}

	//Metoda dodaje do zbioru wska�niki obiekt�w aktualizowanych zdarzenia myszy
	void CGame::AddMouseListener(listener::IMouseListener* mouseListener)
	{
		m_mouseListeners.insert(mouseListener);
	}
}//namespace game
