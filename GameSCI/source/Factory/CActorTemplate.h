/*
 ___________________________________________
| CActorTemplate.h - definicja klasy.       |
| SCI - February 2013.                      |
|___________________________________________|

*/

#ifndef H_ACTOR_TEMPLATE_SCI
#define H_ACTOR_TEMPLATE_SCI

#include "CPhysicalTemplate.h"
#include "../Logic/Enemy/CEnemy.h"
#include <string>
#include <vector>

///
///Forward declaration
///
namespace xml
{
	class CXml;
}

///
///Forward declaration
///
namespace logic
{
	class CActor;
}

///
///Forward declaration
///
namespace rendering
{
	namespace animation
	{
		class CAnimSet;
	}
}

namespace factory
{
	///
	///Klasa reprezentuje generyczny wzorzec aktora
	///
	class CActorTemplate : public CPhysicalTemplate
	{

	public:

		///
		///Konstruktor
		///
		CActorTemplate();

		///
		///Destruktor wirtualny
		///
		virtual ~CActorTemplate();

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
		///Wirtualna metoda �aduj�ca dane z xml �aduje wsp�lne cechy CActor
		///
		///@param &xml - referencja na obiekt klasy CXml
		///
		bool Load(CXml &xml);
		
	protected:

		CAnimSet*				p_templ_animations;				//wska�nik na zestaw animacji CActor
		float					m_templ_energy;					//warto�� energii - �ycie obiektu
		std::vector<CAnimSet*>	m_templ_available_animations;	//wektor wska�nik�w na zestawy dost�pnych animacji dla CActor
		float					m_templ_mass;					//masa obiektu
		float					m_templ_temperature;			//temperatura obiektu (wytwarzana przez engine)
		float					m_templ_speed;					//pr�dko�� przemieszczania si� obiektu
		bool					m_templ_movabled;				//flaga okre�la czy obiekt mo�e si� przemieszcza�

	protected:

		///
		///Wirtualna metoda wype�niaj�ca danymi obiekt klasy CActor
		///
		///@param *actor - wska�nik na obiekt klasy CActor
		///
		virtual void Fill(CActor *actor);

	public:

		//metoda zwraca referencj� na kontener z zestawem animacji
		inline const std::vector<CAnimSet*> &GetAvailableAnims() { return m_templ_available_animations; }
	};
} //namespace factory
#endif //H_ACTOR_TEMPLATE_SCI
