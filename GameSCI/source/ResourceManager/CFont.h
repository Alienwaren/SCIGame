/*
 __________________________________
| CFont.h - definicja klasy.       |
| SCI - October 2013.              |
|__________________________________|

*/

#ifndef H_FONT_SCI
#define H_FONT_SCI

#include <SFML/Graphics/Font.hpp>
#include "IResource.h"

namespace resource
{
	///
	///Klasa reprezetuje opakowanie obiektu klasy sf::Font
	///
	class CFont: public IResource, public sf::Font
	{
	public:
		
		///
		///Konstruktor
		///
		CFont(void);

		///
		///Destruktor
		///
		~CFont(void);

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
#endif //H_FONT_SCI
