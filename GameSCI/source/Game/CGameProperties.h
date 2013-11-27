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
		///Konstruktor domy�lny
		///
		CGameProperties(void);

		///
		///Konstruktor kopiuj�cy
		///
		///@param CGamePropertiesCopy - parametr - obiekt klasy CGamePropertiesCopy
		///
		CGameProperties(const CGameProperties& CGamePropertiesCopy);

		///
		///Destruktor
		///
		~CGameProperties(void);

		///
		///Metoda zwraca szeroko�� okna
		///
		unsigned int GetWidth();

		///
		///Metoda ustawia szeroko�� okna
		///
		///@param width - szeroko�� okna
		///
		void SetWidth(unsigned int width);

		///
		///Metoda zwraca wysoko�� okna
		///
		unsigned int GetHeight();

		///
		///Metoda ustawia wysoko�� okna
		///
		///@param height - wysoko�� okna
		///
		void SetHeight(unsigned int height);

		///
		///Metoda zwraca g�ebi� kolor�w
		///
		unsigned int GetBitsPerPixel();

		///
		///Metoda ustawia g��bi� kolor�w
		///
		///@param bits_per_pixel_depth - g��bia kolor�w
		///
		void SetBitsPerPixel(unsigned int bits_per_pixel_depth);

		///
		///Metoda zwraca tryb pe�noekranowy
		///
		bool IsFullscreen();

		///
		///Metoda ustawia tryb pe�noekranowy
		///
		///@param fullscreen - flaga trybu pe�noekranowego
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
		///Metoda zwraca g�o�no�� d�wi�ku
		///
		float GetSoundVolume();

		///
		///Metoda ustawia g�o�no�� d�wi�ku
		///
		///@param sound_volume - g�o�no�� d�wi�ku
		///
		void SetSoundVolume(float sound_volume);

		///
		///Metoda zwraca g�o�no�� muzyki
		///
		float GetMusicVolume();

		///
		///Metoda ustawia g�o�no�� muzyki
		///
		///@param music_volume - g�o�no�� muzyki
		///
		void SetMusicVolume(float music_volume);

		///
		///Metoda zwraca nazw� okna
		///
		const std::string GetWindowName() const;

		///
		///Metoda ustawia nazw� okna
		///
		///@param & windows_name - nazwa okna
		///
		const void SetWindowName(std::string &windows_name);

		///
		///Metoda �aduj�ca dane
		///
		///@param &name - sta�a referencja na std::string
		///
		bool Load(const std::string &name);

		///
		///Metoda �aduj�ca dane z xml
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
		///Wirtualna metoda czyszcz�ca singleton
		///
		virtual void Cleanup();

	private:

		unsigned int	m_width;				//szeroko�� okna
		unsigned int	m_height;				//wysoko�� okna
		unsigned int	m_bits_per_pixel_depth;	//g��bia kolor�w - poczyta� www.sfml-dev.org
		bool			m_fullscreen;			//flaga - FullScreen
		bool			m_vsync;				//flaga - synchronizacja pionowa - poczyta� www.sfml-dev.org
		float			m_sound_volume;			//g�o�no�� d�wi�ku
		float			m_music_volume;			//g�o�no�� muzyki
		std::string		m_windows_name;			//nazwa okna

	};
}//namespace game
#endif //H_GAME_PROPERTIES_SCI