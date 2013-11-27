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
		///Wirtualna metoda ³aduj¹ca dane z xml ³aduje wspólne cechy CActor
		///
		///@param &xml - referencja na obiekt klasy CXml
		///
		bool Load(CXml &xml);
		
	protected:

		CAnimSet*				p_templ_animations;				//wskaŸnik na zestaw animacji CActor
		float					m_templ_energy;					//wartoœæ energii - ¿ycie obiektu
		std::vector<CAnimSet*>	m_templ_available_animations;	//wektor wskaŸników na zestawy dostêpnych animacji dla CActor
		float					m_templ_mass;					//masa obiektu
		float					m_templ_temperature;			//temperatura obiektu (wytwarzana przez engine)
		float					m_templ_speed;					//prêdkoœæ przemieszczania siê obiektu
		bool					m_templ_movabled;				//flaga okreœla czy obiekt mo¿e siê przemieszczaæ

	protected:

		///
		///Wirtualna metoda wype³niaj¹ca danymi obiekt klasy CActor
		///
		///@param *actor - wskaŸnik na obiekt klasy CActor
		///
		virtual void Fill(CActor *actor);

	public:

		//metoda zwraca referencjê na kontener z zestawem animacji
		inline const std::vector<CAnimSet*> &GetAvailableAnims() { return m_templ_available_animations; }
	};
} //namespace factory
#endif //H_ACTOR_TEMPLATE_SCI
