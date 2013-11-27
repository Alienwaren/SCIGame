/*
 __________________________________
| CFont.cpp - implementacja klasy. |
| SCI - October 2013.              |
|__________________________________|

*/

#include "CFont.h"

namespace resource
{
	//Konstruktor
	CFont::CFont(void)
	:
		IResource	(),	//konstruktor klasy bazowej
		sf::Font	()	//konstruktor klasy bazowej
	{
	}

	//Destruktor
	CFont::~CFont(void)
	{
	}
		
	//Wirtualna metoda �aduj�ca zas�b - implementacja
	bool CFont::Load(const std::string &file_name)
	{
		if (loadFromFile(file_name))//je�li dane zosta�y za�adowane
			return true;			//zwracamy flag� true (ok)
		return false;				//false, je�li program nie za�adowa� pliku
	}

	//Wirtualna metoda zwalniaj�ca zas�b
	void CFont::Drop()
	{
		delete this;
	}
}//namespace resource
