/*
 _____________________________________
| CSprite.cpp - implementacja klasy.  |
| SCI - February 2012.                |
|_____________________________________|

*/

#include "CSprite.h"
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics.hpp>

namespace rendering
{
	namespace displayable
	{
		//Konstruktor domyœlny
		CSprite::CSprite()
		:
			sf::Sprite()//konstruktor klasy bazowej
		{
		}

		//Destruktor
		CSprite::~CSprite()
		{
		}
	}//namespace displayable
}//namespace rendering
