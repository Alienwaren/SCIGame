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
		
	//Wirtualna metoda ³aduj¹ca zasób - implementacja
	bool CMusic::Load(const std::string &file_name)
	{
		if (openFromFile(file_name))//jeœli dane zosta³y za³adowane
			return true;			//zwracamy flagê true (ok)
		return false;				//false, jeœli program nie za³adowa³ pliku
	}

	//Wirtualna metoda zwalniaj¹ca zasób
	void CMusic::Drop()
	{
		delete this;
	}
}//namespace resource
