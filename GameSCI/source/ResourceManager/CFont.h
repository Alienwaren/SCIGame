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
#endif //H_FONT_SCI
