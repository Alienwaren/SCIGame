/*
 ____________________________________________
| CAnimationState.cpp - implementacja klasy. |
| SCI - March 2012.                          |
|____________________________________________|

*/

#include "CAnimationState.h"
#include "CAnimation.h"

namespace rendering
{
	namespace animation
	{
		//Pusta klatka animacji i nadanie jej nazwy
		CAnimationFrame gNullFrame = CAnimationFrame("NULL_ANIMATION");

		//Konstruktor domy�lny
		CAnimationState::CAnimationState(void)
		:
			m_current_time		(0),
			m_anim_speed		(1.0f),
			m_is_looped			(true),
			m_is_paused			(false),
			p_animation			(NULL)
		{
		}

		//Konstruktor kopiuj�cy
		CAnimationState::CAnimationState(const CAnimationState& CAnimationStateCopy)
		:
			m_current_time		(CAnimationStateCopy.m_current_time),
			m_anim_speed		(CAnimationStateCopy.m_anim_speed),
			m_is_looped			(CAnimationStateCopy.m_is_looped),
			m_is_paused			(CAnimationStateCopy.m_is_paused),
			p_animation			(CAnimationStateCopy.p_animation)
		{
		}

		//Konstruktor parametryczny
		CAnimationState::CAnimationState(CAnimation* animation)
		:
			m_current_time		(0),
			m_anim_speed		(1.0f),
			m_is_looped			(true),
			m_is_paused			(false),
			p_animation			(animation)
		{
		}

		//Destruktor
		CAnimationState::~CAnimationState(void)
		{
			m_current_time		= 0;
			m_anim_speed		= 0.0f;
			m_is_looped			= true;
			m_is_paused			= false;
			p_animation			= NULL;
		}

		//Metoda zwraca czas, kt�ry up�yn��
		const float CAnimationState::GetCurrentTime() const
		{
			return m_current_time;
		}

		//Metoda ustawia up�ywaj�cy czas (up�yw czasu)
		void CAnimationState::SetCurrentTime (float current_time)
		{
			m_current_time = current_time;
		}

		//Metoda zwraca wsp�czynnik pr�dko�ci odtwarzania animacji 1.0f - normal speed
		const float CAnimationState::GetAnimSpeed() const
		{
			return m_anim_speed;
		}

		//Metoda ustawia wsp�czynnik pr�dko�ci odtwarzania animacji 1.0f - normal speed
		void CAnimationState::SetAnimSpeed(float anim_speed)
		{
			m_anim_speed = anim_speed;
		}

		//Motoda zwraca flag�, czy animacji jest w trybie zap�tlenia (loop)
		const bool CAnimationState::GetLooped() const
		{
			return m_is_looped;
		}

		//Motoda ustawia flag�, animacji - tryb zap�tlenia (loop)
		void CAnimationState::SetLooped(bool is_looped)
		{
			m_is_looped = is_looped;
		}

		//Motoda zwraca flag�, animacji - stan pause
		const bool CAnimationState::GetPaused() const
		{
			return m_is_paused;
		}

		//Motoda ustawia flag�, animacji - stan pause
		void CAnimationState::SetPaused (bool is_paused)
		{
			m_is_paused = is_paused;
		}

		//Metoda zwraca wska�nik na obiekt klasy CAnimation
		CAnimation* CAnimationState::GetAnimation()
		{
			return p_animation;
		}

		//Metoda ustawia wska�nik na animacj� - obiekt klasy CAnimation
		void CAnimationState::SetAnimation(CAnimation* animation)
		{
			p_animation = animation;
		}

		//Metoda dodaje czas do odtwarzania animacji
		void CAnimationState::AddTime(float time)
		{
			//kumulujemy up�ywaj�cy czas
			m_current_time += time * m_anim_speed;				//G��wna idea - "oszcz�dzamy" czas

			float animationLength = p_animation->TotalLength();	//d�ugo�� animacji to czas r�wny
																//ca�kowitej sumie czas�w trwania wszystkich
																//jej klatek animacji - suma poszczeg�lnych czas�w ka�dej klatki

			if (m_is_looped)									//je�li animacja pracuje w trybie zap�tlenia (loop)
			{
				if (animationLength > 0.0f)						//je�li czas trwania animacji jest dodatni
				{
					//je�li skumulowany czas jest wi�kszy ni� ca�kowity czas trwania animacji
					//wchodzimy w p�tl�...
					while (m_current_time > animationLength)	//dop�ki up�ywaj�cy czas jest wi�kszy
																//od czasu d�ugo�ci trwania ca�ej animacji
						m_current_time -= animationLength;		//zmniejszam czas trwania animacji
																//rekumulacja...
				}
				else											//w przeciwnym wypadku, zerujemy up�ywaj�cy czas												
					m_current_time = 0.0f;
			}
			else												//animacja pracuje w trybie bez zap�tlenia
			{
				if (m_current_time > animationLength)			//je�li czas, kt�ry up�yn�� jest wi�kszy
																//od czasu trwania animacji - to czas, kt�ry up�yn��
					m_current_time = animationLength;			//jest r�wny czasowi trwania animacji (reset)
			}
		}
		
		//Metoda zwraca sta�� referencj� na kolejn� (nast�pn�) klatk� animacji
		const CAnimationFrame& CAnimationState::GetCurrentFrame()
		{
			if (p_animation->m_frames.empty())								//je�li w kontenerze nie ma klatek animacji
					return gNullFrame;										//zwracamy pust� animacj�

			size_t candidate = 0;											//kolejna klatka animacji do odtwarzania
			for (size_t i = p_animation->m_frames.size()-1; i>0; i--)		//przeszukujemy kontener z klatkami animacji
			{
				if (p_animation->m_frames[i-1].GetFrameTime() < m_current_time)
																			//je�li czas  odtwarzania klatki z kontenera
																			//jest mniejszy ni� bie��cy czas
																			//(sko�czy� si� czas jej ekspozycji)
				{
					candidate = i;											//to nast�pn� klatk� do ekspozycji
					break;													//jest kolejna klatka - przerywamy iterowanie
				}
			}
			return p_animation->m_frames[candidate].GetAnimationFrame();	//zwracamy j�, jako kolejn� do odtwarzania
		}

		//Metoda uruchamia animacj�
		void CAnimationState::Play()
		{
			m_is_paused = false;
		}

		//Metoda zatrzymuje animacj�
		void CAnimationState::Stop()
		{
			 m_is_paused = true;
		}
		
		//Metoda przewija sekwencj� animacji do zadanej pozycji (czasu)
		void CAnimationState::RewindTo(float position) // 0.0 - poczatek animacji, 1.0 - koniec
		{
			if (position < 0.0f) position = 0.0f;
			if (position > 1.0f) position = 1.0f;

			float animationLength = p_animation->TotalLength();
			m_current_time = animationLength * position;
		}
	}//namespace animation
}//namespace rendering
