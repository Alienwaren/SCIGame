/*
 ____________________________________________________
| CNameAnimPairTranslator.cpp - implementacja klasy. |
| SCI - March 2012.                                  |
|____________________________________________________|

*/

#include "CNameAnimPairTranslator.h"
#include "CAnimation.h"

namespace rendering
{
	namespace animation
	{

		//Konstruktor domy�lny
		CNameAnimPairTranslator::CNameAnimPairTranslator(void)
		:
			m_animation_name	(""),
			p_animation			(NULL),
			m_is_ready			(false)
		{
		}
		
		//Konstruktor kopiuj�cy
		CNameAnimPairTranslator::CNameAnimPairTranslator(const CNameAnimPairTranslator& CNameAnimPairTranslatorCopy)
		:
			m_animation_name	(CNameAnimPairTranslatorCopy.m_animation_name),
			p_animation			(CNameAnimPairTranslatorCopy.p_animation),
			m_is_ready			(CNameAnimPairTranslatorCopy.m_is_ready)
		{
		}

		//Konstruktor parametryczny
		CNameAnimPairTranslator::CNameAnimPairTranslator(const std::string &animation_name)
		:
			m_animation_name	(animation_name),
			p_animation			(NULL),
			m_is_ready			(false)
		{
		}

		//Destruktor
		CNameAnimPairTranslator::~CNameAnimPairTranslator(void)
		{
			m_animation_name	= "";
			p_animation			= NULL;
			m_is_ready			= false;
		}

		//Metoda zwraca wska�nik na animacj�
		CAnimation * CNameAnimPairTranslator::GetAnimation() const
		{
			return p_animation;
		}

		//Metoda wstawia animacj� do s�ownika
		void CNameAnimPairTranslator::SetAnim(CAnimation *p_anim)
		{
			p_animation = p_anim;
			m_is_ready = true;
		}

		//Metoda zwraca referencj� na nazw� animacji
		std::string& CNameAnimPairTranslator::GetAnimationName()
		{
			return m_animation_name;
		}

		//Metoda zwraca flag�, czy obiekt jest gotowy do u�ycia
		const bool CNameAnimPairTranslator::GetReady() const
		{
			return m_is_ready;
		}

	}//namespace animation
}//namespace rendering