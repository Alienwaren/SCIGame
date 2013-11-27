/*
 _____________________________________
| CFPS.cpp - implementacja klasy.	  |
| SCI - December 2009.                |
|_____________________________________|

*/

#include "CFPS.h"

// Konstruktor domyœlny
CFPS::CFPS()
:
	m_frame(0),
	m_fps(0)
{
	m_clock.restart();
}

//Destruktor
CFPS::~CFPS()
{
	m_frame;
	m_fps;
}

//Metoda zwraca wyliczon¹ iloœc FPS
int CFPS::GetFPS()
{
	return m_fps;
}

//Metoda aktualizuje wyliczenia FPS
void CFPS::UpdateFPS()
{
	if(m_clock.getElapsedTime().asSeconds() >= 1.f)
	{
		m_fps = m_frame;
		m_frame = 0;
		m_clock.restart();
	}
	m_frame++;
}
