/*
 _____________________________________
| CTexture.cpp - implementacja klasy. |
| SCI - October 2013.                 |
|_____________________________________|

*/

#include "CTexture.h"

namespace resource
{
	//Konstruktor
	CTexture::CTexture(void)
	:
		IResource	(),	//konstruktor klasy bazowej
		sf::Texture	()	//konstruktor klasy bazowej
	{
	}

	//Destruktor
	CTexture::~CTexture(void)
	{
	}
		
	//Wirtualna metoda �aduj�ca zas�b - implementacja
	bool CTexture::Load(const std::string &file_name)
	{
		if (loadFromFile(file_name))//je�li dane zosta�y za�adowane
			return true;			//zwracamy flag� true (ok)
		return false;				//false, je�li program nie za�adowa� pliku
	}

	//Wirtualna metoda zwalniaj�ca zas�b
	void CTexture::Drop()
	{
		delete this;
	}
}//namespace resource
