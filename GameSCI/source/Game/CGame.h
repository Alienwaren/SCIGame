/*
 __________________________________
| CGame.h - class definition       |
| SCI - July 2012.                 |
|__________________________________|

*/

#ifndef H_GAME_SCI
#define H_GAME_SCI

#include <SFML/Graphics.hpp>
#include "../Utilities/Singleton/CSingleton.h"
#include "../Utilities/TimeUtilities/CPausableClock.h"
#include "../Utilities/TimeUtilities/CClock.h"
#include "../Utilities/TimeUtilities/CFPS.h"
#include "../Utilities/StringUtils/StringUtils.h"
#include "CGameProperties.h"

#include <set>

#define gGame CGame::GetSingleton()

///
///Forward declaration
///
namespace listener
{
	class IFrameListener;
	class IKeyListener;
	class IMouseListener;
}

namespace game
{
	///
	///Klasa reprezentuje okno gry
	///
	class CGame : public CSingleton<CGame>
	{
	public:

		///
		///Konstruktor domy�lny
		///
		CGame(void);

		///
		///Destruktor
		///
		~CGame(void);

		///
		///Metoda zwraca wska�nik na okno gry
		///
		sf::RenderWindow* GetRenderWindow();// {return m_render_window;}

		///
		///Metoda ustawia wska�nik na okno gry
		///
		void SetRenderWindow(sf::RenderWindow* _renderWindow);

		///
		///Metoda uruchamia g��wn� p�tl� gry
		///
		void Run();

		///
		///Metoda aktualizuje stan gry
		///
		///@param dt - delta time
		///
		void Update(float dt);

		///
		///Metoda zwraca referencj� do obiektu klasy sf::Event
		///
		sf::Event& GetGameEvent();

		///
		///Metoda dodaje do zbioru wska�niki obiekt�w aktualizowanych aktualizuj�cych logik�
		///
		///@param *frameListener - wska�nik na obiekt klasy IFrameListener
		///
		void AddFrameListener(listener::IFrameListener* frameListener);
	    
		///
		///Metoda dodaje do zbioru wska�niki obiekt�w aktualizowanych zdarzenia klawiatury
		///
		///@param *keyListener - wska�nik na obiekt klasy IKeyListener
		//
		void AddKeyListener(listener::IKeyListener* keyListener);
		
		///
		///Metoda dodaje do zbioru wska�niki obiekt�w aktualizowanych zdarzenia myszy
		///
		///@param *mouseListener - wska�nik na obiekt klasy IMouseListener
		///
		void AddMouseListener(listener::IMouseListener* mouseListener);

	protected:
		
		///
		///Wirtualna metoda czyszcz�ca singleton
		///
		virtual void Cleanup();

	private:

		std::set<listener::IFrameListener*>	m_frameListeners;		//zbi�r na wska�niki obiekt�w aktualizowanych aktualizuj�cymi logik�
		std::set<listener::IKeyListener*>	m_keyListeners;			//zbi�r na wska�niki obiekt�w aktualizowanych zdarzenia klawiatury
		std::set<listener::IMouseListener*>	m_mouseListeners;		//zbi�r na wska�niki obiekt�w aktualizowanych zdarzenia myszy

		sf::RenderWindow*			m_render_window;		//wska�nik na renderowany obszar okna
		CPausableClock				m_clock;				//zegar
		CFPS						FPS_Game;				//klasa diagnostyczna FPS
		sf::Text					fps_text;				//obiekt do diagonostyki - wy�wietlenie FPT...

		sf::Event					m_event;				//zdarzenia
		
		void mainLoop				();						//p�tla g��wna gry
		const void initSingletons	();						//metoda inicjuje singletny

	};
}//namespace game
#endif //H_GAME_SCI