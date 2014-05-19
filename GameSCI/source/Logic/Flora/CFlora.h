#ifndef H_CFLORA
#define H_CFLORA
#include "../Actor/CActor.h"

namespace logic
{
	///
	///Klasa reprezentuje obiekty - roœlinnoœæ (drzewa, krzewy, etc...)
	///
	class CFlora : public CActor
	{

		///
		///Deklaracja przyjaŸni
		///
		friend class CPhysicalManager;
		
//Aby uzyskaæ obiekt CFlora, nale¿y wywo³aæ
//CPhysicalManager::CreateFlora();

	protected:
		///
		///Chroniony konstruktor domyœlny
		///
		CFlora(const std::wstring& uniqueId);

		///
		///Destruktor wirtualny
		///
		virtual ~CFlora(void);

	public:

		///
		///Wirtualna metoda aktualizuj¹ca obiekt
		///
		///@param dt - czas
		///
		virtual void Update(float dt);

	};
}//namespace logic


#endif //#ifndef H_CFLORA
