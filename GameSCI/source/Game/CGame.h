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
		///Konstruktor domyœlny
		///
		CGame(void);

		///
		///Destruktor
		///
		~CGame(void);

		///
		///Metoda zwraca wskaŸnik na okno gry
		///
		sf::RenderWindow* GetRenderWindow();// {return m_render_window;}

		///
		///Metoda ustawia wskaŸnik na okno gry
		///
		void SetRenderWindow(sf::RenderWindow* _renderWindow);

		///
		///Metoda uruchamia g³ówn¹ pêtlê gry
		///
		void Run();

		///
		///Metoda aktualizuje stan gry
		///
		///@param dt - delta time
		///
		void Update(float dt);

		///
		///Metoda zwraca referencjê do obiektu klasy sf::Event
		///
		sf::Event& GetGameEvent();

		///
		///Metoda dodaje do zbioru wskaŸniki obiektów aktualizowanych aktualizuj¹cych logikê
		///
		///@param *frameListener - wskaŸnik na obiekt klasy IFrameListener
		///
		void AddFrameListener(listener::IFrameListener* frameListener);
	    
		///
		///Metoda dodaje do zbioru wskaŸniki obiektów aktualizowanych zdarzenia klawiatury
		///
		///@param *keyListener - wskaŸnik na obiekt klasy IKeyListener
		//
		void AddKeyListener(listener::IKeyListener* keyListener);
		
		///
		///Metoda dodaje do zbioru wskaŸniki obiektów aktualizowanych zdarzenia myszy
		///
		///@param *mouseListener - wskaŸnik na obiekt klasy IMouseListener
		///
		void AddMouseListener(listener::IMouseListener* mouseListener);

	protected:
		
		///
		///Wirtualna metoda czyszcz¹ca singleton
		///
		virtual void Cleanup();

	private:

		std::set<listener::IFrameListener*>	m_frameListeners;		//zbiór na wskaŸniki obiektów aktualizowanych aktualizuj¹cymi logikê
		std::set<listener::IKeyListener*>	m_keyListeners;			//zbiór na wskaŸniki obiektów aktualizowanych zdarzenia klawiatury
		std::set<listener::IMouseListener*>	m_mouseListeners;		//zbiór na wskaŸniki obiektów aktualizowanych zdarzenia myszy

		sf::RenderWindow*			m_render_window;		//wskaŸnik na renderowany obszar okna
		CPausableClock				m_clock;				//zegar
		CFPS						FPS_Game;				//klasa diagnostyczna FPS
		sf::Text					fps_text;				//obiekt do diagonostyki - wyœwietlenie FPT...

		sf::Event					m_event;				//zdarzenia
		
		void mainLoop				();						//pêtla g³ówna gry
		const void initSingletons	();						//metoda inicjuje singletny

	};
}//namespace game
#endif //H_GAME_SCI