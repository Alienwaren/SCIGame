/*
 _________________________________________________
| CTimedAnimationFrame.h - definicja klasy.       |
| SCI - by Jack March 2012.                       |
|_________________________________________________|

*/

#ifndef H_TIMED_ANIMATION_FRAME_SCI
#define H_TIMED_ANIMATION_FRAME_SCI

#include "CAnimationFrame.h"

namespace rendering
{
	namespace animation
	{
		///
		///Klasa reprezentuje klatk� animacji wraz z czasem jej ekspozycji
		///
		class CTimedAnimationFrame
		{

		public:

			///
			///Konstruktor domy�lny
			///
			CTimedAnimationFrame(void);

			///
			///Konstruktor kopiuj�cy
			///
			///@param CTimedAnimationFrameCopy - parametr - obiekt klasy CTimedAnimationFrame
			///
			CTimedAnimationFrame(const CTimedAnimationFrame& CTimedAnimationFrameCopy);

			///
			///Konstruktor paramatryczny
			///
			///@param time - czas
			///
			///@param &frame - sta�a referencja na obiekt klasy CAnimationFrame
			///
			CTimedAnimationFrame(float time, const CAnimationFrame& frame);

			///
			///Destruktor
			///
			~CTimedAnimationFrame(void);

			///
			///Metoda zwraca czas odtwarzania klatki animacji
			///
			float GetFrameTime();

			///
			///Metoda zwraca referencj� klatki animacji - referencja do obiektu klasy CAnimationFrame
			///
			CAnimationFrame &GetAnimationFrame();

		private:

			CAnimationFrame m_frame;		//klatka animacji - obiekt klasy CAnimationFrame
			float			m_time;			//czas ekspozycji klatki animacji
		};
	}//namespace animation
}//namespace rendering
#endif//H_TIMED_ANIMATION_FRAME_SCI
