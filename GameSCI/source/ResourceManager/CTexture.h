/*
 _____________________________________
| CTexture.h - definicja klasy.       |
| SCI - October 2013.                 |
|_____________________________________|

*/

#ifndef H_TEXTURE_SCI
#define H_TEXTURE_SCI

#include <SFML/Graphics/Texture.hpp>
#include "IResource.h"

namespace resource
{
	///
	///Klasa reprezetuje opakowanie obiektu klasy sf::Texture
	///
	class CTexture: public IResource, public sf::Texture
	{
	public:
		
		///
		///Konstruktor
		///
		CTexture(void);

		///
		///Destruktor
		///
		~CTexture(void);

		///
		///Wirtualna metoda ³aduj¹ca zasób - implementacja
		///
		///@param &file_name - sta³a referencja na nazwê pliku
		///
		bool Load(const std::string &file_name);

		///
		///Wirtualna metoda zwalniaj¹ca zasób
		///
		void Drop();

	};
}//namespace resource
#endif //H_TEXTURE
