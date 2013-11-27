/*
 ___________________________________
| CSound.h - definicja klasy.       |
| SCI - October 2013.               |
|___________________________________|

*/

#ifndef H_SOUND_SCI
#define H_SOUND_SCI

#include <SFML/Audio/SoundBuffer.hpp>
#include "IResource.h"

namespace resource
{
	///
	///Klasa reprezetuje opakowanie obiektu klasy sf::Texture
	///
	class CSound: public IResource, public sf::SoundBuffer
	{
	public:
		
		///
		///Konstruktor
		///
		CSound(void);

		///
		///Destruktor
		///
		~CSound(void);

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
#endif //H_SOUND_SCI
