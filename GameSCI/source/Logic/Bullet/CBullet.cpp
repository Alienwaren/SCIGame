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
	//Chroniony konstruktor domyœlny
	CBullet::CBullet(const std::wstring &uniqueId)
	:
		CPhysical(uniqueId)//konstruktor klasy bazowej
	{
	}

	//Chroniony konstruktor kopiuj¹cy
	CBullet::CBullet(const CBullet &CBulletCopy)
	:
		CPhysical	(CBulletCopy)//konstruktor kopiuj¹cy klasy bazowej
	{
	}

	CBullet::~CBullet()
	{
		//to do...
	}


	void CBullet::Update(float dt)
	{
		CPhysical::Update(dt);

		//potrzebujê klasy CDetector...
	}
}//namespace logic







//#include "../Utils/MathsFunc.h"
//#include "../Utils/Directions.h"
//#include "CActor.h"
//#include "Effects/CEffectHandle.h"
//#include "CDetector.h"
//#include "Abilities/CTargetChooser.h"
