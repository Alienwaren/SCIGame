/*
 ________________________________________
| CDisplayable.h - definicja klasy       |
| SCI - August 2012.                     |
|________________________________________|

*/

#ifndef H_DISPLAYABLE_SCI
#define H_DISPLAYABLE_SCI

#include "../Drawable/IDrawable.h"
#include "CSprite.h"
#include <string>

///
///Forward declaration
///
namespace sf
{
    class Sprite;
    class RenderWindow;
}

///
///Forward declaration
///
namespace rendering
{
	namespace animation
	{
		class CAnimationState;
		class CAnimationFrame;
		class CAnimation;
	}
}

///
///Forward declaration
///
namespace resource
{
	class CTexture;
}

using namespace rendering::animation;
using namespace resource;
using namespace rendering::drawable;

namespace rendering
{
	namespace displayable
	{
		///
		///Klasa reprezentuje obiekt, który potrafi byæ renderowany (mo¿e byæ tak¿e animowany)
		///
		class CDisplayable : public IDrawable
		{

		public:

			///
			///Konstruktor domyœlny
			///
			CDisplayable();

			///
			///Konstruktor kopiuj¹cy
			///
			///@param &CDisplayableCopy - sta³a referencja na obiekt klasy CDisplayable
			///
			CDisplayable(const CDisplayable& CDisplayableCopy);

			///
			///Destruktor wirtualny
			///
			virtual ~CDisplayable();

			///
			///Metoda zwraca wskaŸnik na obiekt sf::Sprite
			///
			CSprite *GetSprite();

			///
			///Metoda zwraca flagê, czy obiekt mo¿na rysowaæ
			///
			const bool getCanDraw() const;

			///
			///Metoda ustawia flagê, czy obiekt mo¿na rysowaæ
			///
			///@param can_draw - flaga, czy obiekt mo¿na rysowaæ
			///
			const void setCanDraw(bool can_draw);

			///
			///Metoda zwraca flagê, czy obiekt jest widoczny
			///
			const bool getVisible() const;

			///
			///Metoda ustawia flagê, czy obiekt jest widoczny
			///
			///@param visible - flaga, czy obiekt jest widoczny
			///
			const void setVisible(bool visible);

			///
			///Metoda zwraca pozycjê obiektu
			///
			const sf::Vector2f& getPosition() const;

			///
			///Metoda ustawia pozycjê obiektu
			///
			///@param x - wspó³rzêdna x obiektu
			///
			///@param y - wspó³rzêdna y obiektu
			///
			void setPosition(float x, float y);

			///
			//Metoda ustawia pozycjê obiektu
			///
			///@param &vector - referenacja - obiekt klasy sf::Vector2f
			///
			void setPosition(const sf::Vector2f& vector);

			///
			///Metoda zwraca wartoœæ obrotu
			///
			float getRotation() const;
		
			///
			///Metoda ustawia wartoœæ obrotu
			///
			///@param rotation_value - wartoœæ obrotu
			///
			void setRotation(float rotation_value);

			///
			///Metoda obraca wartoœæ obrotu
			///
			///@param angle - wartoœæ obrotu
			///
			void rotate(float angle);

			///
			///Metoda zwraca skalê
			///
			const sf::Vector2f& getScale() const;
		
			///
			///Metoda ustawia skalê
			///
			///@param x - wspó³rzêdna x wektora
			///
			///@param y - wspó³rzêdna y wektora
			///
			void setScale(float x, float y);

			///
			///Metoda ustawia skalê
			///
			///@param &new_scale_value - referencja na obiekt klasy sf::Vector2f
			///
			void setScale(const sf::Vector2f& new_scale_value);

			///
			///Metoda ustawia skalê
			///
			///@param factors - jednolita wartoœæ skaluj¹ca w osi x i y
			///
			void setScale(float factors);

			///
			///Metoda ustawia skalê w stosunku do obecnej skali
			///
			///@param factorX - wspó³czynnik w osi x
			///
			///@param factorY - spó³czynnik w osi y
			///
			void scale(float factorX, float factorY);
			
			///
			///Metoda ustawia skalê w stosunku do obecnej skali
			///
			///@param &factor - sta³a referencja na obiekt klasy sf::Vector2f
			///
			void scale(const sf::Vector2f& factor);

			///
			///Metoda zwraca wspó³rzêdne punktu uchwytu obiektu
			///
			const sf::Vector2f& getOrigin() const;

			///
			///Metoda ustawia wspó³rzêdne punktu uchwytu obiektu
			///
			///@param x - wspó³rzêdna x
			///
			///@param y - wspó³rzêdna y
			///
			void setOrigin(float x, float y);

			///
			///Metoda ustawia wspó³rzêdne punktu uchwytu obiektu
			///
			///@param &origin - sta³a referencja na obiekt klasy sf::Vector2f
			///
			void setOrigin(const sf::Vector2f& origin);

			///
			///Metoda zwraca obszar prostok¹tny zajmowany przez teksturê
			///
			const sf::IntRect& getTextureRect() const;

			///
			///Metoda ustawia obszar prostok¹tny zajmowany przez teksturê
			///
			///@param rectLeft - lewy róg prostok¹tnego obszaru
			///
			///@param rectTop - górny róg prostok¹tnego obszaru
			///
			///@param rectWidth - szerokoœæ prostok¹tnego obszaru
			///
			///@param rectHeight - wysokoœæ prostok¹tnego obszaru
			///
			void setTextureRect(int rectLeft, int rectTop, int rectWidth, int rectHeight);

			///
			///Metoda ustawia obszar prostok¹tny zajmowany przez teksturê
			///
			///@param rectangle - sta³a referencja na obiekt klasy sf::IntRect
			///
			void setTextureRect (const sf::IntRect& rectangle);

			///
			///Metoda zwraca granice obiektu w lokalnym w uk³adzie wspó³rzêdnych
			///
			sf::FloatRect getLocalBounds() const;

			///
			///Metoda zwraca granice obiektu w globalnym w uk³adzie wspó³rzêdnych
			///
			sf::FloatRect getGlobalBounds() const;
			
			///
			///Metoda przemieszcza obiekt o wartoœæ podan¹ w parametrach wzglêdem aktualnej pozycji
			///
			///@param offsetX - wartoœæ przesuniêcia w osi x
			///
			///@param offsetX - wartoœæ przesuniêcia w osi x
			///
			void move(float offsetX, float offsetY);

			///
			///Metoda przemieszcza obiekt o wartoœæ wektora przesuniêcia
			///
			///@param &offset - sta³a referencja na obiekt klasy sf::Vector2f - wektora przesuniêcia
			///
			void move(const sf::Vector2f& offset);

			///
			///Metoda zwraca kolor obiektu
			///
			const sf::Color& getColor() const;

			///
			///Metoda ustawia kolor obiektu
			///
			///@param color - kolor obiektu
			///
			void setColor(const sf::Color& color);

			///
			///Metoda ustawia teksturê obiektu
			///
			///@param &texture_name - sta³a referencja na obiekt std::string - nazwa tekstury
			///
			void setTexture(const std::string& texture_name);

			///
			///Metoda ustawia teksturê obiektu
			///
			///@param *p_texture - wskaŸnik na obiekt klasy CTexture
			///
			void setTexture(CTexture *p_texture);

			///
			///Metoda ustawia animacjê
			///
			///@param &animation_name - sta³a referencja na obiekt std::string - nazwa animacji
			///
			void SetAnimation( const std::string& animation_name );

			///
			///Metoda ustawia animacjê
			///
			///@param *p_animation - wskaŸnik na obiekt klasy CAnimation
			///
			void SetAnimation(CAnimation *p_animation);

			///
			///Metoda zwraca wskaŸnik na obiekt klasy CAnimationState
			///
			CAnimationState* GetAnimationState();

			///
			////Metoda zwraca tryb wyg³adzania tekstury
			///
			const bool getSmoothing() const;

			///
			///Metoda ustawia tryb wyg³adzania tekstury
			///
			///@param smooth - flaga wyg³adzania tekstury
			///
			void setSmoothing(bool smooth);

			///
			///Wirtualna metoda renderuj¹ca obiekt
			///
			///@render render - parametr drawable
			///
			virtual void Draw(sf::RenderWindow* render);
		
		protected:
		
			CSprite*			m_sprite;				//wskaŸnik na obiekt klasy CSprite (kontekst graficzny)
			CAnimationState*	m_animation_state;		//wskaŸnik na obiekt CAnimationState
			bool				m_visible;				//flaga okreœlaj¹cy, czy obiekt jest widoczny
			bool				m_can_draw;				//flaga okreœlaj¹cy, czy mo¿na rysowaæ ten obiekt
			std::string			m_animation_name;		//nazwa animacji
			bool				m_smooth;				//flaga, czy obiekt wyg³adza piksele tekstury
		};
	} //namespace displayable
}//namespace rendering
#endif //H_DISPLAYABLE_SCI
