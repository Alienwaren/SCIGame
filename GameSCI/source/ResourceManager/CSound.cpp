/*
 ___________________________________
| CSound.cpp - implementacja klasy. |
| SCI - October 2013.               |
|___________________________________|

*/

#include "CSound.h"

namespace resource
{
	//Konstruktor
	CSound::CSound(void)
	:
		IResource		(),	//konstruktor klasy bazowej
		sf::SoundBuffer	()	//konstruktor klasy bazowej
	{
	}

	//Destruktor
	CSound::~CSound(void)
	{
	}
		
	//Wirtualna metoda �aduj�ca zas�b - implementacja
	bool CSound::Load(const std::string &file_name)
	{
		if (loadFromFile(file_name))//je�li dane zosta�y za�adowane
			return true;			//zwracamy flag� true (ok)
		return false;				//false, je�li program nie za�adowa� pliku
	}

	//Wirtualna metoda zwalniaj�ca zas�b
	void CSound::Drop()
	{
		delete this;
	}
}//namespace resource
