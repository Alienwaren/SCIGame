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
														//co sekundê aktualizacja k¹ta...
		m_color_shadow		(m_default_color_shadow),	//na sztywno, ale klasa mo¿e aktualizowaæ
														//parametr kana³u alpha - nasycenie cienie
														//w zale¿noœci od pory dnia...
		m_elapsed_time		(0.0f)
	{
		printf("CWeather::CWeather()\n");
		gGame.AddFrameListener(this);	//dodajemy do kontenera wskaŸnik na ten obiekt
										//celem aktualizacji jego stanu
										//i aktualizujemy logikê
										//czyli metoda FrameStarted(float secondsPassed),
										//(aktualizacja k¹ta) - wirtualne s³oñce (ruchomy cieñ)
	}

	//Destruktor
	CWeather::~CWeather(void)
	{
		m_degree			= 0.0f;
		m_shadow_time		= 0.0f;
		//m_color_shadow	not edit
		m_elapsed_time		= 0.0f;
	}

	//Metoda zwraca wartoœæ k¹ta - pozorny obieg Ÿród³a œwiat³a wokó³ sceny
	float CWeather::GetDegree()
	{
		return m_degree;
	}

	//Metoda ustawia wartoœæ k¹ta - pozorny obieg Ÿród³a œwiat³a wokó³ sceny
	void CWeather::SetDegree(float degree)
	{
		m_degree = degree;
	}

	//Metoda zwraca czas aktualizacji wartoœci k¹ta padania Ÿród³a œwiat³a wokó³ sceny
	float CWeather::GetShadowTime()
	{
		return m_shadow_time;
	}

	//Metoda ustawia czas aktualizacji wartoœci k¹ta padania Ÿród³a œwiat³a wokó³ sceny
	void CWeather::SetShadowTime(float shadow_time)
	{
		m_shadow_time = shadow_time;
	}

	//Wirtualna metoda aktualizuje obiekty w kontenerze
	void CWeather::FrameStarted(float secondsPassed)
	{
		m_elapsed_time += secondsPassed;//zliczanie czasu

		//Obliczanie przesuniêcia cienia w czasie rzeczywistym
		if (m_elapsed_time > m_shadow_time)
		{
			m_degree += 0.01f;			//docelowo mo¿na dane pogodowe
										//³adowaæ z xml (np. weather_config.xml)
			if (m_degree >= 360.f)		//jeœli wykonano pe³ny obieg zerujemy k¹t
				m_degree = 0.f;
			m_elapsed_time = 0.0f;		//zerujê up³yw czasu
		}
		
		//to do...
		//wartoœæ kana³u alpha mo¿na uzale¿niæ od wartoœci k¹ta przyk³adowo na zasadzie:
		//gdy Ÿród³o œwiat³a (s³oñce, gwiazda, etc.) jest w zenicie, to cieñ
		//mo¿e mieæ wiêksze nasycenie
		//Ka¿dy, kto zaimpementuje pomys³ uatrakcyjniaj¹cy grê, otrzyma dodatkow¹ ocenê
		
		//m_color_shadow		//kana³ alpha - nasycenie cienie w zale¿noœci od pory dnia
								//pora dnia to wysokoœæ po³o¿enia (s³oñca, gwiazdy, etc.)
								//scena mo¿e mieæ wiele (s³oñc, gwiazd, etc.), zatem
								//obiekt mo¿e mieæ wiele cieniów,
								//lub mo¿na zmieniaæ kolor rzucanego cienie
								//pomys³ów mo¿e byæ nieskoñczenie wiele...
	}

	//Wirtualna metoda czyszcz¹ca singleton
	void CWeather::Cleanup()
	{
		printf("CWeather::Cleanup()\n");
		printf("CWeather::Cleanup() done...\n");
	}
}//namespace weather
//Nadanie wartoœci sta³ym sk³adowum statycznym
sf::Color weather::CWeather::m_default_color_shadow = sf::Color(0,0,0,82);	//pocz¹tkowa wartoœæ koloru i nasycenia cienia
																			//w zale¿noœci od pory dnia
