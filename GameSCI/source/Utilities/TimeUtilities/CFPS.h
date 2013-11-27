/*
 _____________________________________
| CFPS.h - definicja klasy.  		  |
| SCI - December 2009.                |
|_____________________________________|

*/

#ifndef H_FPS_SCI
#define H_FPS_SCI

#include <SFML/System/Clock.hpp>

///
///Klasa reprezentuje interfejs obliczaj�cy FPS (Frame Per Secound)
///
class CFPS
{
public:

	///
	///Konstruktor domy�lny
	///
	CFPS();

	///
	///Destruktor
	///
	~CFPS();

	///
	///Metoda zwraca wyliczon� ilo�c FPS
	///
	int GetFPS();

	///
	///Metoda aktualizuje wyliczenia FPS
	///
	void UpdateFPS();

private:

	int			m_frame;	//ilo�� klatek
	int			m_fps;		//wyliczana ilo�� klatek	
	sf::Clock	m_clock;	//zegar - sf::Clock
};
#endif //H_FPS_SCI

