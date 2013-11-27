/*
 _______________________________________
| CActor.h - definicja klasy.           |
| SCI - December 2012.                  |
|_______________________________________|

*/

#ifndef H_ACTOR_SCI
#define H_ACTOR_SCI

#include "../Physical/CPhysical.h"
#include <vector>
#include <map>

///
///Forward declaration
///
namespace rendering
{
	namespace displayable
	{
		class CDisplayable;
	}
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
namespace logic
{
	///
	///Klasa reprezentuje klas� bazow�, z kt�rej dziedzicz� wszystkie obiekty sceny np. CEnemy, CPlayer, etc...
	///
	class CActor : public logic::CPhysical
	{

		///
		///Deklaracja przyja�ni
		///
		friend class CPhysicalManager;
		
		//Aby uzyska� obiekt CActor, nale�y wywo�a� CPhysicalManager::CreateActor();

	protected:

		///
		///Chroniony konstruktor domy�lny
		///
		CActor(const std::wstring& uniqueId);

		///
		///Chroniony konstruktor kopiuj�cy
		///
		///@param CActorCopy - obiekt klasy CActor
		///
		CActor(const CActor &CActorCopy);

		///
		///Chroniony destruktor wirtualny - u�ywany wy��cznie przez CPhysicalManager
		///
		virtual ~CActor(void);

	public:

		///
		///Metoda zwraca mas� obiektu
		///
		const float getEnergy() const;

		///
		///Metoda zwraca mas� obiektu
		///
		///@param energy - energia obiektu
		///
		const void setEnergy(float energy);

		///
		///Metoda zwraca mas� obiektu
		///
		const float getMass() const;

		///
		///Metoda ustawia mas� obiektu
		///
		///@param mass - masa obiektu
		///
		const void setMass(float mass);

		///
		///Metoda zwraca temperatur� obiektu
		///
		const float getTemperature() const;

		///
		///Metoda ustawia temperatur� obiektu
		///
		///@param temperature - temperatura obiektu
		///
		const void setTemperature(float temperature);

		///
		///Metoda zwraca flag�, czy obiekt si� porusza
		///
		bool const getIsMove() const;

		///
		///Metoda ustawia flag�, �e obiekt si� porusza
		///
		///@param is_move - flaga, czy obiekt si� porusza
		///
		const void setIsMove(bool is_move);

		///
		///Metoda zwraca flag�, czy obiekt mo�e si� przemieszcza�
		///
		const bool getIsMovabled() const;

		///
		///Metoda ustawia flag�, czy obiekt mo�e si� przemieszcza�
		///
		///@param movabled - parametr okre�laj�cy, czy obiekt mo�e si� przemieszcza�
		///
		const void setIsMovabled(bool movabled);

		///
		///Metoda zwraca pr�dko�� obiektu
		///
		const float getSpeed() const;

		///
		///Metoda ustawia pr�dko�� obiektu
		///
		///@param speed - pr�dko�� obiektu
		///
		const void setSpeed(float speed);

		///
		///Metoda zwraca wska�nik na zestaw animacji
		///
		CAnimSet *GetAnimSet();

		///
		///Metoda ustawia zestaw animacji
		///
		///@param *anim_set - wska�nik na obiekt klasy CAnimSet
		///
		void SetAnimSet(CAnimSet *anim_set);

		///
		///Wirtualan metoda zabija obiekt klasy CActor i wywo�uje odpowiednie czynno�ci z tym zwi�zane
		///
		virtual void Kill();

		///
		///Wirtualna metoda aktualizuj�ca obiekt
		///
		///@param dt - czas
		///
		virtual void Update(float dt);

	protected:

		CAnimSet*			p_anim_set;		//wska�nik na obiekt klasy CAnimSet (zestaw animacji)
		float				m_energy;		//warto�� energii - �ycie obiektu
		float				m_mass;			//masa obiektu
		float				m_temperature;	//temperatura obiektu
		float				m_speed;		//pr�dko�� przemieszczania si� obiektu
		bool				m_movabled;		//flaga okre�la czy obiekt mo�e si� przemieszcza�
		bool				m_is_move;		//flaga, czy obiekt si� porusza

	private:

		//
		//metoda aktualizuje animacje w zale�no�ci od stanu logiki obiektu (move, attack, death, etc...)
		//
		//@param dt - czas
		//
		void UpdateAnimations(float dt);

		//metoda pomocnicza - metoda ustawia zestaw animacji - body
		void SetAnimSetBody(CAnimSet *anim_set);

		//metoda pomocnicza - metoda ustawia zestaw animacji - head
		void SetAnimSetHead(CAnimSet *anim_set);
	};
}//namespace logic
#endif //H_ACTOR_SCI
