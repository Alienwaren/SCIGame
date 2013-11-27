/*
 ___________________________________
| CMusic.cpp - implementacja klasy. |
| SCI - October 2013.               |
|___________________________________|

*/

#include "CMusic.h"

namespace resource
{
	//Konstruktor
	CMusic::CMusic(void)
	:
		IResource	(),	//konstruktor klasy bazowej
		sf::Music	()	//konstruktor klasy bazowej
	{
	}

	//Destruktor
	CMusic::~CMusic(void)
	{
	}
		
	//Wirtualna metoda �aduj�ca zas�b - implementacja
	bool CMusic::Load(const std::string &file_name)
	{
		if (openFromFile(file_name))//je�li dane zosta�y za�adowane
			return true;			//zwracamy flag� true (ok)
		return false;				//false, je�li program nie za�adowa� pliku
	}

	//Wirtualna metoda zwalniaj�ca zas�b
	void CMusic::Drop()
	{
		delete this;
	}
}//namespace resource
