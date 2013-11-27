/*
 ____________________________________
| CBullet.h - definicja klasy.       |
| SCI - March 2013.                  |
|____________________________________|

*/

#ifndef H_BULLET_JACK
#define H_BULLET_JACK

#include "../Physical/CPhysical.h"

namespace logic
{
	///
	///Klasa reprezentuje funkcjonalnoœæ pocisku
	///
	class CBullet : public CPhysical
	{
		///
		///Deklaracja przyjaŸni
		///
		friend class CPhysicalManager;
		
		//Aby uzyskaæ obiekt CBullet, nale¿y wywo³aæ CPhysicalManager::CreateCBullet();
		
	protected:

		///
		///Chroniony konstruktor domyœlny
		///
		CBullet(const std::wstring& uniqueId);

		///
		///Chroniony konstruktor kopiuj¹cy
		///
		///@param CBulletCopy - parametr - obiekt klasy CBullet
		///
		CBullet(const CBullet &CBulletCopy);

		///
		///Chroniony destruktor wirtualny - u¿ywany wy³¹cznie przez CPhysicalManager
		///
		virtual ~CBullet();

	public:

		///
		///Wirtualna metoda aktualizuj¹ca obiekt
		///
		///@param dt - czas
		///
		virtual void Update(float dt);

	private:

		//dodaæ pola z Testowy...
		//dodaæ metody z Testowy...
	};
}//namespace logic
#endif//H_BULLET_JACK



//Ekxploxja
//wypuszcza detector
//sprawdza kolizje...
//patrz Testowy...

//float TTL;
//float range;
//EffectSourcePtr source;
//EffectSourcePtr meAsSource;
//int rotSpeed;
//ExecutionContextPtr context;
//float acceleration;
//int explodeOnFade;
//int filter; //tox, 26 sierpnia - patrz komentarz w BulletEmiterze.h
//void HandleCollision(CPhysical *phys);
//virtual CAppliedEffectContainer *GetAppliedEffectContainer();
		// dla pociskow samonaprowadzajacych
		//float mTimeForTracking;
		//float mTurningSpeed;
		//Memory::CSafePtr<CActor> mTarget;
		//CTargetChooser *mTargetChooser;
