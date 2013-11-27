/*
 ____________________________________
| CEnemy.cpp - implementacja klasy.  |
| SCI - March 2013.                  |
|____________________________________|

*/

#include "CEnemy.h"

namespace logic
{

	//Chroniony konstruktor domy�lny
	CEnemy::CEnemy(const std::wstring &uniqueId) 
	:	
		CActor	(uniqueId)	
	{
	}

	//Chroniony konstruktor kopiuj�cy
	CEnemy::CEnemy(const CEnemy &CEnemyCopy)
	:
		CActor	(CEnemyCopy)//konstruktor kopiuj�cy klasy bazowej
	{
	}

	//Chroniony destruktor wirtualny - u�ywany wy��cznie przez CPhysicalManager
	CEnemy::~CEnemy(void) 
	{
		//to do...
	}

	//Wirtualna metoda aktualizuj�ca obiekt
	void CEnemy::Update(float dt)
	{
		CActor::Update(dt);
	}

	//Wirtualan metoda zabija obiekt klasy CEnemy i wywo�uje odpowiednie czynno�ci z tym zwi�zane
	void CEnemy::Kill() 
	{
		//p�ki co b�dzie si� wywo�ywa�a metoda klasy bazowej
		CActor::Kill();
		//to do...
	}
}//namespace logic
