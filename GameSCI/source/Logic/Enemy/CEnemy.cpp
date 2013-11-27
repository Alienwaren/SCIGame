/*
 ____________________________________
| CEnemy.cpp - implementacja klasy.  |
| SCI - March 2013.                  |
|____________________________________|

*/

#include "CEnemy.h"

namespace logic
{

	//Chroniony konstruktor domyœlny
	CEnemy::CEnemy(const std::wstring &uniqueId) 
	:	
		CActor	(uniqueId)	
	{
	}

	//Chroniony konstruktor kopiuj¹cy
	CEnemy::CEnemy(const CEnemy &CEnemyCopy)
	:
		CActor	(CEnemyCopy)//konstruktor kopiuj¹cy klasy bazowej
	{
	}

	//Chroniony destruktor wirtualny - u¿ywany wy³¹cznie przez CPhysicalManager
	CEnemy::~CEnemy(void) 
	{
		//to do...
	}

	//Wirtualna metoda aktualizuj¹ca obiekt
	void CEnemy::Update(float dt)
	{
		CActor::Update(dt);
	}

	//Wirtualan metoda zabija obiekt klasy CEnemy i wywo³uje odpowiednie czynnoœci z tym zwi¹zane
	void CEnemy::Kill() 
	{
		//póki co bêdzie siê wywo³ywa³a metoda klasy bazowej
		CActor::Kill();
		//to do...
	}
}//namespace logic
