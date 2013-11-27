/*
 ____________________________________
| CEnemy.h - definicja klasy.        |
| SCI - March 2013.                  |
|____________________________________|

*/

#ifndef H_ENEMY_SCI
#define H_ENEMY_SCI

#include <string>
#include "../Actor/CActor.h"

///
///Forward declaration
///
class CActorAI;

namespace logic
{
	///
	///Klasa reprezentuje wroga
	///
	class CEnemy: public logic::CActor 
	{

		///
		///Deklaracja przyja�ni
		///
		friend class CPhysicalManager;

		//Aby uzyska� obiekt CEnemy, nale�y wywo�a� CPhysicalManager::CreateEnemy();

	protected:

		///
		///Chroniony konstruktor domy�lny
		///
		CEnemy(const std::wstring& uniqueId);

		///
		///Chroniony konstruktor kopiuj�cy
		///
		///@param CEnemyCopy - parametr - obiekt klasy CEnemy
		///
		CEnemy(const CEnemy &CEnemyCopy);

		///
		///Chroniony destruktor wirtualny - u�ywany wy��cznie przez CPhysicalManager
		///
		virtual ~CEnemy(void);

	public:

		///
		///Wirtualna metoda aktualizuj�ca obiekt
		///
		///@param dt - czas
		///
		virtual void Update(float dt);

		///
		///Wirtualan metoda zabija obiekt klasy CEnemy i wywo�uje odpowiednie czynno�ci z tym zwi�zane
		///
		virtual void Kill();

	private:

		//rozwojowo - zaproponuj pola oraz metody dla wroga (w zale�no�ci od pomys�u)
	};
}//namespace logic
#endif //H_ENEMY_SCI
