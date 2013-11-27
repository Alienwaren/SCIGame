/*
 ____________________________________
| CWeather.cpp - implemetacja klasy  |
| SCI - October 2010.                |
|____________________________________|

*/

#include "CWeather.h"
#include "../Game/CGame.h"

using namespace weather;
using namespace game;

template<> CWeather* CSingleton<CWeather>::m_singleton = 0;

namespace weather
{
	//Konstruktor
	CWeather::CWeather(void)
	:
		m_degree			(0.f),
		m_shadow_time		(1.f),						//na starcie jedna sekunda,
														//co sekund� aktualizacja k�ta...
		m_color_shadow		(m_default_color_shadow),	//na sztywno, ale klasa mo�e aktualizowa�
														//parametr kana�u alpha - nasycenie cienie
														//w zale�no�ci od pory dnia...
		m_elapsed_time		(0.0f)
	{
		printf("CWeather::CWeather()\n");
		gGame.AddFrameListener(this);	//dodajemy do kontenera wska�nik na ten obiekt
										//celem aktualizacji jego stanu
										//i aktualizujemy logik�
										//czyli metoda FrameStarted(float secondsPassed),
										//(aktualizacja k�ta) - wirtualne s�o�ce (ruchomy cie�)
	}

	//Destruktor
	CWeather::~CWeather(void)
	{
		m_degree			= 0.0f;
		m_shadow_time		= 0.0f;
		//m_color_shadow	not edit
		m_elapsed_time		= 0.0f;
	}

	//Metoda zwraca warto�� k�ta - pozorny obieg �r�d�a �wiat�a wok� sceny
	float CWeather::GetDegree()
	{
		return m_degree;
	}

	//Metoda ustawia warto�� k�ta - pozorny obieg �r�d�a �wiat�a wok� sceny
	void CWeather::SetDegree(float degree)
	{
		m_degree = degree;
	}

	//Metoda zwraca czas aktualizacji warto�ci k�ta padania �r�d�a �wiat�a wok� sceny
	float CWeather::GetShadowTime()
	{
		return m_shadow_time;
	}

	//Metoda ustawia czas aktualizacji warto�ci k�ta padania �r�d�a �wiat�a wok� sceny
	void CWeather::SetShadowTime(float shadow_time)
	{
		m_shadow_time = shadow_time;
	}

	//Wirtualna metoda aktualizuje obiekty w kontenerze
	void CWeather::FrameStarted(float secondsPassed)
	{
		m_elapsed_time += secondsPassed;//zliczanie czasu

		//Obliczanie przesuni�cia cienia w czasie rzeczywistym
		if (m_elapsed_time > m_shadow_time)
		{
			m_degree += 0.01f;			//docelowo mo�na dane pogodowe
										//�adowa� z xml (np. weather_config.xml)
			if (m_degree >= 360.f)		//je�li wykonano pe�ny obieg zerujemy k�t
				m_degree = 0.f;
			m_elapsed_time = 0.0f;		//zeruj� up�yw czasu
		}
		
		//to do...
		//warto�� kana�u alpha mo�na uzale�ni� od warto�ci k�ta przyk�adowo na zasadzie:
		//gdy �r�d�o �wiat�a (s�o�ce, gwiazda, etc.) jest w zenicie, to cie�
		//mo�e mie� wi�ksze nasycenie
		//Ka�dy, kto zaimpementuje pomys� uatrakcyjniaj�cy gr�, otrzyma dodatkow� ocen�
		
		//m_color_shadow		//kana� alpha - nasycenie cienie w zale�no�ci od pory dnia
								//pora dnia to wysoko�� po�o�enia (s�o�ca, gwiazdy, etc.)
								//scena mo�e mie� wiele (s�o�c, gwiazd, etc.), zatem
								//obiekt mo�e mie� wiele cieni�w,
								//lub mo�na zmienia� kolor rzucanego cienie
								//pomys��w mo�e by� niesko�czenie wiele...
	}

	//Wirtualna metoda czyszcz�ca singleton
	void CWeather::Cleanup()
	{
		printf("CWeather::Cleanup()\n");
		printf("CWeather::Cleanup() done...\n");
	}
}//namespace weather
//Nadanie warto�ci sta�ym sk�adowum statycznym
sf::Color weather::CWeather::m_default_color_shadow = sf::Color(0,0,0,82);	//pocz�tkowa warto�� koloru i nasycenia cienia
																			//w zale�no�ci od pory dnia
