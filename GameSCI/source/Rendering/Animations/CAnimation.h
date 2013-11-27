/*
 ___________________________________
| CAnimation.h - definicja klasy.   |
| SCI - March 2012.                 |
|___________________________________|

*/

#ifndef H_ANIMATION_SCI
#define H_ANIMATION_SCI

#include "CTimedAnimationFrame.h"
#include <vector>
#include <string>
namespace rendering
{
	namespace animation
	{
		///
		///Klasa reprezentuje pojemnik na animacje
		///
		class CAnimation
		{

		public:

			///
			///Konstruktor domyœlny
			///
			CAnimation(void);

			///
			///Konstruktor kopiuj¹cy
			///
			///@param CAnimationCopy - parametr - obiekt klasy CAnimation
			///
			CAnimation(const CAnimation& CAnimationCopy);

			///
			///Destruktor
			///
			~CAnimation(void);

			///
			///Metoda zwraca referencjê na nazwê animacji
			///
			const std::string& GetAnimationName() const;

			///
			///Metoda ustawia na nazwê animacji
			///
			///@param name - nazwa animacji
			///
			const void SetAnimationName(std::string anim_name);

			///
			///Metoda zwraca czas równy ca³kowitej d³ugoœci trwania wszystkich klatek animacji (kumulacja)
			///
			float TotalLength();

		private:

			std::string m_animation_name;				//nazwa animacji

		public:

			std::vector<CTimedAnimationFrame> m_frames;	//wektor przechowuj¹cy klatki animacji
		};
	}//namespace animation
}//namespace rendering
#endif//H_ANIMATION_SCI