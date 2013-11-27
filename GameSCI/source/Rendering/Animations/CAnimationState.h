/*
 ____________________________________________
| CAnimationState.h - definicja klasy.       |
| SCI - March 2012.                          |
|____________________________________________|

*/

#ifndef H_ANIMATION_STATE_SCI
#define H_ANIMATION_STATE_SCI

#include "CAnimationFrame.h"

namespace rendering
{
	namespace animation
	{
		///
		///Forward declaration
		///
		class CAnimation;

		///
		///Klasa reprezentuje funkcjonalny obiekt animowany
		///
		class CAnimationState
		{

		public:

			///
			///Konstruktor domy�lny
			///
			CAnimationState(void);

			///
			///Konstruktor kopiuj�cy
			///
			///@param &CAnimationStateCopy - parametr - obiekt klasy CAnimationState
			///
			CAnimationState(const CAnimationState& CAnimationStateCopy);

			///
			///Konstruktor parametryczny
			///
			///@param *animation - wska�nik na obiekt klasy CAnimation
			///
			CAnimationState(CAnimation* animation);

			///
			///Destruktor
			///
			~CAnimationState(void);

			///
			///Metoda zwraca czas, kt�ry up�yn��
			///
			const float GetCurrentTime() const;

			///
			///Metoda ustawia up�ywaj�cy czas (up�yw czasu)
			///
			///@param current_time - up�ywaj�cy
			///
			void SetCurrentTime (float current_time);

			///
			///Metoda zwraca wsp�czynnik pr�dko�ci odtwarzania animacji 1.0f - normal speed
			///
			const float GetAnimSpeed() const;

			///
			///Metoda ustawia wsp�czynnik pr�dko�ci odtwarzania animacji 1.0f - normal speed
			///
			///@param anim_speed - wsp�czynnik pr�dko�ci odtwarzania animacji
			///
			void SetAnimSpeed(float anim_speed);

			///
			///Motoda zwraca flag�, czy animacji jest w trybie zap�tlenia (loop)
			///
			const bool GetLooped() const;

			///
			///Motoda ustawia flag�, animacji - tryb zap�tlenia (loop)
			///
			///@param is_looped - tryb zap�tlenia (loop)
			///
			void SetLooped(bool is_looped);

			///
			///Motoda zwraca flag�, animacji - stan pause
			///
			const bool GetPaused() const;

			///
			///Motoda ustawia flag�, animacji - stan pause
			///
			///@param is_paused - flaga animacji - stan pause
			///
			void SetPaused (bool is_paused);

			///
			///Metoda zwraca wska�nik na obiekt klasy CAnimation
			///
			CAnimation* GetAnimation();

			///
			///Metoda ustawia wska�nik na animacj� - obiekt klasy CAnimation
			///
			///@param *animation - wska�nik na obiekt klasy CAnimation (pojemnik na klatki animacji)
			///
			void SetAnimation(CAnimation* animation);

			///
			///Metoda dodaje czas do odtwarzania animacji
			///
			///@param - time - czas
			///
			void AddTime(float time);

			///
			///Metoda zwraca sta�� referencj� na kolejn� (nast�pn�) klatk� animacji
			///
			const CAnimationFrame& GetCurrentFrame();
			
			///
			///Metoda uruchamia animacj�
			///
			void Play();

			///
			///Metoda zatrzymuje animacj�
			///
			void Stop();

			///
			///Metoda przewija sekwencj� animacji do zadanej pozycji (czasu)
			///
			///@param - position - pozycja klatki animacji (0.0 - poczatek animacji, 1.0 - koniec)
			///
			void RewindTo(float position);

		private:

			float		m_current_time;	//up�ywaj�cy czas
			float		m_anim_speed;	//wsp�czynnik pr�dko�ci odtwarzania animacji 1.0f - normal speed
			bool		m_is_looped;	//flaga, czy animacja ma by� odtwarzana jako zap�tlona (loop)
			bool		m_is_paused;	//flaga, czy animacja jest wstrzymana
			CAnimation* p_animation;	//wska�nik na obiekt klasy CAnimation (pojemnik z klatkami)
		};
	}//namespace animation
}//namespace rendering
#endif //H_ANIMATION_STATE_SCI