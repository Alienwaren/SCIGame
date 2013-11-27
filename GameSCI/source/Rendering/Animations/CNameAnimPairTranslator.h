/*
 ____________________________________________________
| CNameAnimPairTranslator.h - definicja klasy.       |
| SCI - March 2012.                                  |
|____________________________________________________|

*/

#ifndef H_NAME_ANIM_PAIR_TRANSLATOR_SCI
#define H_NAME_ANIM_PAIR_TRANSLATOR_SCI

#include <string>

namespace rendering
{
	namespace animation
	{
		///
		///Forward declaration
		///
		class CAnimation;

		///
		///Klasa reprezentuje mechanizm zamiany nazwy animacji na jej wskaŸnik
		///
		class CNameAnimPairTranslator
		{

		public:
			
			///
			///Konstruktor domyœlny
			///
			CNameAnimPairTranslator(void);

			///
			///Konstruktor kopiuj¹cy
			///
			///@param CNameAnimPairTranslatorCopy - parametr - obiekt klasy CNameAnimPairTranslator
			///
			CNameAnimPairTranslator(const CNameAnimPairTranslator& CNameAnimPairTranslatorCopy);

			///
			///Konstruktor parametryczny
			///
			///@param &m_animation_name - sta³a referencja na nazwê animacji
			///
			CNameAnimPairTranslator(const std::string &animation_name);
			
			///
			///Destruktor
			///
			~CNameAnimPairTranslator(void);

			///
			///Metoda zwraca wskaŸnik na animacjê
			///
			CAnimation * GetAnimation() const;

			///
			///Metoda wstawia animacjê do s³ownika
			///
			///@param *p_anim - wskaŸnik na animacjê
			///
			void SetAnim(CAnimation *p_anim);

			///
			///Metoda zwraca referencjê na nazwê animacji
			///
			std::string& GetAnimationName();

			///
			///Metoda zwraca flagê, czy obiekt jest gotowy do u¿ycia
			///
			const bool GetReady() const;

		private:

			std::string		m_animation_name;	//nazwa animacji
			CAnimation*		p_animation;		//wskaŸnik na animacjê
			bool			m_is_ready;			//flaga, czy wskaŸnik
												//na animacjê (p_animation) jest zainicjowany,
												//czy animacja jest gotowa do u¿ycia
		};
	}//namespace animation
}//namespace rendering
#endif //H_NAME_ANIM_PAIR_TRANSLATOR_SCI