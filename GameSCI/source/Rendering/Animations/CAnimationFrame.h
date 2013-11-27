/*
 ______________________________________
| CAnimationFrame.h - definicja klasy. |
| SCI - March 2012.                    |
|______________________________________|

*/

#ifndef H_ANIMATION_FRAME_SCI
#define H_ANIMATION_FRAME_SCI

#include <string>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>

namespace rendering
{
	namespace animation
	{
		///
		///Klasa reprezentuje klatkê animacji
		///
		class CAnimationFrame
		{

		public:

			///
			///Konstruktor domyœlny
			///
			CAnimationFrame(void);

			///
			///Konstruktor parametryczny
			///
			///@param texture_name - nazwa tekstury
			///
			///@param rect - prostoktny obszar - rozmiar tekstury
			///
			CAnimationFrame(const std::string& texture_name, const sf::IntRect&	rectangle = sf::IntRect(0,0,0,0));

			///
			///Konstruktor kopiuj¹cy
			///
			///@param CAnimationFrameCopy - sta³a referencja na obiekt klasy CAnimationFrame
			///
			CAnimationFrame(const CAnimationFrame& CAnimationFrameCopy);

			///
			///Destruktor
			///
			~CAnimationFrame(void);

			///
			///Metoda zwraca sta³¹ referencjê na nazwê tekstury std::string
			///
			const std::string& GetTextureName() const;

			///
			///Metoda zwraca sta³¹ referencjê na prostok¹tny obszar tekstury sf::IntRect
			///
			const sf::IntRect& GetImageRectangle() const;

		private:

			std::string		m_texture_name;	//nazwa tekstury
			sf::IntRect		m_rectangle;	//prostok¹tny obszar tekstury
		};
	}//namespace animation
}//namespace rendering
#endif //H_ANIMATION_FRAME_SCI