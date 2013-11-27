/*
 ____________________________________
| CWeather.h - definicja klasy.      |
| SCI - October 2010.                |
|____________________________________|

*/

#ifndef H_WEATHER_SCI
#define H_WEATHER_SCI

#include "../Utilities/Singleton/CSingleton.h"
#include "../Game/Listener/IFrameListener.h"
#include <SFML/Graphics/Color.hpp>

using namespace listener;

#define gWeather CWeather::GetSingleton()

namespace weather
{
	///
	///Klasa reprezentuje menad�era zjawisk pogodowych
	///
	class CWeather : public CSingleton<CWeather>, public IFrameListener
	{
	public:

		///
		///Konstruktor
		///
		CWeather(void);

		///
		///Destruktor
		///
		~CWeather(void);

		///
		///Metoda zwraca warto�� k�ta - pozorny obieg �r�d�a �wiat�a wok� sceny
		///
		float GetDegree();

		///Metoda ustawia warto�� k�ta - pozorny obieg �r�d�a �wiat�a wok� sceny
		///
		///@param degree - k�t
		///
		void SetDegree(float degree);

		///
		///Metoda zwraca czas aktualizacji warto�ci k�ta padania �r�d�a �wiat�a wok� sceny
		///
		float GetShadowTime();

		///Metoda ustawia czas aktualizacji warto�ci k�ta padania �r�d�a �wiat�a wok� sceny
		///
		///@param shadow_time - czas
		///
		void SetShadowTime(float shadow_time);

		///
		///Wirtualna metoda aktualizuje obiekty w kontenerze
		///
		///@param secondsPassed - up�ywaj�cy czas
		///
		virtual void FrameStarted(float secondsPassed);

		///
		///Metoda zwraca kolor i nasycenie cienia w zale�no�ci od pory dnia
		///
		inline const sf::Color& GetWeatherShadowColor() const { return m_color_shadow; }

		///
		///Metoda ustawia kolor i nasycenie cienia w zale�no�ci od pory dnia
		///
		///@param &color_shadow - sta�a referencja na obiekt klasy sf::Color
		///
		inline void SetWeatherShadowColor(const sf::Color& color_shadow) { m_color_shadow = color_shadow; }

	protected:

		///
		///Wirtualna metoda czyszcz�ca singleton
		///
		virtual void Cleanup();

	private:

		float				m_degree;				//warto�� k�ta obiegu �wiat�a
		float				m_shadow_time;			//czas obiegu s�o�ca - pora dzie� - noc
		sf::Color			m_color_shadow;			//kolor cienia w zale�no�ci od pory dnia
		float				m_elapsed_time;			//up�ywajacy czas

		static sf::Color	m_default_color_shadow;	//kolor cienia w zale�no�ci od pory dnia
	};
}//weather
#endif //H_WEATHER_SCI
