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
		///Deklaracja przyja�ni
		///
		friend class CPhysicalManager;

		//Aby uzyska� obiekt CPlayer, nale�y wywo�a� CPhysicalManager::CreatePlayer();

	protected:

		///
		///Chroniony konstruktor domy�lny
		///
		CPlayer(const std::wstring& uniqueId);

		///
		///Chroniony konstruktor kopiuj�cy
		///
		///@param CPlayerCopy - parametr - obiekt klasy CPlayer
		///
		CPlayer(const CPlayer &CPlayerCopy);

		///
		///Chroniony destruktor wirtualny - u�ywany wy��cznie przez CPhysicalManager
		///
		virtual ~CPlayer(void);

	public:

		///
		///Wirtualna metoda aktualizuj�ca obiekt
		///
		///@param dt - czas
		///
		virtual void Update(float dt);

		///
		///Wirtualan metoda zabija obiekt klasy CPlayer i wywo�uje odpowiednie czynno�ci z tym zwi�zane
		///
		virtual void Kill();

	private:

		//rozwojowo - zaproponuj pola oraz metody dla gracza (w zale�no�ci od pomys�u)
	};
}//namespace logic
#endif //H_PLAYER_SCI
