/*
 ____________________________________
| CBullet.cpp - implementacja klasy. |
| SCI - March 2013.                  |
|____________________________________|

*/

#include "CBullet.h"
#include "../CPhysicalManager.h"

namespace logic
{
	//Chroniony konstruktor domy�lny
	CBullet::CBullet(const std::wstring &uniqueId)
	:
		CPhysical(uniqueId)//konstruktor klasy bazowej
	{
	}

	//Chroniony konstruktor kopiuj�cy
	CBullet::CBullet(const CBullet &CBulletCopy)
	:
		CPhysical	(CBulletCopy)//konstruktor kopiuj�cy klasy bazowej
	{
	}

	CBullet::~CBullet()
	{
		//to do...
	}


	void CBullet::Update(float dt)
	{
		CPhysical::Update(dt);

		//potrzebuj� klasy CDetector...
	}
}//namespace logic







//#include "../Utils/MathsFunc.h"
//#include "../Utils/Directions.h"
//#include "CActor.h"
//#include "Effects/CEffectHandle.h"
//#include "CDetector.h"
//#include "Abilities/CTargetChooser.h"
