/*
 ______________________________________
| CPhysical.h - definicja klasy        |
| SCI - August 2012.                   |
|______________________________________|

 */

#ifndef H_PHYSICAL_SCI
#define H_PHYSICAL_SCI

#include <SFML/System/Vector2.hpp>
#include <string>
#include "ECollisionShape.h"
#include "EPhysicalPart.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>

///
///Forward declaration
///
namespace rendering
{
	namespace displayable
	{
		class CDisplayable;
	}
}

///
///Forward declaration
///
namespace rendering
{
	namespace animation
	{
		class CAnimation;
		class CAnimationState;
	}
}

///
///Forward declaration
///
namespace factory
{
	class CPhysicalTemplate;
}

using namespace rendering::displayable;
using namespace rendering::animation;
using namespace factory;

namespace logic
{
	///
	///Klasa reprezentuje behawioralne cechy fizyczne i logiczne
	///
	class CPhysical
	{

		///
		///Deklaracja przyja�ni
		///
		friend class CPhysicalManager;

		//Aby uzyska� obiekt CPhysical, nale�y wywo�a� CPhysicalManager::CreatePhysical();

	protected:

		///
		///Chroniony konstruktor domy�lny - u�ywany wy��cznie przez CPhysicalManager
		///
		CPhysical(const std::wstring& uniqueId);

		///
		///Chroniony konstruktor kopiuj�cy
		///
		///@param CPhysicalCopy - parametr - obiekt klasy CPhysical
		///
		CPhysical(const CPhysical &CPhysicalCopy);

		///
		///Chroniony destruktor wirtualny - u�ywany wy��cznie przez CPhysicalManager
		///
		virtual ~CPhysical();

	public:

		///
		///Metoda zwraca unikaln� nazw� obiektu klasy CPhysical
		///
		const std::wstring& GetUniqueId() const;

		///
		///Metoda zwraca nazw� gatunku
		///
		const std::wstring& GetGenre();

		///
		///Metoda ustawia nazw� gatunku
		///
		///@param &genre - sta�a referencja na obiekt klasy std::wstring
		///
		void SetGenre(const std::wstring& genre);

		///
		///Metoda zwraca pozycj� obiektu
		///
		const sf::Vector2f& GetPosition() const;

		///
		///Metoda ustawia pozycj� obiektu
		///
		///@param x - wsp�rz�dna x obiektu
		///
		///@param y - wsp�rz�dna y obiektu
		///
		///@param change_old_position - flaga, czy aktualizowa� m_old_position
		///
		void SetPosition(float x, float y, bool change_old_position = false);

		///
		///Metoda ustawia pozycj� obiektu
		///
		///@param &vector - sta�a referenacja na obiekt klasy sf::Vector2f
		///
		///@param change_old_position - flaga, czy aktualizowa� m_old_position
		///
		void SetPosition(const sf::Vector2f& new_value, bool change_old_position = false);

		///
		///Metoda zwraca pozycj� przed aktualizacj� logiki m_old_position
		///
		const sf::Vector2f& GetOldPosition() const;

		///
		///Metoda zwraca skal� (body)
		///
		const sf::Vector2f& GetScaleBody() const;
		
		///
		///Metoda ustawia skal� (body)
		///
		///@param scale_X - warto�� X
		///
		///@param scale_Y - warto�� Y
		///
		void SetScaleBody(float scale_X, float scale_Y);
		
		///
		///Metoda ustawia skal� (body)
		///
		///@param &scale_vector - wektor skali - sta�a referencja na obiekt klasy sf::Vector2f
		///
		void SetScaleBody(const sf::Vector2f& scale_vector);

		///
		///Metoda zwraca skal� (head)
		///
		const sf::Vector2f& GetScaleHead() const;

		///
		///Metoda ustawia skal� (head)
		///
		///@param scale_X - warto�� X
		///
		///@param scale_Y - warto�� Y
		///
		void SetScaleHead(float scale_X, float scale_Y);

		///
		///Metoda ustawia skal� (head)
		///
		///@param &scale_vector - wektor skali - sta�a referencja na obiekt klasy sf::Vector2f
		///
		void SetScaleHead(const sf::Vector2f& scale_vector);

		///
		///Metoda ustawia skal� (body and head)
		///
		///@param scale_X - warto�� X
		///
		///@param scale_Y - warto�� Y
		///
		void SetScale(float scale_X, float scale_Y);

		///
		///Metoda ustawia skal� (body and head)
		///
		///@param &scale - wektor skali - sta�a referencja na obiekt klasy sf::Vector2f
		///
		void SetScale(const sf::Vector2f& scale);

		///
		///Metoda ustawia skal�
		///
		///@param uniform - jednolita warto�� skaluj�ca w osi x i y
		///
		void SetScale(float uniform);

		///
		///Metoda zwraca warto�� obrotu obiektu w stopniach (body and head)
		///
		float GetRotation();

		///
		///Metoda ustawia warto�� obrotu obiektu w stopniach (body and head)
		///
		///@param rotation_uniform - warto�� obrotu obiektu (body and head)
		///
		void SetRotation(float rotation_uniform);

		///
		///Metoda zwraca warto�� obrotu obiektu w stopniach (body)
		///
		float GetRotationBody();

		///
		///Metoda ustawia warto�� obrotu obiektu w stopniach (body)
		///
		///@param rotation_body - warto�� obrotu obiektu (body)
		///
		void SetRotationBody(float rotation_body);

		///
		///Metoda zwraca warto�� obrotu obiektu w stopniach (head)
		///
		float GetRotationHead();

		///
		///Metoda ustawia warto�� obrotu obiektu w stopniach (head)
		///
		///@param rotation_head - warto�� obrotu obiektu (head)
		///
		void SetRotationHead(float rotation_head);

		///
		///Metoda obraca obiekt o zadany k�t (body)
		///
		///@param angle - warto�� obrotu
		///
		void RotateBody(float angle);

		///
		///Metoda obraca obiekt o zadany k�t (head)
		///
		///@param angle - warto�� obrotu
		///
		void RotateHead(float angle);

		///
		///Metoda obraca obiekt o zadany k�t (body and head)
		///
		///@param angle - warto�� obrotu
		///
		void Rotate(float angle);

		///
		///Metoda zwraca pr�dko�� obiektu
		///
		const sf::Vector2f& GetVelocity() const;

		///
		///Metoda ustawia pr�dko�� obiektu
		///
		///@param velocity - sta�a referencja na obiekt klasy sf::Vector2f
		///
		void SetVelocity(const sf::Vector2f& velocity);

		///
		///Metoda zwraca promie� detekcji wykorzystywany przy liczeniu kolizji
		///
		float GetCircleRadius();

		///
		///Metoda zwraca wyliczenie - typ liczenia kolizji
		///
		ECollisionShape GetCollisionShape();

		///
		///Wirtualna metoda ustawiaj�ca warto�� promienia detekcji wykorzystywan� przy liczeniu kolizji
		///
		///@param radius - promie� detekcji
		///
		virtual void SetBoundingCircle(float radius);

		///
		///Metoda ustawia warto�� obszaru prostok�tnego detekcji wykorzystywany przy liczeniu kolizji
		///
		///@param &rect_size - sta�a referencja wektor dla obszaru prostok�tnego detekcji wykorzystywany przy liczeniu kolizji
		///
		void SetBoundingRect(const sf::Vector2f& rect_size);

		///
		///Metoda zwraca wektor dla obszaru prostok�tnego detekcji wykorzystywany przy liczeniu kolizji
		///
		const sf::Vector2f& GetRectSize() const ;

		///
		///Metoda zwraca warto�� pu�apu obiektu
		///
		const float GetAltitude() const;

		///
		///Metoda ustawia warto�� pu�apu obiektu
		///
		///@param altitude - warto�� pu�apu obiektu
		///
		void SetAltitude(float altitude);

		///
		///Metoda zwraca kolor obiektu - body
		///
		const sf::Color& GetColor() const;

		///
		///Metoda ustawia kolor obiektu - (body and head)
		///
		///@param color - kolor
		///
		void SetColor(const sf::Color& color);

		///
		///Metoda zwraca kolor obiektu - body
		///
		const sf::Color& GetColorBody() const;

		///
		///Metoda ustawia kolor obiektu - body
		///
		///@param color_body - kolor obiektu
		///
		void SetColorBody(const sf::Color& color_body);

		///
		///Metoda zwraca kolor obiektu - head
		///
		const sf::Color& GetColorHead() const;

		///
		///Metoda ustawia kolor obiektu - head
		///
		///@param color_head - kolor
		///
		void SetColorHead(const sf::Color& color_head);

		///
		///Metoda ustawia oryginalny kolor obiektu za�adowany z tekstury - body and head
		///
		void RestoreColor();

		///
		///Metoda ustawia oryginalny kolor obiektu za�adowany z tekstury - body
		///
		void RestoreColorBody();

		///
		///Metoda ustawia oryginalny kolor obiektu za�adowany z tekstury - head
		///
		void RestoreColorHead();

		///
		///Metoda zwraca kolor cienia obiektu
		///
		const sf::Color& GetColorShadow() const;

		///
		///Metoda ustawia kolor cienia obiektu
		///
		///@param color_shadow - kolor cienia obiektu
		///
		void SetColorShadow(const sf::Color& color_shadow);

		///
		///Metoda zwraca wektor przesuni�cia cienia wzgl�dem obiektu - body
		///
		sf::Vector2f GetShadowOffsetBody() const;

		///
		///Metoda ustawia wektor przesuni�cia cienia wzgl�dem obiektu - body
		///
		///@param &shadow_offset_body - sta�a referencja na wektor przesuni�cia cienia wzgl�dem obiektu
		///
		void SetShadowOffsetBody(sf::Vector2f& shadow_offset_body);

		///
		///Metoda zwraca wektor przesuni�cia cienia wzgl�dem obiektu - head
		///
		sf::Vector2f GetShadowOffsetHead() const;

		///
		///Metoda ustawia wektor przesuni�cia cienia wzgl�dem obiektu - head
		///
		///@param &shadow_offset_head - sta�a referencja na wektor przesuni�cia cienia wzgl�dem obiektu
		///
		void SetShadowOffsetHead(sf::Vector2f& shadow_offset_head);

		///
		///Metoda ustawia flag�, czy CPhysical ma reprezentacj� graficz� (body and head)
		///
		inline void SetUseDisplayable(bool b) { m_use_displayable_body = m_use_displayable_head = b; }

		///
		///Metoda ustawia flag�, czy CPhysical ma reprezentacj� graficz� (body)
		///
		inline void SetUseDisplayableBody(bool b) { m_use_displayable_body = b; }

		///
		///Metoda ustawia flag�, czy CPhysical ma reprezentacj� graficz� (head)
		///
		inline void SetUseDisplayableHead(bool b) { m_use_displayable_head = b; }

		///
		///Metoda zwraca flag�, czy CPhysical ma reprezentacj� graficz� (body)
		///
		inline const bool GetUseDisplayableBody() const { return m_use_displayable_body; }

		///
		///Metoda zwraca flag�, czy CPhysical ma reprezentacj� graficz� (head)
		///
		inline const bool GetUseDisplayableHead() const { return m_use_displayable_head; }

		///
		///Metoda zwraca wska�nik na animacj�
		///
		///@param physical_part - wyliczenie EPhysicalPart - cz�� physical (default BODY)
		///
		CAnimation *GetAnimation(EPhysicalPart physical_part = BODY);

		///
		///Metoda ustawia ustawia wska�nik na animacj�
		///
		///@param *p_anim - wska�nik na animacj� - obiekt klasy CAnimation
		///
		///@param physical_part - wyliczenie EPhysicalPart - cz�� physical (default BODY)
		///
		void SetAnimation(CAnimation* p_anim, EPhysicalPart physical_part = BODY);

		///
		///Metoda ustawia nazw� animacji (only body) /zgodno�� interfejsu/
		///
		///@param &anim_name - nazwa animacji (only body) /zgodno�� interfejsu/
		///
		///@param physical_part - wyliczenie EPhysicalPart - cz�� physical (default BODY)
		///
		void SetAnimation(const std::string& anim_name, EPhysicalPart physical_part = BODY);

		///
		///Metoda zwraca nazw� animacji
		///
		/////@param physical_part - wyliczenie EPhysicalPart - cz�� physical (default BODY)
		///
		const std::string& GetAnimationName(EPhysicalPart physical_part = BODY) const;

		///
		///Metoda zwraca wska�nik na animacj� (body) /zgodno�� interfejsu/
		///
		CAnimation *GetAnimation();

		///
		///Metoda ustawia ustawia wska�nik na animacj� (body) /zgodno�� interfejsu/
		///
		///@param *p_anim - wska�nik na animacj� - obiekt klasy CAnimation /zgodno�� interfejsu/
		///
		void SetAnimation(CAnimation* p_anim);

		///
		///Metoda zwraca nazw� animacji (only body) /zgodno�� interfejsu/
		///
		const std::string& GetAnimationName() const;

		///
		///Metoda ustawia nazw� animacji (only body) /zgodno�� interfejsu/
		///
		///@param &anim_name - nazwa animacji (only body) /zgodno�� interfejsu/
		///
		void SetAnimation(const std::string& anim_name);

		///
		///Metoda zwraca wska�nik na animacj� (body)
		///
		CAnimation *GetAnimationBody();

		///
		///Metoda ustawia ustawia wska�nik na animacj� (body)
		///
		///@param *p_anim_body - wska�nik na animacj� - obiekt klasy CAnimation (body)
		///
		void SetAnimationBody(CAnimation* p_anim_body);

		///
		///Metoda zwraca nazw� animacji (body)
		///
		const std::string& GetAnimationBodyName() const;

		///
		///Metoda ustawia nazw� animacji (body)
		///
		///@param &anim_body_name - nazwa animacji (body)
		///
		void SetAnimationBody(const std::string& anim_body_name);

		///
		///Metoda zwraca wska�nik na animacj� (head)
		///
		CAnimation *GetAnimationHead();

		///
		///Metoda ustawia ustawia wska�nik na animacj� (head)
		///
		///@param *p_anim_head - wska�nik na animacj� - obiekt klasy CAnimation (head)
		///
		void SetAnimationHead(CAnimation* p_anim_head);

		///
		///Metoda zwraca nazw� animacji (head)
		///
		const std::string& GetAnimationHeadName() const;

		///
		///Metoda ustawia nazw� animacji (head)
		///
		///@param &anim_head_name - nazwa animacji (head)
		///
		void SetAnimationHead(const std::string& anim_head_name);

		///
		///Metoda ustawia komplet animacji
		///
		///@param *p_anim_body - wska�nik na obiekt klasy CAnimation (body)
		///
		///@param *p_anim_head - wska�nik na obiekt klasy CAnimation (head)
		///
		void SetAnimation(CAnimation *p_anim_body, CAnimation *p_anim_head);

		///
		///Metoda ustawia komplet animacji
		///
		///@param &anim_name_body - sta�a referencja na obiekt klasy std::string - nazwa animacji (body)
		///
		///@param &anim_name_head - sta�a referencja na obiekt klasy std::string - nazwa animacji (head)
		///
		void SetAnimation(const std::string& anim_name_body, const std::string& anim_name_head);
	    
		///
		///Metoda zwraca wska�nik na obiekt klasy CDisplayable (body) /zgodno�� interfejsu/
		///
		CDisplayable* GetDisplayable();
	    
		///
		///Metoda zwraca wska�nik na obiekt klasy CDisplayable (shadow) /zgodno�� interfejsu/
		///
		CDisplayable* GetShadow();

		///
		///Metoda zwraca wska�nik na obiekt klasy CDisplayable (body)
		///
		///@param physical_part - wyliczenie EPhysicalPart - cz�� physical
		///
		CDisplayable* GetDisplayable(EPhysicalPart physical_part);
	    
		///
		///Metoda zwraca wska�nik na obiekt klasy CDisplayable (shadow)
		///
		///@param physical_part - wyliczenie EPhysicalPart - cz�� physical
		///
		CDisplayable* GetShadow(EPhysicalPart physical_part);

		///
		///Metoda zwraca wska�nik na obiekt klasy CDisplayable (body)
		///
		CDisplayable* GetDisplayableBody();
	    
		///
		///Metoda zwraca wska�nik na obiekt klasy CDisplayable (body shadow)
		///
		CDisplayable* GetDisplayableBodyShadow();

		///
		///Metoda zwraca wska�nik na obiekt klasy CDisplayable (head)
		///
		CDisplayable* GetDisplayableHead();

		///
		///Metoda zwraca wska�nik na obiekt klasy CDisplayable (head shadow)
		///
		CDisplayable* GetDisplayableHeadShadow();

		///
		///Metoda zwraca flag�, czy obiekt generuje cie� (body)
		///
		bool GetUseShadowBody();

		///
		///Metoda ustawia flag�, czy obiekt ma generowa� cie� (body)
		///
		///@param use_shadow_body - flaga, czy obiekt ma generowa� cie� (body)
		///
		void SetUseShadowBody(bool use_shadow_body);

		///
		///Metoda zwraca flag�, czy obiekt generuje cie� (head)
		///
		bool GetUseShadowHead();

		///
		///Metoda ustawia flag�, czy obiekt ma generowa� cie� (head)
		///
		///@param use_shadow_head - flaga, czy obiekt ma generowa� cie� (head)
		///
		void SetUseShadowHead(bool use_shadow_head);

		///
		///Metoda zwraca flag�, czy obiekt generuje cie� (body and head) /zgodno�� interfejsu/
		///
		bool GetUseShadow();

		///
		///Metoda ustawia flag�, czy obiekt ma generowa� cie� (body and head) /zgodno�� interfejsu/
		///
		///@param use_shadow - flaga, czy obiekt ma generowa� cie� (body and head) /zgodno�� interfejsu/
		///
		void SetUseShadow(bool use_shadow);

		///
		///Metoda ustawia flag� dla obiekt�w gotowych do destrukcji
		///
		void MarkForDelete();
	    
		///
		///Wirtualna metoda zaznacza obiekty do destrukcji
		///
		virtual void Kill();

		///
		///Metoda zwraca flag�, czy obiekt jest gotowy do usuniecia
		///
		virtual bool IsDead();

		///
		///Metoda zwraca nazw� tekstury (body)
		///
		const std::string& GetTextureBody() const;
		
		///
		///Metoda ustatawia nazw� tekstury (body)
		///
		///@param texture_body - nazwa tekstury (body)
		///
		void SetTextureBody(const std::string& texture_body);

		///
		///Metoda zwraca nazw� tekstury (head)
		///
		const std::string& GetTextureHead() const;
		
		///
		///Metoda ustatwia nazw� tekstury (head)
		///
		///@param texture_head - nazwa tekstury (head)
		///
		void SetTextureHead(const std::string& texture_head);

		///
		////Metoda zwraca tryb wyg�adzania tekstury
		///
		const bool getSmoothing() const;

		///
		///Metoda ustawia tryb wyg�adzania tekstury
		///
		///@param smooth - flaga wyg�adzania tekstury
		///
		void setSmoothing(bool smooth);

		///
		///Metoda zwraca statyczny wsp�czynnik wirtualnej wysoko�ci obiektu
		///
		const float GetIncrease() const;

		///
		///Metoda ustawia statyczny wsp�czynnik wirtualnej wysoko�ci obiektu
		///
		///@param increase - wirtualna wysoko�� obiektu
		///
		const void SetIncrease(float increase) const;

		///
		///Metoda zwraca wska�nik na obiekt klasy CPhysicalTemplate
		///
		inline CPhysicalTemplate *GetTemplate() const { return p_template; }

		///
		///Metoda ustawia wska�nik na obiekt klasy CPhysicalTemplate
		///
		///@param *p_template - wska�nik na obiekt klasy CPhysicalTemplate
		///
		inline void SetTemplate(CPhysicalTemplate* p_template) { p_template = p_template; }

		///
		///Wirtualna metoda aktualizuj�ca obiekt
		///
		///@param dt - czas
		///
		virtual void Update(float dt);

	protected:
	    
		std::wstring		m_unique_id;				//unikalny identyfikator (nadawany w CPhysicalManager)
		std::wstring		m_genre;					//nazwa "gatunku" obiektu (np. robot, human, gun, etc.)
		sf::Vector2f		m_position;					//wektor pozycji
		sf::Vector2f		m_old_position;				//wektor pozycji (przed aktualizacj�)
		float				m_rotation_uniform;			//warto�� obrotu (body and head)
		float				m_rotation_body;			//warto�� obrotu (body)
		float				m_rotation_head;			//warto�� obrotu (head)
		sf::Vector2f		m_velocity;					//wektor pr�dko�ci obiektu
		float				m_circle_radius;			//promie� detekcji kolizji
		std::string			m_texture_body;				//nazwa tekstury reprezentacji graficznej obiektu - body
		std::string			m_texture_head;				//nazwa tekstury reprezentacji graficznej obiektu - head
		CAnimation*			p_animation_body;			//wska�nik na animacj� - body (cienie - taka sama animacja)
		CAnimation*			p_animation_head;			//wska�nik na animacj� - head (cienie - taka sama animacja)
		ECollisionShape		m_collision_shape;			//wyliczenie - typ detekcji kolizji
		sf::Vector2f		m_rect_size;				//wektor przechowuj�cy rozmiar obszaru prostok�tnego
		float				m_altitude;					//warto�� pu�apu obiektu wzgl�dem pod�o�a
		sf::Color			m_color_body;				//kolor obiektu - body
		sf::Color			m_color_head;				//kolor obiektu - head
		sf::Color			m_color_stored_body;		//zapami�tany kolor obiektu
		sf::Color			m_color_stored_head;		//zapami�tany kolor obiektu
		sf::Color			m_color_shadow;				//kolor cienia
		sf::Vector2f		m_shadow_offset_body;		//wektor przesuni�cia cienia - body
		sf::Vector2f		m_shadow_offset_head;		//wektor przesuni�cia cienia - head
		bool				m_ready_for_destruction;	//flaga ustawia obiekty gotowe do destrukcji
		bool				m_use_displayable_body;		//flaga okre�la, czy CPhysical posiada reprezentacj� graficzn� - body
		bool				m_use_shadow_body;			//flaga okre�la, czy CPhysical posiada reprezentacj� graficzn� - body - cie�
		bool				m_use_displayable_head;		//flaga okre�la, czy CPhysical posiada reprezentacj� graficzn� - head
		bool				m_use_shadow_head;			//flaga okre�la, czy CPhysical posiada reprezentacj� graficzn� - head - cie�
		CPhysicalTemplate*	p_template;					//wska�nik na obiekt klasy CPhysicalTemplate
		static float		m_shadow_init;				//wsp�czynnik przesuni�cia cienia w zale�no�ci od wielko�ci obiektu

	private:

		int					m_z_index;					//indeks warstwy rysowania
		int					m_physical_manager_index;	//wyliczony indeks w CPhysicalManager
		CDisplayable*		p_displayable_body;			//wska�nik na obiekt CDisplayable - body (cz�� zasadnicza)
		CDisplayable*		p_displayable_body_shadow;	//wska�nik na obiekt CDisplayable - body shadow	(cie� cz�ci zasadniczej)
		CDisplayable*		p_displayable_head;			//wska�nik na obiekt CDisplayable - head (cz�� dodatkowa)
		CDisplayable*		p_displayable_head_shadow;	//wska�nik na obiekt CDisplayable - head shadow (cie� cz�ci dodatkowej)
		float				m_init_height;				//wyliczona wirtualna wysoko�� obiektu
		sf::Vector2f		m_stored_scale_body;		//zapami�tana skala - pole pomocniczne - body
		sf::Vector2f		m_stored_scale_head;		//zapami�tana skala - pole pomocniczne - head
		bool				m_smooth;					//flaga, czy obiekt wyg�adza piksele tekstury	
		static float		m_increase;					//wsp�czynnik wirtualnej wysoko�ci obiektu

	protected:

		///
		///Metoda ustawia indeks warstwy renderingu obiektu
		///
		///@param layer_index - indeks warstwy renderingu obiektu
		///
		void SetZIndex(int layer_index);

		///
		///Metoda zwraca indeks warstwy renderingu obiektu
		///
		inline int GetZIndex() { return m_z_index; }

	private:

		void CheckDisplayableBody();		//prywatna metoda sprawdza, czy trzeba utworzy�
											//obiekt klasy CDisplayable (body), np. gdy chcemy
											//doda� obrazek, animacj�, etc...

		void CheckDisplayableHead();		//prywatna metoda sprawdza, czy trzeba utworzy�
											//obiekt klasy CDisplayable (head), np. gdy chcemy
											//doda� obrazek, animacj�, etc...

		void UpdateShadowOffset(float dt);	//prywatna metoda dobieraj�ca przesuni�cie cienia
											//w zale�no�ci od wielko�ci obiektu - body and head

	};
}//namespace logic
#endif //H_PHYSICAL_SCI
