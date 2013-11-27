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
		///Klasa reprezentuje mechanizm zamiany nazwy animacji na jej wska�nik
		///
		class CNameAnimPairTranslator
		{

		public:
			
			///
			///Konstruktor domy�lny
			///
			CNameAnimPairTranslator(void);

			///
			///Konstruktor kopiuj�cy
			///
			///@param CNameAnimPairTranslatorCopy - parametr - obiekt klasy CNameAnimPairTranslator
			///
			CNameAnimPairTranslator(const CNameAnimPairTranslator& CNameAnimPairTranslatorCopy);

			///
			///Konstruktor parametryczny
			///
			///@param &m_animation_name - sta�a referencja na nazw� animacji
			///
			CNameAnimPairTranslator(const std::string &animation_name);
			
			///
			///Destruktor
			///
			~CNameAnimPairTranslator(void);

			///
			///Metoda zwraca wska�nik na animacj�
			///
			CAnimation * GetAnimation() const;

			///
			///Metoda wstawia animacj� do s�ownika
			///
			///@param *p_anim - wska�nik na animacj�
			///
			void SetAnim(CAnimation *p_anim);

			///
			///Metoda zwraca referencj� na nazw� animacji
			///
			std::string& GetAnimationName();

			///
			///Metoda zwraca flag�, czy obiekt jest gotowy do u�ycia
			///
			const bool GetReady() const;

		private:

			std::string		m_animation_name;	//nazwa animacji
			CAnimation*		p_animation;		//wska�nik na animacj�
			bool			m_is_ready;			//flaga, czy wska�nik
												//na animacj� (p_animation) jest zainicjowany,
												//czy animacja jest gotowa do u�ycia
		};
	}//namespace animation
}//namespace rendering
#endif //H_NAME_ANIM_PAIR_TRANSLATOR_SCI