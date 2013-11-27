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
	///Klasa reprezentuje klasê bazow¹, z której dziedzicz¹ wszystkie obiekty sceny np. CEnemy, CPlayer, etc...
	///
	class CActor : public logic::CPhysical
	{

		///
		///Deklaracja przyjaŸni
		///
		friend class CPhysicalManager;
		
		//Aby uzyskaæ obiekt CActor, nale¿y wywo³aæ CPhysicalManager::CreateActor();

	protected:

		///
		///Chroniony konstruktor domyœlny
		///
		CActor(const std::wstring& uniqueId);

		///
		///Chroniony konstruktor kopiuj¹cy
		///
		///@param CActorCopy - obiekt klasy CActor
		///
		CActor(const CActor &CActorCopy);

		///
		///Chroniony destruktor wirtualny - u¿ywany wy³¹cznie przez CPhysicalManager
		///
		virtual ~CActor(void);

	public:

		///
		///Metoda zwraca masê obiektu
		///
		const float getEnergy() const;

		///
		///Metoda zwraca masê obiektu
		///
		///@param energy - energia obiektu
		///
		const void setEnergy(float energy);

		///
		///Metoda zwraca masê obiektu
		///
		const float getMass() const;

		///
		///Metoda ustawia masê obiektu
		///
		///@param mass - masa obiektu
		///
		const void setMass(float mass);

		///
		///Metoda zwraca temperaturê obiektu
		///
		const float getTemperature() const;

		///
		///Metoda ustawia temperaturê obiektu
		///
		///@param temperature - temperatura obiektu
		///
		const void setTemperature(float temperature);

		///
		///Metoda zwraca flagê, czy obiekt siê porusza
		///
		bool const getIsMove() const;

		///
		///Metoda ustawia flagê, ¿e obiekt siê porusza
		///
		///@param is_move - flaga, czy obiekt siê porusza
		///
		const void setIsMove(bool is_move);

		///
		///Metoda zwraca flagê, czy obiekt mo¿e siê przemieszczaæ
		///
		const bool getIsMovabled() const;

		///
		///Metoda ustawia flagê, czy obiekt mo¿e siê przemieszczaæ
		///
		///@param movabled - parametr okreœlaj¹cy, czy obiekt mo¿e siê przemieszczaæ
		///
		const void setIsMovabled(bool movabled);

		///
		///Metoda zwraca prêdkoœæ obiektu
		///
		const float getSpeed() const;

		///
		///Metoda ustawia prêdkoœæ obiektu
		///
		///@param speed - prêdkoœæ obiektu
		///
		const void setSpeed(float speed);

		///
		///Metoda zwraca wskaŸnik na zestaw animacji
		///
		CAnimSet *GetAnimSet();

		///
		///Metoda ustawia zestaw animacji
		///
		///@param *anim_set - wskaŸnik na obiekt klasy CAnimSet
		///
		void SetAnimSet(CAnimSet *anim_set);

		///
		///Wirtualan metoda zabija obiekt klasy CActor i wywo³uje odpowiednie czynnoœci z tym zwi¹zane
		///
		virtual void Kill();

		///
		///Wirtualna metoda aktualizuj¹ca obiekt
		///
		///@param dt - czas
		///
		virtual void Update(float dt);

	protected:

		CAnimSet*			p_anim_set;		//wskaŸnik na obiekt klasy CAnimSet (zestaw animacji)
		float				m_energy;		//wartoœæ energii - ¿ycie obiektu
		float				m_mass;			//masa obiektu
		float				m_temperature;	//temperatura obiektu
		float				m_speed;		//prêdkoœæ przemieszczania siê obiektu
		bool				m_movabled;		//flaga okreœla czy obiekt mo¿e siê przemieszczaæ
		bool				m_is_move;		//flaga, czy obiekt siê porusza

	private:

		//
		//metoda aktualizuje animacje w zale¿noœci od stanu logiki obiektu (move, attack, death, etc...)
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
