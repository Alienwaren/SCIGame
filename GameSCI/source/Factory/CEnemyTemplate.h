/*
 ___________________________________________
| CEnemyTemplate.h - definicja klasy.       |
| SCI - May 2013.                           |
|___________________________________________|

*/

#ifndef H_ENEMY_TEMPLATE_SCI
#define H_ENEMY_TEMPLATE_SCI

#include "CActorTemplate.h"
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
	class CEnemyTemplate : public CActorTemplate
	{

	public:

		///
		///Konstruktor
		///
		CEnemyTemplate();

		///
		///Destruktor wirtualny
		///
		virtual ~CEnemyTemplate();

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
		///Wirtualna metoda ³aduj¹ca dane z xml ³aduje cechy CEnemy
		///
		///@param &xml - referencja na obiekt klasy CXml
		///
		bool Load(CXml &xml);

		///
		///Metoda tworzy obiek klasy CEnemy
		///
		///@param id - nazwa identyfikatora - obiekt klasy std::wstring
		///
		logic::CEnemy* Create(std::wstring id = L"");

	private:

		std::vector<std::wstring> m_enemy_AI;	//kontener nazw dostêpnych schematów AI wroga...to do...
	};
}//namespace factory
#endif //H_ENEMY_TEMPLATE_SCI
