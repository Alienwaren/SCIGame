/*
 ___________________________________
| CClock.h - definicja klasy.       |
| SCI - May 2013.                   |
|___________________________________|

*/

#ifndef H_CLOCK_SCI
#define H_CLOCK_SCI

#include "../Singleton/CSingleton.h"
#include <SFML/System/Clock.hpp>
#include <ctime>
#include <string>

#define gClock CClock::GetSingleton()

///
///Klasa reprezentuj¹ca prosty zegar
///
class CClock : public CSingleton< CClock >
{

public:

	///
	///Konstruktor
	///
	CClock();

	///
	///Destruktor wirtualny
	///
	virtual ~CClock();

	///
	///Metoda zwraca up³ywaj¹cy czas pobierany z zegara
	///
	float GetElapsedTime();

	///
	///Metoda zwraca iloœæ klatek na sekundê
	///
	float GetFPS() const;
    
	///
	///Metoda zwraca œredni¹ iloœæ klatek na sekundê
	///
	float GetAverageFPS() const;
    
    ///
	///Metoda zwraca licznik klatek
	///
	unsigned int GetFramesCount() const;
    
	///
	///Metoda zwraca czas jaki up³yn¹³ od zainicjowania zegara
	///
	float GetTotalTime() const;

	///
	///Metoda zwraca czas systemowy
	///
	time_t GetTime();

	///
	///Metoda zwraca obiekt zegara
	///
	clock_t GetClock();

	///
	///Metoda generuje znacznik czasu w formacie std::string (yyyy-mm-dd-hh-mm-ss)
    ///
	const std::string GenerateTimestamp(); 

	///
	///Metoda wstrzymuje zegar
	///
	void Pause(void);

	///
	///Metoda uruchamia zegar
	///
	void Start(void);

	///
	///Metoda resetuje zegar z parametrem, aby po resecie zegar chodzi³ lub nie
	///
	void Reset(bool paused = false);

	///
	///Metoda aktualizuje stan obiektu - wywo³ywana raz na klatkê
	///
	void Update();

private:
    
	float					m_time;			//zmienna akumulacji czasu
	float					m_fps;			//FPS - iloœæ klatek na sekundê
	unsigned int			m_frames;		//iloœæ klatek - licznik klatek
	bool					m_is_paused;	//tryb pracy zegara
	sf::Clock				m_clock;		//obiekt klasy sf::Clock - zegra taktuj¹cy
};

#endif //H_CLOCK_SCI
