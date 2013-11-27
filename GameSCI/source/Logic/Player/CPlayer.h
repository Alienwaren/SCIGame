/*
 _____________________________________
| CPlayer.h - definicja klasy.        |
| SCI - March 2013.                   |
|_____________________________________|

*/

#ifndef H_PLAYER_SCI
#define H_PLAYER_SCI

#include <string>
#include "../Actor/CActor.h"

///
///Forward declaration
///
class CPlayerAI;

namespace logic
{
	///
	///Klasa reprezentuje gracza
	///
	class CPlayer: public logic::CActor 
	{

		///
		///Deklaracja przyjaŸni
		///
		friend class CPhysicalManager;

		//Aby uzyskaæ obiekt CPlayer, nale¿y wywo³aæ CPhysicalManager::CreatePlayer();

	protected:

		///
		///Chroniony konstruktor domyœlny
		///
		CPlayer(const std::wstring& uniqueId);

		///
		///Chroniony konstruktor kopiuj¹cy
		///
		///@param CPlayerCopy - parametr - obiekt klasy CPlayer
		///
		CPlayer(const CPlayer &CPlayerCopy);

		///
		///Chroniony destruktor wirtualny - u¿ywany wy³¹cznie przez CPhysicalManager
		///
		virtual ~CPlayer(void);

	public:

		///
		///Wirtualna metoda aktualizuj¹ca obiekt
		///
		///@param dt - czas
		///
		virtual void Update(float dt);

		///
		///Wirtualan metoda zabija obiekt klasy CPlayer i wywo³uje odpowiednie czynnoœci z tym zwi¹zane
		///
		virtual void Kill();

	private:

		//rozwojowo - zaproponuj pola oraz metody dla gracza (w zale¿noœci od pomys³u)
	};
}//namespace logic
#endif //H_PLAYER_SCI
