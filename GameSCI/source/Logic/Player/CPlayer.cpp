/*
 _____________________________________
| CPlayer.cpp - implementacja klasy.  |
| SCI - March 2013.                   |
|_____________________________________|

*/

#include "CPlayer.h"

namespace logic
{
	//Chroniony konstruktor domyœlny
	CPlayer::CPlayer(const std::wstring &uniqueId) 
	:	
		CActor	(uniqueId)	
	{
	}

	//Chroniony konstruktor kopiuj¹cy
	CPlayer::CPlayer(const CPlayer &CPlayerCopy)
	:
		CActor	(CPlayerCopy)//konstruktor kopiuj¹cy klasy bazowej
	{
	}

	//Chroniony destruktor wirtualny - u¿ywany wy³¹cznie przez CPhysicalManager
	CPlayer::~CPlayer(void) 
	{
		//to do...
	}

	//Wirtualna metoda aktualizuj¹ca obiekt
	void CPlayer::Update(float dt)
	{
		CActor::Update(dt);
	}

	//Wirtualan metoda zabija obiekt klasy CPlayer i wywo³uje odpowiednie czynnoœci z tym zwi¹zane
	void CPlayer::Kill() 
	{
		//póki co bêdzie siê wywo³ywa³a metoda klasy bazowej
		CActor::Kill();
		//to do...
	}
}//namespace logic