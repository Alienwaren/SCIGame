/*
 ________________________________________
| CDisplayable.cpp - mplementacja klasy. |
| SCI - August 2012.                     |
|________________________________________|

*/

#include "CDisplayable.h"
#include "../Animations/CAnimation.h"
#include "../Animations/CAnimationManager.h"
#include "../Animations/CAnimationState.h"
#include "../../ResourceManager/CResourceManager.h"
#include "../../ResourceManager/CTexture.h"
#include <SFML/Graphics.hpp>

namespace rendering
{
	namespace displayable
	{
		//Konstruktor domy�lny
		CDisplayable::CDisplayable()
		:
			IDrawable(),			//konstruktor klasy bazowej
			m_sprite				(),
			m_animation_state		(NULL),
			m_visible				(true),
			m_can_draw				(true),
			m_animation_name		(""),
			m_smooth				(false)
		{
			//tworzymy obiekt klasy CSprite
			m_sprite = new CSprite();
		}

		//Konstruktor kopiuj�cy
		CDisplayable::CDisplayable(const CDisplayable& CDisplayableCopy)
		:
			IDrawable				(CDisplayableCopy),//konstruktor kopiuj�cy klasy bazowej
			//m_sprite				//tego nie kopiujemy...
			m_animation_state		(CDisplayableCopy.m_animation_state),
			m_visible				(CDisplayableCopy.m_visible),
			m_can_draw				(CDisplayableCopy.m_can_draw),
			m_animation_name		(CDisplayableCopy.m_animation_name),
			m_smooth				(CDisplayableCopy.m_smooth)
		{
			//tworzymy obiekt klasy CSprite, aby konstruktor kopiuj�cy pracowa� na nowym obiekcie
			//bo w czasie kopiowanie skopiowa�by wska�nik, czyli orygina� i kopia (nowy obiekt)
			//wskazywa�aby na ten sam obiekt, co jest niepo��danie
			m_sprite = new CSprite();
		}

		//Destruktor wirtualny
		CDisplayable::~CDisplayable() 
		{
			delete m_sprite;//usuwamy obiekt (mamy pewno��, �e istnieje, bo konstruktor go stworzy�)
			m_sprite				= NULL;
			m_animation_state		= NULL;
			m_visible				= false;
			m_can_draw				= false;
			m_animation_name		= "";
			m_smooth				= false;
		}

		//Metoda zwraca wska�nik na obiekt sf::Sprite
		CSprite* CDisplayable::GetSprite()
		{
			return m_sprite;
		}

		//Metoda zwraca flag�, czy obiekt mo�na rysowa�
		const bool CDisplayable::getCanDraw() const
		{
			return m_can_draw;
		}

		//Metoda ustawia flag�, czy obiekt mo�na rysowa�
		const void CDisplayable::setCanDraw(bool can_draw)
		{
			m_can_draw = can_draw;
		}

		//Metoda zwraca flag�, czy obiekt jest widoczny
		const bool CDisplayable::getVisible() const
		{
			return m_visible;
		}

		//Metoda ustawia flag�, czy obiekt jest widoczny
		const void CDisplayable::setVisible(bool visible)
		{
			m_visible = visible;
		}

		//Metoda zwraca pozycj� obiektu
		const sf::Vector2f& CDisplayable::getPosition() const
		{
			return m_sprite->getPosition();
		}

		//Metoda ustawia pozycj� obiektu
		void CDisplayable::setPosition(float x, float y)
		{
			m_sprite->setPosition(x, y);
		}

		//Metoda ustawia pozycj� obiektu
		void CDisplayable::setPosition(const sf::Vector2f& vector)
		{
			setPosition(vector.x, vector.y);
		}

		//Metoda zwraca warto�� obrotu
		float CDisplayable::getRotation() const
		{ 
			return m_sprite->getRotation();
		}

		//Metoda ustawia warto�� obrotu
		void CDisplayable::setRotation(float rotation_value)
		{
			m_sprite->setRotation(rotation_value);
		}

		//Metoda obraca warto�� obrotu
		void CDisplayable::rotate(float angle)
		{
			m_sprite->rotate(angle);
		}

		//Metoda zwraca skal�
		const sf::Vector2f& CDisplayable::getScale() const
		{
			return m_sprite->getScale();
		}

		//Metoda ustawia skal�
		void CDisplayable::setScale(float x, float y)
		{
			m_sprite->setScale(x, y);
		}

		//Metoda ustawia skal�
		void CDisplayable::setScale(const sf::Vector2f& new_scale_value)
		{
			m_sprite->setScale(new_scale_value);
		}

		//Metoda ustawia skal�
		void CDisplayable::setScale(float factors)
		{
			setScale(factors, factors);
		}

		//Metoda ustawia skal� w stosunku do obecnej skali
		void CDisplayable::scale(float factorX, float factorY)
		{
			m_sprite->scale(factorX, factorY);
		}

		//Metoda ustawia skal� w stosunku do obecnej skali
		void CDisplayable::scale(const sf::Vector2f& factor)
		{
			m_sprite->scale(factor);
		}

		//Metoda zwraca wsp�rz�dne punktu uchwytu obiektu
		const sf::Vector2f& CDisplayable::getOrigin() const
		{
			return m_sprite->getOrigin();
		}

		//Metoda ustawia wsp�rz�dne punktu uchwytu obiektu
		void CDisplayable::setOrigin(float x, float y)
		{
			m_sprite->setOrigin(x, y);
		}

		//Metoda ustawia wsp�rz�dne punktu uchwytu obiektu
		void CDisplayable::setOrigin(const sf::Vector2f& origin)
		{
			m_sprite->setOrigin(origin);
		}

		//Metoda zwraca obszar prostok�tny zajmowany przez tekstur�
		const sf::IntRect& CDisplayable::getTextureRect() const
		{
			return m_sprite->getTextureRect();
		}

		//Metoda ustawia obszar prostok�tny zajmowany przez tekstur�
		void CDisplayable::setTextureRect(int rectLeft, int rectTop, int rectWidth, int rectHeight)
		{
			setTextureRect(sf::IntRect(rectLeft, rectTop, rectWidth, rectHeight));
		}

		//Metoda ustawia obszar prostok�tny zajmowany przez tekstur�
		void CDisplayable::setTextureRect (const sf::IntRect& rectangle)
		{
			m_sprite->setTextureRect(rectangle);
		}

		//Metoda zwraca granice obiektu w lokalnym w uk�adzie wsp�rz�dnych
		sf::FloatRect CDisplayable::getLocalBounds() const
		{
			return m_sprite->getLocalBounds();
		}

		//Metoda zwraca granice obiektu w globalnym w uk�adzie wsp�rz�dnych
		sf::FloatRect CDisplayable::getGlobalBounds() const
		{
			return m_sprite->getGlobalBounds();
		}

		//Metoda przemieszcza obiekt o warto�� podan� w parametrach wzgl�dem aktualnej pozycji
		void CDisplayable::move(float offsetX, float offsetY)
		{
			m_sprite->move(offsetX, offsetY);
		}

		//Metoda przemieszcza obiekt o warto�� wektora przesuni�cia
		void CDisplayable::move(const sf::Vector2f& offset)
		{
			m_sprite->move(offset);
		}

		//Metoda zwraca kolor obiektu
		const sf::Color& CDisplayable::getColor() const
		{
			return m_sprite->getColor();
		}

		//Metoda ustawia kolor obiektu
		void CDisplayable::setColor(const sf::Color& color)
		{
			m_sprite->setColor(color);
		}

		//Metoda ustawia tekstur� obiektu
		void CDisplayable::setTexture(const std::string& texture_name)
		{
			CTexture* p_texture = gResourceManager.GetTexture(texture_name);
			if (!p_texture)
			{
				fprintf(stderr, "warning: CDisplayable::SetStaticImage: unable to obtain image `%s'\n", texture_name.c_str());
				setTexture(NULL);
				return;
			}
			setTexture(p_texture);
		}

		//Metoda ustawia tekstur� obiektu
		void CDisplayable::setTexture(CTexture *p_texture)
		{
			if (m_animation_state)					//je�li wska�nik na CAnimationState jest zainicjowany - usuwamy animacj�
			{
				gAnimationManager.DestroyAnimationState(m_animation_state);
				m_animation_state = NULL;			//ustawiamy wska�nik na NULL
			}

			if (p_texture != NULL)					//je�li mamy wska�nik poprawnie wskazuj�cy na tekstur�
			{
				m_sprite->setTexture(*p_texture);	//ustawiamy tesktur�
				//po za�adowaniu tekstury wyznaczamy punkt uchwytu sprite'a na jego �rodek geometryczny
				m_sprite->setOrigin(m_sprite->getLocalBounds().width * 0.5f, m_sprite->getLocalBounds().height * 0.5f);
			}
		}

		//Metoda ustawia animacj�
		void CDisplayable::SetAnimation(const std::string& animation_name)
		{
			//warunki, gdy zamiana animacji si� nie powiedzie:
			//nie jest �adowana animacja, je�li pr�bujemy
			//zamieni� j� na tak� sam� (istniej�c� pod tak� sam� nazw�)
			if (m_animation_name == animation_name) return;

			m_animation_name = animation_name;

			//usuwamy animacj�, je�li wcze�niej jaka� by�a
			if (m_animation_state)
				gAnimationManager.DestroyAnimationState(m_animation_state);

			//tworzymy now� animacj�
			m_animation_state = gAnimationManager.CreateAnimationState(animation_name);

			if (!m_animation_state)
			{
				fprintf(stderr, "warning: CDisplayable::SetAnimation: unable to obtain animation `%s'\n", animation_name.c_str());
			} 
		}

		//Metoda ustawia animacj�
		void CDisplayable::SetAnimation(CAnimation *p_animation)
		{
			//warunki, gdy zamiana animacji si� nie powiedzie:
			//je�li wska�nik jest NULL - return
			//je�li wska�nik jest zainicjowany, a pr�bujemy go zainicjowa� takim samym wska�nikiem - return

			if (p_animation == NULL)
				return;
			if ((m_animation_state != NULL) && (m_animation_state->GetAnimation() == p_animation))
				return;

			m_animation_name = p_animation->GetAnimationName();

			if (m_animation_state)
				gAnimationManager.DestroyAnimationState(m_animation_state);
			m_animation_state = gAnimationManager.CreateAnimationState(p_animation);

			if (!m_animation_state)
			{
				fprintf(stderr, "warning: CDrawable::SetAnimation: unable to obtain animation '%s'\n", m_animation_name.c_str());
			} 
		}

		//Metoda zwraca wska�nik na obiekt klasy CAnimationState
		CAnimationState* CDisplayable::GetAnimationState()
		{
			return m_animation_state;
		}
		
		///Metoda zwraca tryb wyg�adzania tekstury
		const bool CDisplayable::getSmoothing() const
		{
			return m_smooth;
		}

		//Metoda ustawia tryb wyg�adzania tekstury
		void CDisplayable::setSmoothing(bool smooth)
		{
			m_smooth = smooth;
		}

		//Wirtualna metoda renderuj�ca obiekt
		void CDisplayable::Draw(sf::RenderWindow* render)
		{
			//je�li flaga nie pozwala - nie rysujemy obiektu - return
			if(m_can_draw == false)	return;

			//je�li wska�nik na obiekt CAnimationState pokazuje na animacj�
			if (m_animation_state)
			{
				//tworzymy klatk� animacji i pobieramy bie��c� klatk� z CAnimationState
				CAnimationFrame frame = m_animation_state->GetCurrentFrame();

				//tworzymy wska�nik na obiekt klasy CTexture (tekstura)
				//inicjujemy ten wska�nik obrazem pobranym na podstawie nazwy
				//tekstury, na kt�rej znajduje sie klatka animacji.
				//CResourceManager zwraca na podstawie tej nazwy wska�nik na tekstur�.
				CTexture* p_texture = gResourceManager.GetTexture(frame.GetTextureName());
				//ustawiamy flag� wyg�adzania tekstury
				p_texture->setSmooth(m_smooth);

				
				//je�li wska�nik nie jest zainicjowany - komunikat o b��dzie
				if (!p_texture)
				{
					fprintf(stderr, "warning: CDisplayable::Draw: animation: unable to obtain image `%s'\n", frame.GetTextureName().c_str());
				}
				else
				{
					//w przeciwnym wypadku pobieramy obszar klatki animacji
					sf::IntRect rect = frame.GetImageRectangle();

					//sprawdzamy, wielko�� tekstury (czy ten kod jest potrzebny?)
					//niech na razie sobie tutaj pole�y, najwy�ej mo�na to zakomentowa�...
					//if (rect.left == 0 && rect.top == 0 && rect.width == 0 && rect.height == 0)
					//{
					//	rect.width = p_texture->getSize().x;	//wyznaczamy szeroko��
					//	rect.height = p_texture->getSize().y;	//wyznaczamy wysoko��
					//}
			
					m_sprite->setTexture(*p_texture);			//pod��czamy wska�nik na tekstur� pod sprite'a
					m_sprite->setTextureRect(rect);				//pod��czamy wyliczony obszar tekstury pod sprite'a

					//wyznaczamy punkt uchwytu sprite'a na jego �rodek geometryczny
					m_sprite->setOrigin(m_sprite->getLocalBounds().width * 0.5f, m_sprite->getLocalBounds().height * 0.5f);
				}
			}
			
			if(m_can_draw == false) return;	//na wszelki wypadek, gdyby w ramce czasu flaga ustawi�a si� na false
			if (m_sprite)					//na wszelki wypadek, gdyby wska�nik straci� adres...
				render->draw(*m_sprite);	//rysujemy obiekt
		}
	}//namespace displayable
}//namespace rendering
