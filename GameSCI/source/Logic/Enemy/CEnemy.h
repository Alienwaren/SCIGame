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
		///Deklaracja przyjaŸni
		///
		friend class CPhysicalManager;

		//Aby uzyskaæ obiekt CEnemy, nale¿y wywo³aæ CPhysicalManager::CreateEnemy();

	protected:

		///
		///Chroniony konstruktor domyœlny
		///
		CEnemy(const std::wstring& uniqueId);

		///
		///Chroniony konstruktor kopiuj¹cy
		///
		///@param CEnemyCopy - parametr - obiekt klasy CEnemy
		///
		CEnemy(const CEnemy &CEnemyCopy);

		///
		///Chroniony destruktor wirtualny - u¿ywany wy³¹cznie przez CPhysicalManager
		///
		virtual ~CEnemy(void);

	public:

		///
		///Wirtualna metoda aktualizuj¹ca obiekt
		///
		///@param dt - czas
		///
		virtual void Update(float dt);

		///
		///Wirtualan metoda zabija obiekt klasy CEnemy i wywo³uje odpowiednie czynnoœci z tym zwi¹zane
		///
		virtual void Kill();

	private:

		//rozwojowo - zaproponuj pola oraz metody dla wroga (w zale¿noœci od pomys³u)
	};
}//namespace logic
#endif //H_ENEMY_SCI
