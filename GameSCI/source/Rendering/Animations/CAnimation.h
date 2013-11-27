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
			///Konstruktor domy�lny
			///
			CAnimation(void);

			///
			///Konstruktor kopiuj�cy
			///
			///@param CAnimationCopy - parametr - obiekt klasy CAnimation
			///
			CAnimation(const CAnimation& CAnimationCopy);

			///
			///Destruktor
			///
			~CAnimation(void);

			///
			///Metoda zwraca referencj� na nazw� animacji
			///
			const std::string& GetAnimationName() const;

			///
			///Metoda ustawia na nazw� animacji
			///
			///@param name - nazwa animacji
			///
			const void SetAnimationName(std::string anim_name);

			///
			///Metoda zwraca czas r�wny ca�kowitej d�ugo�ci trwania wszystkich klatek animacji (kumulacja)
			///
			float TotalLength();

		private:

			std::string m_animation_name;				//nazwa animacji

		public:

			std::vector<CTimedAnimationFrame> m_frames;	//wektor przechowuj�cy klatki animacji
		};
	}//namespace animation
}//namespace rendering
#endif//H_ANIMATION_SCI