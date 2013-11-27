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
		///Wirtualna metoda zwalniaj�ca zas�b - implementacje w klasach pochodnych
		///
		void Drop();

		///
		///Metoda �aduj�ca dane
		///
		///@param &name - sta�a referencja na std::string
		///
		bool Load(const std::string &name);

		///
		///Wirtualna metoda �aduj�ca dane z xml �aduje cechy CPlayer
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

		std::vector<std::wstring> m_player_AI;	//kontener nazw dost�pnych schemat�w AI gracza...to do...
	};
}//namespace factory
#endif //H_PLAYER_TEMPLATE_SCI
