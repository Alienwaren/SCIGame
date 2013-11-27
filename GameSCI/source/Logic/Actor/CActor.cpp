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
	//Chroniony konstruktor domy�lny
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

	//Chroniony konstruktor kopiuj�cy
	CActor::CActor(const CActor &CActorCopy)
	:
		CPhysical		(CActorCopy),//konstruktor kopiuj�cy klasy bazowej
		p_anim_set		(CActorCopy.p_anim_set),
		m_energy		(CActorCopy.m_energy),
		m_mass			(CActorCopy.m_mass),
		m_temperature	(CActorCopy.m_temperature),
		m_speed			(CActorCopy.m_speed),
		m_movabled		(CActorCopy.m_movabled),
		m_is_move		(CActorCopy.m_is_move)
	{
	}

	//Chroniony destruktor wirtualny - u�ywany wy��cznie przez CPhysicalManager
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

	//Metoda zwraca mas� obiektu
	const float CActor::getEnergy() const
	{
		return m_energy;
	}

	//Metoda zwraca mas� obiektu
	const void CActor::setEnergy(float energy)
	{
		if (energy < 0) return;
		m_energy = energy;
	}

	//Metoda ustawia mas� obiektu
	const void CActor::setMass(float mass)
	{
		if (mass < 0) return;
		m_mass = mass;
	}

	//Metoda zwraca temperatur� obiektu
	const float CActor::getTemperature() const
	{
		return m_temperature;
	}

	//Metoda ustawia temperatur� obiektu
	const void CActor::setTemperature(float temperature)
	{
		m_temperature = temperature;
	}

	//Metoda zwraca flag�, czy obiekt si� porusza
	bool const CActor::getIsMove() const
	{
		return m_is_move;
	}

	//Metoda ustawia flag�, �e obiekt si� porusza
	const void CActor::setIsMove(bool is_move)
	{
		m_is_move = is_move;
	}

	//Metoda zwraca flag�, czy obiekt mo�e si� przemieszcza�
	const bool CActor::getIsMovabled() const
	{
		return m_movabled;
	}

	//Metoda ustawia flag�, czy obiekt mo�e si� przemieszcza�
	const void CActor::setIsMovabled(bool movabled)
	{
		m_movabled = movabled;
	}

	//Metoda zwraca pr�dko�� obiektu
	const float CActor::getSpeed() const
	{
		return m_speed;
	}

	//Metoda ustawia pr�dko�� obiektu
	const void CActor::setSpeed(float speed)
	{
		if (speed < 0) return;
		m_speed = speed;
	}

	//Metoda zwraca wska�nik na zestaw animacji
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

	//Wirtualan metoda zabija obiekt klasy CActor i wywo�uje odpowiednie czynno�ci z tym zwi�zane
	void CActor::Kill()
	{
		//p�ki co b�dzie si� wywo�ywa�a metoda klasy bazowej
		CPhysical::Kill();
		//to do...
	}

	//Wirtualna metoda aktualizuj�ca obiekt
	void CActor::Update(float dt)
	{
		CPhysical::Update(dt);			//aktualizacja klasy bazowej
		m_energy = m_energy - 0.05f;	//aktualizujemy energi�...(zmniejszamy)
										//warto�� pocz�tkowa by�a ustawiona na 100
		
		//poni�sza metoda podmienia zestaw animacji w zale�no�ci od energii
		UpdateAnimations(dt);

		//Wniosek:
		//gdy stan obiektu (energia, kondycja, lub inne stany) obiektu
		//si� zmieni�, mo�emy podmiania� zestawy animacji, aby to zobrazowa�...
		//np. zestaw animacji (normalny, obiekt si� przemieszcza, animacja uszkodze�, itp...)
	}

	//implementajca metod private:

	//metoda ustawia zestaw animacji - body
	void CActor::SetAnimSetBody(CAnimSet *anim_set)
	{
		//je�li zestaw animacji jest zainicjowany
		if (p_anim_set)//body
		{
			//p�ynna zmiana animacji - body
			CAnimation *curr_anim = GetAnimationBody();

			//kontener przechowuj�cy stary (dotychczasowy) zestaw animacji
			const std::vector<CNameAnimPairTranslator> &old_anims = p_anim_set->GetAnims();
			
			//kontener przechowuj�cy nowy (parametr tej metody) zestaw animacji
			const std::vector<CNameAnimPairTranslator> &new_anims = anim_set->GetAnims();
	        
			//indeks, pod kt�rym mo�e znajdowa� si� szukana animacja
			unsigned int index = -1;
	        
			//przeszukuj� stary zestaw animacji, aby odszuka� w nim animacj� do podmiany
			for (unsigned int i = 0; i < old_anims.size(); i++)
			{
				//je�li znalaz�em szukan� animacj� w starym (dotychczasowym) kontenerze
				if (old_anims[i].GetAnimation() == curr_anim)
				{
					index = i;	//zapami�tuj� pod jakim jest indeksem w kontenerze
					break;		//i przerywam przeszukiwanie
				}
			}

			//je�li indeks jest wi�kszy od zera oraz indeks jest mniejszy od rozmiaru kontenera
			//z zestawem (nie mo�na przekroczy� rozmiaru nowego kontenera)
			//i w nowym zestawie (parametr), pod tym indeksem jest animacja
			if ((index >= 0) && (index < new_anims.size()) && (new_anims[index].GetAnimation() != NULL))
			{
				//zapami�tuj� czas trwania bie��cej animacji
				float currTime = GetDisplayableBody()->GetAnimationState()->GetCurrentTime();
				
				//podmieniam star� animacj� ze starego zestawu na now� animacj� z nowego zestawu
				SetAnimationBody(new_anims[index].GetAnimation());
				
				//przewijam animacj� do "czasu", w kt�rym rozpocz�� si� proces podmiany animacji
				GetDisplayableBody()->GetAnimationState()->RewindTo(currTime);
			}
		}
	}

	//metoda pomocnicza - metoda ustawia zestaw animacji - head
	void CActor::SetAnimSetHead(CAnimSet *anim_set)
	{
		//je�li zestaw animacji jest zainicjowany
		if (p_anim_set)//head
		{
			//p�ynna zmiana animacji - head
			CAnimation *curr_anim = GetAnimationHead();

			//kontener przechowuj�cy stary (dotychczasowy) zestaw animacji
			const std::vector<CNameAnimPairTranslator> &old_anims = p_anim_set->GetAnims();
			
			//kontener przechowuj�cy nowy (parametr tej metody) zestaw animacji
			const std::vector<CNameAnimPairTranslator> &new_anims = anim_set->GetAnims();
	        
			//indeks, pod kt�rym mo�e znajdowa� si� szukana animacja
			unsigned int index = -1;
	        
			//przeszukuj� stary zestaw animacji, aby odszuka� w nim animacj� do podmiany
			for (unsigned int i = 0; i < old_anims.size(); i++)
			{
				//je�li znalaz�em szukan� animacj� w starym (dotychczasowym) kontenerze
				if (old_anims[i].GetAnimation() == curr_anim)
				{
					index = i;	//zapami�tuj� pod jakim jest indeksem w kontenerze
					break;		//i przerywam przeszukiwanie
				}
			}

			//je�li indeks jest wi�kszy od zera oraz indeks jest mniejszy od rozmiaru kontenera
			//z zestawem (nie mo�na przekroczy� rozmiaru nowego kontenera)
			//i w nowym zestawie (parametr), pod tym indeksem jest animacja
			if ((index >= 0) && (index < new_anims.size()) && (new_anims[index].GetAnimation() != NULL))
			{
				//zapami�tuj� czas trwania bie��cej animacji
				float currTime = GetDisplayableHead()->GetAnimationState()->GetCurrentTime();
				
				//podmieniam star� animacj� ze starego zestawu na now� animacj� z nowego zestawu
				SetAnimationHead(new_anims[index].GetAnimation());
				
				//przewijam animacj� do "czasu", w kt�rym rozpocz�� si� proces podmiany animacji
				GetDisplayableHead()->GetAnimationState()->RewindTo(currTime);
			}
		}
	}

	//metoda aktualizuje animacje w zale�no�ci od stanu logiki obiektu
	void CActor::UpdateAnimations(float dt)
	{
		//je�li energia b�dzie mniejsza do 50
		//podmianiamy zestaw animacji (w przyk�adzie cz�� body)
		if(m_energy < 50)//mamy ma�o energii - obiekt podmienia animacje
			if(p_anim_set)
				SetAnimationBody(p_anim_set->GetMoveAnimBody());
	}
}//namespace logic
