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
		
	//Wirtualna metoda ³aduj¹ca zasób - implementacja
	bool CSound::Load(const std::string &file_name)
	{
		if (loadFromFile(file_name))//jeœli dane zosta³y za³adowane
			return true;			//zwracamy flagê true (ok)
		return false;				//false, jeœli program nie za³adowa³ pliku
	}

	//Wirtualna metoda zwalniaj¹ca zasób
	void CSound::Drop()
	{
		delete this;
	}
}//namespace resource
