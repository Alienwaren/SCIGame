/*
 ___________________________________
| CClock.cpp - implementacja klasy. |
| SCI - May 2013.                   |
|___________________________________|

*/

#include "CClock.h"

template<> CClock * CSingleton<CClock>::m_singleton = 0;

//Konstruktor
CClock::CClock()
:
	m_time			(0.0f),
	m_fps			(0.0f),
	m_frames		(0),
	m_is_paused		(true)//na wszelki wypadek w³¹czam zegar w konstruktorze
{
	m_clock.restart();
}

//Destruktor wirtualny
CClock::~CClock()
{
	m_time			= 0.0f;
	m_fps			= 0.0f;
	m_frames		= 0;
	m_is_paused		= false;
	//m_clock		not edit
}

//Metoda zwraca up³ywaj¹cy czas pobierany z zegara
float CClock::GetElapsedTime()
{
	return m_clock.getElapsedTime().asSeconds();
}

//Metoda zwraca iloœæ klatek na sekundê
float CClock::GetFPS() const
{
	return m_fps;
}

//Metoda zwraca œredni¹ iloœæ klatek na sekundê
float CClock::GetAverageFPS() const
{
	return (float) m_frames/m_time;
}

//Metoda zwraca licznik klatek
unsigned int CClock::GetFramesCount() const
{
	return m_frames;
}

//Metoda zwraca czas jaki up³yn¹³ od zainicjowania zegara
float CClock::GetTotalTime() const
{
	return m_time;
}

//Metoda zwraca czas systemowy
time_t CClock::GetTime()
{
	return time(0);
}

//Metoda zwraca obiekt zegara
clock_t CClock::GetClock()
{
	return clock();
}

//Metoda generuje znacznik czasu w formacie std::string (yyyy-mm-dd-hh-mm-ss)
const std::string CClock::GenerateTimestamp() 
{
	static char buff[15] = { 0 };	//tablica char - bufor przechowuj¹cy czas systemowy
									//yyyymmddHHMMSS + NULL == 15
	static struct tm * timeinfo;	//wskaŸnik na strukturê przechowuj¹c¹ czas systemowy

	time_t t = time (NULL);			//czas systemowy
	timeinfo = localtime(&t);		//uzupe³niamy strukturê czasu systemowego

	//castujemy czas na string
	strftime(buff, sizeof(buff)/sizeof(buff[0]), "%Y%m%d%H%M%S", timeinfo);
	return std::string(buff);		//zwracamy czas jako std::string
}

//Metoda wstrzymuje zegar
void CClock::Pause(void)
{
	if (!m_is_paused)
	{
		m_is_paused = true;
		m_time += m_clock.getElapsedTime().asSeconds();
	}
}

//Metoda uruchamia zegar
void CClock::Start(void)
{
	if (m_is_paused)
	{
		m_clock.restart();
		m_is_paused = false;
	}
}

//Metoda resetuje zegar z parametrem, aby po resecie zegar chodzi³ lub nie
void CClock::Reset(bool paused)
{
	m_is_paused = paused;
	m_time = 0.f;
	m_clock.restart();
}

//Metoda aktualizuje stan obiektu - wywo³ywana raz na klatkê
void CClock::Update()
{
	//w celu unikniêcia mini-b³êdów
	static float tmp;

	tmp = m_clock.getElapsedTime().asSeconds();
	m_clock.restart();

	m_time += tmp;
	m_fps = 1.f / tmp;
	++m_frames;
}
