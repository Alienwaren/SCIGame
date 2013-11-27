/*
 ____________________________________________
| CPlayerTemplate.h - definicja klasy.       |
| SCI - May 2013.                            |
|____________________________________________|

*/

#ifndef H_PLAYER_TEMPLATE_SCI
#define H_PLAYER_TEMPLATE_SCI

#include "CActorTemplate.h"
#include "../Logic/Player/CPlayer.h"
#include <string>
#include <vector>

///
///Forward declaration
///
namespace xml
{
	class CXml;
}

namespace factory
{
	///
	///Klasa reprezentuje generyczny wzorzec wrogiej jednostki
	///
	class CPlayerTemplate : public CActorTemplate
	{

	public:

		///
		///Konstruktor
		///
		CPlayerTemplate();

		///
		///Destruktor wirtualny
		///
		virtual ~CPlayerTemplate();

		///
		///Wirtualna metoda zwalniaj¹ca zasób - implementacje w klasach pochodnych
		///
		void Drop();

		///
		///Metoda ³aduj¹ca dane
		///
		///@param &name - sta³a referencja na std::string
		///
		bool Load(const std::string &name);

		///
		///Wirtualna metoda ³aduj¹ca dane z xml ³aduje cechy CPlayer
		///
		///@param &xml - referencja na obiekt klasy CXml
		///
		bool Load(CXml &xml);

		///
		///Metoda tworzy obiek klasy CPlayer
		///
		///@param id - nazwa identyfikatora - obiekt klasy std::wstring
		///
		logic::CPlayer* Create(std::wstring id = L"");

	private:

		std::vector<std::wstring> m_player_AI;	//kontener nazw dostêpnych schematów AI gracza...to do...
	};
}//namespace factory
#endif //H_PLAYER_TEMPLATE_SCI
