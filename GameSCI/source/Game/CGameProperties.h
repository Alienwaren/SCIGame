/*
 ______________________________________________
| CGameProperties.h - definicja klasy.         |
| SCI -  July 2012.                            |
|______________________________________________|

*/

#ifndef H_GAME_PROPERTIES_SCI
#define H_GAME_PROPERTIES_SCI

#include "../Utilities/Singleton/CSingleton.h"
#include "../XML/CXml.h"

#define gGameProperties CGameProperties::GetSingleton()

using namespace xml;

namespace game
{
	///
	///Klasa reprezentuje opcje gry
	///
	class CGameProperties : public CSingleton<CGameProperties>
	{
	public:

		///
		///Konstruktor domyœlny
		///
		CGameProperties(void);

		///
		///Konstruktor kopiuj¹cy
		///
		///@param CGamePropertiesCopy - parametr - obiekt klasy CGamePropertiesCopy
		///
		CGameProperties(const CGameProperties& CGamePropertiesCopy);

		///
		///Destruktor
		///
		~CGameProperties(void);

		///
		///Metoda zwraca szerokoœæ okna
		///
		unsigned int GetWidth();

		///
		///Metoda ustawia szerokoœæ okna
		///
		///@param width - szerokoœæ okna
		///
		void SetWidth(unsigned int width);

		///
		///Metoda zwraca wysokoœæ okna
		///
		unsigned int GetHeight();

		///
		///Metoda ustawia wysokoœæ okna
		///
		///@param height - wysokoœæ okna
		///
		void SetHeight(unsigned int height);

		///
		///Metoda zwraca g³ebiê kolorów
		///
		unsigned int GetBitsPerPixel();

		///
		///Metoda ustawia g³êbiê kolorów
		///
		///@param bits_per_pixel_depth - g³êbia kolorów
		///
		void SetBitsPerPixel(unsigned int bits_per_pixel_depth);

		///
		///Metoda zwraca tryb pe³noekranowy
		///
		bool IsFullscreen();

		///
		///Metoda ustawia tryb pe³noekranowy
		///
		///@param fullscreen - flaga trybu pe³noekranowego
		///
		void SetFullscreen(bool fullscreen);

		///
		///Metora zwraca tryb synchronizacji pionowej
		///
		bool IsVSync();

		///
		///Metoda ustawia tryb synchronizacji pionowej
		///
		///@param vsync - flaga trybu synchronizacji pionowej
		///
		void SetVSync(bool vsync);

		///
		///Metoda zwraca g³oœnoœæ dŸwiêku
		///
		float GetSoundVolume();

		///
		///Metoda ustawia g³oœnoœæ dŸwiêku
		///
		///@param sound_volume - g³oœnoœæ dŸwiêku
		///
		void SetSoundVolume(float sound_volume);

		///
		///Metoda zwraca g³oœnoœæ muzyki
		///
		float GetMusicVolume();

		///
		///Metoda ustawia g³oœnoœæ muzyki
		///
		///@param music_volume - g³oœnoœæ muzyki
		///
		void SetMusicVolume(float music_volume);

		///
		///Metoda zwraca nazwê okna
		///
		const std::string GetWindowName() const;

		///
		///Metoda ustawia nazwê okna
		///
		///@param & windows_name - nazwa okna
		///
		const void SetWindowName(std::string &windows_name);

		///
		///Metoda ³aduj¹ca dane
		///
		///@param &name - sta³a referencja na std::string
		///
		bool Load(const std::string &name);

		///
		///Metoda ³aduj¹ca dane z xml
		///
		///@param &xml - referencja na obiekt klasy CXml
		///
		bool Load(CXml &xml);

		///
		///Metoda tworzy okno
		///
		void UpdateWindow();

	protected:

		///
		///Wirtualna metoda czyszcz¹ca singleton
		///
		virtual void Cleanup();

	private:

		unsigned int	m_width;				//szerokoœæ okna
		unsigned int	m_height;				//wysokoœæ okna
		unsigned int	m_bits_per_pixel_depth;	//g³êbia kolorów - poczytaæ www.sfml-dev.org
		bool			m_fullscreen;			//flaga - FullScreen
		bool			m_vsync;				//flaga - synchronizacja pionowa - poczytaæ www.sfml-dev.org
		float			m_sound_volume;			//g³oœnoœæ dŸwiêku
		float			m_music_volume;			//g³oœnoœæ muzyki
		std::string		m_windows_name;			//nazwa okna

	};
}//namespace game
#endif //H_GAME_PROPERTIES_SCI