/*
 ___________________________________
| CMusic.h - definicja klasy.       |
| SCI - October 2013.               |
|___________________________________|

*/

#ifndef H_MUSIC_SCI
#define H_MUSIC_SCI

#include <SFML/Audio/Music.hpp>
#include "IResource.h"

namespace resource
{
	///
	///Klasa reprezetuje opakowanie obiektu klasy sf::Music
	///
	class CMusic: public IResource, public sf::Music
	{
	public:
		
		///
		///Konstruktor
		///
		CMusic(void);

		///
		///Destruktor
		///
		~CMusic(void);

		///
		///Wirtualna metoda �aduj�ca zas�b - implementacja
		///
		///@param &file_name - sta�a referencja na nazw� pliku
		///
		bool Load(const std::string &file_name);

		///
		///Wirtualna metoda zwalniaj�ca zas�b
		///
		void Drop();

	};
}//namespace resource
#endif //H_MUSIC_SCI
