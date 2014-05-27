
#include "CFlora.h"

namespace logic
{
	//Chroniony konstruktor domyœlny
	CFlora::CFlora(const std::wstring& uniqueId)
	:
		CActor			(uniqueId)//konstruktor klasy bazowej
	{
	}
	CFlora *CPhysicalManager::CreateFlora(const std::wstring &uniqueId)
	{
		fprintf(stderr, "CFlora created\n");
		return Create<CFlora>(uniqueId);
	}

	//Destruktor wirtualny
	CFlora::~CFlora(void)
	{
	}

	//Wirtualna metoda aktualizuj¹ca obiekt
	void CFlora::Update(float dt)
	{
		//AI flora: To Do...
	}

}//namespace logic


