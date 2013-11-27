/*
 ____________________________________________
| CBulletTemplate.h - definicja klasy.       |
| SCI - November 2012.                       |
|____________________________________________|

*/

#ifndef H_BULLET_TEMPLATE_JACK
#define H_BULLET_TEMPLATE_JACK

#include "CPhysicalTemplate.h"
#include "../Logic/CPhysicalManager.h"
#include "../Logic/Bullet/CBullet.h"
#include <string>
#include <vector>

///
///Forward declaration
///
namespace xml
{
	class CXml;
}

using namespace logic;

namespace factory
{
	///
	///Klasa reprezentuje wzorzec pocisku
	///
	class CBulletTemplate : public CPhysicalTemplate
	{
	
	public:

		///
		///Konstruktor
		///
		CBulletTemplate();

		///
		///Destruktor
		///
		~CBulletTemplate();

		///
		///Wirtualna metoda zwalniaj�ca zas�b
		///
		void Drop();

		///
		///Metoda �aduj�ca dane
		///
		///@param &name - sta�a referencja na std::string
		///
		bool Load(const std::string &name);

		///
		///Wirtualna metoda �aduj�ca dane z xml wywo�ywana przez implementacje klas potomnych
		///
		///@param &xml - referencja na obiekt klasy CXml
		///
		bool Load(CXml &xml);

		///
		///Wirtualna metoda tworzenie obiekt�w pochodnych klasy CPhysical
		///
		///implementowana przez w pe�ni konkretne podklasy
		///
		///@param id - nazwa identyfikatora - obiekt klasy std::wstring
		///
		CBullet* Create(std::wstring id = L"");

	protected:

		///
		///Wirtualna metoda wype�niaj�ca danymi obiekt klasy CBullet
		///
		///@param *bullet - wska�nik na obiekt klasy CBullet
		///
		virtual void Fill(CBullet *bullet);

	private:

	};
}//namespace factory
#endif//H_BULLET_TEMPLATE_JACK

