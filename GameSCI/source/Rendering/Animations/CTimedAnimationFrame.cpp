/*
 _________________________________________________
| CTimedAnimationFrame.cpp - implementacja klasy. |
| SCI - by Jack March 2012.                       |
|_________________________________________________|

*/

#include "CTimedAnimationFrame.h"

namespace rendering
{
	namespace animation
	{
		//Konstruktor domyœlny
		CTimedAnimationFrame::CTimedAnimationFrame(void)
		:
			m_time	(0.0f),
			m_frame	()
		{
		}

		//Konstruktor kopiuj¹cy
		CTimedAnimationFrame::CTimedAnimationFrame(const CTimedAnimationFrame& CTimedAnimationFrameCopy)
		:
			m_time	(CTimedAnimationFrameCopy.m_time),
			m_frame	(CTimedAnimationFrameCopy.m_frame)
		{
		}

		//Konstruktor paramatryczny
		CTimedAnimationFrame::CTimedAnimationFrame(float time, const CAnimationFrame& frame)
		:
			m_time	(time),
			m_frame	(frame)
		{
		}

		//Destruktor
		CTimedAnimationFrame::~CTimedAnimationFrame(void)
		{
			m_time	= 0.0f;
		}

		//Metoda zwraca czas odtwarzania klatki animacji
		float CTimedAnimationFrame::GetFrameTime()
		{
			return m_time;
		}

		//Metoda zwraca referencjê klatki animacji - referencja do obiektu klasy CAnimationFrame
		CAnimationFrame &CTimedAnimationFrame::GetAnimationFrame()
		{
			return m_frame;
		}
	}//namespace animation
}//namespace rendering
