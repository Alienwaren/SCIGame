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
		
	//Wirtualna metoda ³aduj¹ca zasób - implementacja
	bool CFont::Load(const std::string &file_name)
	{
		if (loadFromFile(file_name))//jeœli dane zosta³y za³adowane
			return true;			//zwracamy flagê true (ok)
		return false;				//false, jeœli program nie za³adowa³ pliku
	}

	//Wirtualna metoda zwalniaj¹ca zasób
	void CFont::Drop()
	{
		delete this;
	}
}//namespace resource
