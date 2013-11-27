/*
 ______________________________________
| CCPausableClock.h - definicja klasy. |
| SCI - January 2009.                  |
|______________________________________|

*/
#ifndef H_PAUSABLE_CLOCK_SCI
#define H_PAUSABLE_CLOCK_SCI

#include <SFML/System.hpp>

///
///Klasa reprezentuje prosty zegar. Opakowanie klasy sf::Clock
///
class CPausableClock
{
	public :

	///
	///Kosnstruktor domyœlny
	///
	CPausableClock(bool paused = false)
	:
		m_is_paused(paused),
		m_time(0.f),
		m_clock()
	{
	}

	///
	///Metoda wstrzymuje zegar
	///
	void Pause(void)
	{
		if (!m_is_paused)
		{
			m_is_paused = true;
			m_time += m_clock.getElapsedTime().asSeconds();
		}
	}

	///
	///Metoda uruchamia zegar
	///
	void Start(void)
	{
		if (m_is_paused)
		{
			m_clock.restart();
			m_is_paused = false;
		}
	}

	///
	///Metoda zwraca czas
	///
	float GetElapsedTime(void) const
	{
		if (!m_is_paused)
			return m_time + m_clock.getElapsedTime().asSeconds();
		else
			return m_time;
	}

	///
	///Metoda resetuje zegar z parametrem, aby po resecie zegar chodzi³ lub nie
	///
	void Reset(bool paused = false)
	{
		m_is_paused = paused;
		m_time = 0.f;
		m_clock.restart();
	}
	
	private :
		bool m_is_paused;		//tryb pracy zegara
		float m_time;			//up³yw czasu
		sf::Clock m_clock;		//klasa zegara
};

#endif //H_PAUSABLE_CLOCK_SCI


