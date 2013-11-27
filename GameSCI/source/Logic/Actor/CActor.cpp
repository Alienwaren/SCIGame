/*
 _______________________________________
| CActor.cpp - implementacja klasy.     |
| SCI - December 2012.                  |
|_______________________________________|

*/

#include "CActor.h"
#include "../../Rendering/Displayable/CDisplayable.h"
#include "../../Rendering/Animations/CAnimSet.h"
#include "../../Rendering/Animations/CAnimationState.h"
#include "../../Rendering/Animations/CNameAnimPairTranslator.h"

using namespace rendering::displayable;

namespace logic
{
	//Chroniony konstruktor domyœlny
	CActor::CActor(const std::wstring& uniqueId)
	:
		CPhysical		(uniqueId),	//konstruktor klasy bazowej
		p_anim_set		(NULL),
		m_energy		(0.0f),
		m_mass			(0.0f),
		m_temperature	(0.0f),
		m_speed			(0.0f),
		m_movabled		(true),
		m_is_move		(false)
	{
	}

	//Chroniony konstruktor kopiuj¹cy
	CActor::CActor(const CActor &CActorCopy)
	:
		CPhysical		(CActorCopy),//konstruktor kopiuj¹cy klasy bazowej
		p_anim_set		(CActorCopy.p_anim_set),
		m_energy		(CActorCopy.m_energy),
		m_mass			(CActorCopy.m_mass),
		m_temperature	(CActorCopy.m_temperature),
		m_speed			(CActorCopy.m_speed),
		m_movabled		(CActorCopy.m_movabled),
		m_is_move		(CActorCopy.m_is_move)
	{
	}

	//Chroniony destruktor wirtualny - u¿ywany wy³¹cznie przez CPhysicalManager
	CActor::~CActor(void)
	{
		p_anim_set		= NULL;
		m_energy		= 0.0f;
		m_mass			= 0.0f;
		m_temperature	= 0.0f;
		m_speed			= 0.0f;
		m_movabled		= false;
		m_is_move		= false;
	}

	//Metoda zwraca masê obiektu
	const float CActor::getEnergy() const
	{
		return m_energy;
	}

	//Metoda zwraca masê obiektu
	const void CActor::setEnergy(float energy)
	{
		if (energy < 0) return;
		m_energy = energy;
	}

	//Metoda ustawia masê obiektu
	const void CActor::setMass(float mass)
	{
		if (mass < 0) return;
		m_mass = mass;
	}

	//Metoda zwraca temperaturê obiektu
	const float CActor::getTemperature() const
	{
		return m_temperature;
	}

	//Metoda ustawia temperaturê obiektu
	const void CActor::setTemperature(float temperature)
	{
		m_temperature = temperature;
	}

	//Metoda zwraca flagê, czy obiekt siê porusza
	bool const CActor::getIsMove() const
	{
		return m_is_move;
	}

	//Metoda ustawia flagê, ¿e obiekt siê porusza
	const void CActor::setIsMove(bool is_move)
	{
		m_is_move = is_move;
	}

	//Metoda zwraca flagê, czy obiekt mo¿e siê przemieszczaæ
	const bool CActor::getIsMovabled() const
	{
		return m_movabled;
	}

	//Metoda ustawia flagê, czy obiekt mo¿e siê przemieszczaæ
	const void CActor::setIsMovabled(bool movabled)
	{
		m_movabled = movabled;
	}

	//Metoda zwraca prêdkoœæ obiektu
	const float CActor::getSpeed() const
	{
		return m_speed;
	}

	//Metoda ustawia prêdkoœæ obiektu
	const void CActor::setSpeed(float speed)
	{
		if (speed < 0) return;
		m_speed = speed;
	}

	//Metoda zwraca wskaŸnik na zestaw animacji
	CAnimSet *CActor::GetAnimSet()
	{
		return p_anim_set;
	}

	//Metoda ustawia zestaw animacji
	void CActor::SetAnimSet(CAnimSet *anim_set)
	{
		SetAnimSetBody(anim_set);	//body
		SetAnimSetHead(anim_set);	//head
		p_anim_set = anim_set;		//zmiana zestawu animacji na nowy (parametr)
	}

	//Wirtualan metoda zabija obiekt klasy CActor i wywo³uje odpowiednie czynnoœci z tym zwi¹zane
	void CActor::Kill()
	{
		//póki co bêdzie siê wywo³ywa³a metoda klasy bazowej
		CPhysical::Kill();
		//to do...
	}

	//Wirtualna metoda aktualizuj¹ca obiekt
	void CActor::Update(float dt)
	{
		CPhysical::Update(dt);			//aktualizacja klasy bazowej
		m_energy = m_energy - 0.05f;	//aktualizujemy energiê...(zmniejszamy)
										//wartoœæ pocz¹tkowa by³a ustawiona na 100
		
		//poni¿sza metoda podmienia zestaw animacji w zale¿noœci od energii
		UpdateAnimations(dt);

		//Wniosek:
		//gdy stan obiektu (energia, kondycja, lub inne stany) obiektu
		//siê zmieni¹, mo¿emy podmianiaæ zestawy animacji, aby to zobrazowaæ...
		//np. zestaw animacji (normalny, obiekt siê przemieszcza, animacja uszkodzeñ, itp...)
	}

	//implementajca metod private:

	//metoda ustawia zestaw animacji - body
	void CActor::SetAnimSetBody(CAnimSet *anim_set)
	{
		//jeœli zestaw animacji jest zainicjowany
		if (p_anim_set)//body
		{
			//p³ynna zmiana animacji - body
			CAnimation *curr_anim = GetAnimationBody();

			//kontener przechowuj¹cy stary (dotychczasowy) zestaw animacji
			const std::vector<CNameAnimPairTranslator> &old_anims = p_anim_set->GetAnims();
			
			//kontener przechowuj¹cy nowy (parametr tej metody) zestaw animacji
			const std::vector<CNameAnimPairTranslator> &new_anims = anim_set->GetAnims();
	        
			//indeks, pod którym mo¿e znajdowaæ siê szukana animacja
			unsigned int index = -1;
	        
			//przeszukujê stary zestaw animacji, aby odszukaæ w nim animacjê do podmiany
			for (unsigned int i = 0; i < old_anims.size(); i++)
			{
				//jeœli znalaz³em szukan¹ animacjê w starym (dotychczasowym) kontenerze
				if (old_anims[i].GetAnimation() == curr_anim)
				{
					index = i;	//zapamiêtujê pod jakim jest indeksem w kontenerze
					break;		//i przerywam przeszukiwanie
				}
			}

			//jeœli indeks jest wiêkszy od zera oraz indeks jest mniejszy od rozmiaru kontenera
			//z zestawem (nie mo¿na przekroczyæ rozmiaru nowego kontenera)
			//i w nowym zestawie (parametr), pod tym indeksem jest animacja
			if ((index >= 0) && (index < new_anims.size()) && (new_anims[index].GetAnimation() != NULL))
			{
				//zapamiêtujê czas trwania bie¿¹cej animacji
				float currTime = GetDisplayableBody()->GetAnimationState()->GetCurrentTime();
				
				//podmieniam star¹ animacjê ze starego zestawu na now¹ animacjê z nowego zestawu
				SetAnimationBody(new_anims[index].GetAnimation());
				
				//przewijam animacjê do "czasu", w którym rozpocz¹³ siê proces podmiany animacji
				GetDisplayableBody()->GetAnimationState()->RewindTo(currTime);
			}
		}
	}

	//metoda pomocnicza - metoda ustawia zestaw animacji - head
	void CActor::SetAnimSetHead(CAnimSet *anim_set)
	{
		//jeœli zestaw animacji jest zainicjowany
		if (p_anim_set)//head
		{
			//p³ynna zmiana animacji - head
			CAnimation *curr_anim = GetAnimationHead();

			//kontener przechowuj¹cy stary (dotychczasowy) zestaw animacji
			const std::vector<CNameAnimPairTranslator> &old_anims = p_anim_set->GetAnims();
			
			//kontener przechowuj¹cy nowy (parametr tej metody) zestaw animacji
			const std::vector<CNameAnimPairTranslator> &new_anims = anim_set->GetAnims();
	        
			//indeks, pod którym mo¿e znajdowaæ siê szukana animacja
			unsigned int index = -1;
	        
			//przeszukujê stary zestaw animacji, aby odszukaæ w nim animacjê do podmiany
			for (unsigned int i = 0; i < old_anims.size(); i++)
			{
				//jeœli znalaz³em szukan¹ animacjê w starym (dotychczasowym) kontenerze
				if (old_anims[i].GetAnimation() == curr_anim)
				{
					index = i;	//zapamiêtujê pod jakim jest indeksem w kontenerze
					break;		//i przerywam przeszukiwanie
				}
			}

			//jeœli indeks jest wiêkszy od zera oraz indeks jest mniejszy od rozmiaru kontenera
			//z zestawem (nie mo¿na przekroczyæ rozmiaru nowego kontenera)
			//i w nowym zestawie (parametr), pod tym indeksem jest animacja
			if ((index >= 0) && (index < new_anims.size()) && (new_anims[index].GetAnimation() != NULL))
			{
				//zapamiêtujê czas trwania bie¿¹cej animacji
				float currTime = GetDisplayableHead()->GetAnimationState()->GetCurrentTime();
				
				//podmieniam star¹ animacjê ze starego zestawu na now¹ animacjê z nowego zestawu
				SetAnimationHead(new_anims[index].GetAnimation());
				
				//przewijam animacjê do "czasu", w którym rozpocz¹³ siê proces podmiany animacji
				GetDisplayableHead()->GetAnimationState()->RewindTo(currTime);
			}
		}
	}

	//metoda aktualizuje animacje w zale¿noœci od stanu logiki obiektu
	void CActor::UpdateAnimations(float dt)
	{
		//jeœli energia bêdzie mniejsza do 50
		//podmianiamy zestaw animacji (w przyk³adzie czêœæ body)
		if(m_energy < 50)//mamy ma³o energii - obiekt podmienia animacje
			if(p_anim_set)
				SetAnimationBody(p_anim_set->GetMoveAnimBody());
	}
}//namespace logic
