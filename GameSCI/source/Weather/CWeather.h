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
	///Klasa reprezentuje menad¿era zjawisk pogodowych
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
		///Metoda zwraca wartoœæ k¹ta - pozorny obieg Ÿród³a œwiat³a wokó³ sceny
		///
		float GetDegree();

		///Metoda ustawia wartoœæ k¹ta - pozorny obieg Ÿród³a œwiat³a wokó³ sceny
		///
		///@param degree - k¹t
		///
		void SetDegree(float degree);

		///
		///Metoda zwraca czas aktualizacji wartoœci k¹ta padania Ÿród³a œwiat³a wokó³ sceny
		///
		float GetShadowTime();

		///Metoda ustawia czas aktualizacji wartoœci k¹ta padania Ÿród³a œwiat³a wokó³ sceny
		///
		///@param shadow_time - czas
		///
		void SetShadowTime(float shadow_time);

		///
		///Wirtualna metoda aktualizuje obiekty w kontenerze
		///
		///@param secondsPassed - up³ywaj¹cy czas
		///
		virtual void FrameStarted(float secondsPassed);

		///
		///Metoda zwraca kolor i nasycenie cienia w zale¿noœci od pory dnia
		///
		inline const sf::Color& GetWeatherShadowColor() const { return m_color_shadow; }

		///
		///Metoda ustawia kolor i nasycenie cienia w zale¿noœci od pory dnia
		///
		///@param &color_shadow - sta³a referencja na obiekt klasy sf::Color
		///
		inline void SetWeatherShadowColor(const sf::Color& color_shadow) { m_color_shadow = color_shadow; }

	protected:

		///
		///Wirtualna metoda czyszcz¹ca singleton
		///
		virtual void Cleanup();

	private:

		float				m_degree;				//wartoœæ k¹ta obiegu œwiat³a
		float				m_shadow_time;			//czas obiegu s³oñca - pora dzieñ - noc
		sf::Color			m_color_shadow;			//kolor cienia w zale¿noœci od pory dnia
		float				m_elapsed_time;			//up³ywajacy czas

		static sf::Color	m_default_color_shadow;	//kolor cienia w zale¿noœci od pory dnia
	};
}//weather
#endif //H_WEATHER_SCI
