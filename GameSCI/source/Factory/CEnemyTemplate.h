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
		///Wirtualna metoda �aduj�ca dane z xml �aduje cechy CEnemy
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

		std::vector<std::wstring> m_enemy_AI;	//kontener nazw dost�pnych schemat�w AI wroga...to do...
	};
}//namespace factory
#endif //H_ENEMY_TEMPLATE_SCI
