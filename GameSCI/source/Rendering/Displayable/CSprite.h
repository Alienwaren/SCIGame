/*
 _____________________________________
| CSprite.h - definicja klasy.        |
| SCI - February 2012.                |
|_____________________________________|

*/

#ifndef H_SPRITE_SCI
#define H_SPRITE_SCI

#include <SFML/Graphics/Sprite.hpp>

namespace rendering
{
	namespace displayable
	{
		///
		///Klasa reprezentuje opakowanie klasy sf::sprite
		///
		class CSprite : public sf::Sprite
		{

		public:

			///
			///Konstruktor domyœlny
			///
			CSprite();

			///
			///Destruktor
			///
			~CSprite();
		};
	}//namespace displayable
}//namespace rendering
#endif //_H_SPRITE_JACK
