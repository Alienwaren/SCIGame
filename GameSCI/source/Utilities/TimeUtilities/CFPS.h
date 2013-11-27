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
///Klasa reprezentuje interfejs obliczaj¹cy FPS (Frame Per Secound)
///
class CFPS
{
public:

	///
	///Konstruktor domyœlny
	///
	CFPS();

	///
	///Destruktor
	///
	~CFPS();

	///
	///Metoda zwraca wyliczon¹ iloœc FPS
	///
	int GetFPS();

	///
	///Metoda aktualizuje wyliczenia FPS
	///
	void UpdateFPS();

private:

	int			m_frame;	//iloœæ klatek
	int			m_fps;		//wyliczana iloœæ klatek	
	sf::Clock	m_clock;	//zegar - sf::Clock
};
#endif //H_FPS_SCI

