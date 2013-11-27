/*
 ___________________________________
| CAnimation.cpp - definicja klasy. |
| SCI - March 2012.                 |
|___________________________________|

*/


#include "CAnimation.h"

namespace rendering
{
	namespace animation
	{
		//Konstruktor domyœlny
		CAnimation::CAnimation(void)
		:
			m_animation_name("")
		{
		}

		//Konstruktor kopiuj¹cy
		CAnimation::CAnimation(const CAnimation& CAnimationCopy)
		:
			m_animation_name(CAnimationCopy.m_animation_name)
		{
		}

		//Destruktor
		CAnimation::~CAnimation(void)
		{
			m_animation_name = "";
		}

		//Metoda zwraca referencjê na nazwê animacji
		const std::string& CAnimation::GetAnimationName() const
		{ 
			return m_animation_name;
		}

		//Metoda ustawia na nazwê animacji
		const void CAnimation::SetAnimationName(std::string anim_name)
		{
			m_animation_name = anim_name;
		}

		//Metoda zwraca czas równy ca³kowitej d³ugoœci trwania wszystkich klatek animacji (kumulacja)
		float CAnimation::TotalLength()
		{
			if (m_frames.empty())						//jeœli nie ma klatek, to czas odtwarzania klatki animacji
				return 0.0f;							//jest równy zero
			else
				return m_frames.back().GetFrameTime();	//w przeciwnym wypadku jest to czas odtwarzania
														//(ostatniej) klatki animacji wektora - czyli czas
														//kumulacji poprzednich (suma trwania wszystckich klatek)
		}
	}//namespace animation
}//namespace rendering