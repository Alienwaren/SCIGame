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

		//Konstruktor domyœlny
		CAnimationState::CAnimationState(void)
		:
			m_current_time		(0),
			m_anim_speed		(1.0f),
			m_is_looped			(true),
			m_is_paused			(false),
			p_animation			(NULL)
		{
		}

		//Konstruktor kopiuj¹cy
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

		//Metoda zwraca czas, który up³yn¹³
		const float CAnimationState::GetCurrentTime() const
		{
			return m_current_time;
		}

		//Metoda ustawia up³ywaj¹cy czas (up³yw czasu)
		void CAnimationState::SetCurrentTime (float current_time)
		{
			m_current_time = current_time;
		}

		//Metoda zwraca wspó³czynnik prêdkoœci odtwarzania animacji 1.0f - normal speed
		const float CAnimationState::GetAnimSpeed() const
		{
			return m_anim_speed;
		}

		//Metoda ustawia wspó³czynnik prêdkoœci odtwarzania animacji 1.0f - normal speed
		void CAnimationState::SetAnimSpeed(float anim_speed)
		{
			m_anim_speed = anim_speed;
		}

		//Motoda zwraca flagê, czy animacji jest w trybie zapêtlenia (loop)
		const bool CAnimationState::GetLooped() const
		{
			return m_is_looped;
		}

		//Motoda ustawia flagê, animacji - tryb zapêtlenia (loop)
		void CAnimationState::SetLooped(bool is_looped)
		{
			m_is_looped = is_looped;
		}

		//Motoda zwraca flagê, animacji - stan pause
		const bool CAnimationState::GetPaused() const
		{
			return m_is_paused;
		}

		//Motoda ustawia flagê, animacji - stan pause
		void CAnimationState::SetPaused (bool is_paused)
		{
			m_is_paused = is_paused;
		}

		//Metoda zwraca wskaŸnik na obiekt klasy CAnimation
		CAnimation* CAnimationState::GetAnimation()
		{
			return p_animation;
		}

		//Metoda ustawia wskaŸnik na animacjê - obiekt klasy CAnimation
		void CAnimationState::SetAnimation(CAnimation* animation)
		{
			p_animation = animation;
		}

		//Metoda dodaje czas do odtwarzania animacji
		void CAnimationState::AddTime(float time)
		{
			//kumulujemy up³ywaj¹cy czas
			m_current_time += time * m_anim_speed;				//G³ówna idea - "oszczêdzamy" czas

			float animationLength = p_animation->TotalLength();	//d³ugoœæ animacji to czas równy
																//ca³kowitej sumie czasów trwania wszystkich
																//jej klatek animacji - suma poszczególnych czasów ka¿dej klatki

			if (m_is_looped)									//jeœli animacja pracuje w trybie zapêtlenia (loop)
			{
				if (animationLength > 0.0f)						//jeœli czas trwania animacji jest dodatni
				{
					//jeœli skumulowany czas jest wiêkszy ni¿ ca³kowity czas trwania animacji
					//wchodzimy w pêtlê...
					while (m_current_time > animationLength)	//dopóki up³ywaj¹cy czas jest wiêkszy
																//od czasu d³ugoœci trwania ca³ej animacji
						m_current_time -= animationLength;		//zmniejszam czas trwania animacji
																//rekumulacja...
				}
				else											//w przeciwnym wypadku, zerujemy up³ywaj¹cy czas												
					m_current_time = 0.0f;
			}
			else												//animacja pracuje w trybie bez zapêtlenia
			{
				if (m_current_time > animationLength)			//jeœli czas, który up³yn¹³ jest wiêkszy
																//od czasu trwania animacji - to czas, który up³yn¹³
					m_current_time = animationLength;			//jest równy czasowi trwania animacji (reset)
			}
		}
		
		//Metoda zwraca sta³¹ referencjê na kolejn¹ (nastêpn¹) klatkê animacji
		const CAnimationFrame& CAnimationState::GetCurrentFrame()
		{
			if (p_animation->m_frames.empty())								//jeœli w kontenerze nie ma klatek animacji
					return gNullFrame;										//zwracamy pust¹ animacjê

			size_t candidate = 0;											//kolejna klatka animacji do odtwarzania
			for (size_t i = p_animation->m_frames.size()-1; i>0; i--)		//przeszukujemy kontener z klatkami animacji
			{
				if (p_animation->m_frames[i-1].GetFrameTime() < m_current_time)
																			//jeœli czas  odtwarzania klatki z kontenera
																			//jest mniejszy ni¿ bie¿¹cy czas
																			//(skoñczy³ siê czas jej ekspozycji)
				{
					candidate = i;											//to nastêpn¹ klatk¹ do ekspozycji
					break;													//jest kolejna klatka - przerywamy iterowanie
				}
			}
			return p_animation->m_frames[candidate].GetAnimationFrame();	//zwracamy j¹, jako kolejn¹ do odtwarzania
		}

		//Metoda uruchamia animacjê
		void CAnimationState::Play()
		{
			m_is_paused = false;
		}

		//Metoda zatrzymuje animacjê
		void CAnimationState::Stop()
		{
			 m_is_paused = true;
		}
		
		//Metoda przewija sekwencjê animacji do zadanej pozycji (czasu)
		void CAnimationState::RewindTo(float position) // 0.0 - poczatek animacji, 1.0 - koniec
		{
			if (position < 0.0f) position = 0.0f;
			if (position > 1.0f) position = 1.0f;

			float animationLength = p_animation->TotalLength();
			m_current_time = animationLength * position;
		}
	}//namespace animation
}//namespace rendering
