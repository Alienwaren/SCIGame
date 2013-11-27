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
		///Deklaracja przyjaŸni
		///
		friend class CPhysicalManager;

		//Aby uzyskaæ obiekt CPhysical, nale¿y wywo³aæ CPhysicalManager::CreatePhysical();

	protected:

		///
		///Chroniony konstruktor domyœlny - u¿ywany wy³¹cznie przez CPhysicalManager
		///
		CPhysical(const std::wstring& uniqueId);

		///
		///Chroniony konstruktor kopiuj¹cy
		///
		///@param CPhysicalCopy - parametr - obiekt klasy CPhysical
		///
		CPhysical(const CPhysical &CPhysicalCopy);

		///
		///Chroniony destruktor wirtualny - u¿ywany wy³¹cznie przez CPhysicalManager
		///
		virtual ~CPhysical();

	public:

		///
		///Metoda zwraca unikaln¹ nazwê obiektu klasy CPhysical
		///
		const std::wstring& GetUniqueId() const;

		///
		///Metoda zwraca nazwê gatunku
		///
		const std::wstring& GetGenre();

		///
		///Metoda ustawia nazwê gatunku
		///
		///@param &genre - sta³a referencja na obiekt klasy std::wstring
		///
		void SetGenre(const std::wstring& genre);

		///
		///Metoda zwraca pozycjê obiektu
		///
		const sf::Vector2f& GetPosition() const;

		///
		///Metoda ustawia pozycjê obiektu
		///
		///@param x - wspó³rzêdna x obiektu
		///
		///@param y - wspó³rzêdna y obiektu
		///
		///@param change_old_position - flaga, czy aktualizowaæ m_old_position
		///
		void SetPosition(float x, float y, bool change_old_position = false);

		///
		///Metoda ustawia pozycjê obiektu
		///
		///@param &vector - sta³a referenacja na obiekt klasy sf::Vector2f
		///
		///@param change_old_position - flaga, czy aktualizowaæ m_old_position
		///
		void SetPosition(const sf::Vector2f& new_value, bool change_old_position = false);

		///
		///Metoda zwraca pozycjê przed aktualizacj¹ logiki m_old_position
		///
		const sf::Vector2f& GetOldPosition() const;

		///
		///Metoda zwraca skalê (body)
		///
		const sf::Vector2f& GetScaleBody() const;
		
		///
		///Metoda ustawia skalê (body)
		///
		///@param scale_X - wartoœæ X
		///
		///@param scale_Y - wartoœæ Y
		///
		void SetScaleBody(float scale_X, float scale_Y);
		
		///
		///Metoda ustawia skalê (body)
		///
		///@param &scale_vector - wektor skali - sta³a referencja na obiekt klasy sf::Vector2f
		///
		void SetScaleBody(const sf::Vector2f& scale_vector);

		///
		///Metoda zwraca skalê (head)
		///
		const sf::Vector2f& GetScaleHead() const;

		///
		///Metoda ustawia skalê (head)
		///
		///@param scale_X - wartoœæ X
		///
		///@param scale_Y - wartoœæ Y
		///
		void SetScaleHead(float scale_X, float scale_Y);

		///
		///Metoda ustawia skalê (head)
		///
		///@param &scale_vector - wektor skali - sta³a referencja na obiekt klasy sf::Vector2f
		///
		void SetScaleHead(const sf::Vector2f& scale_vector);

		///
		///Metoda ustawia skalê (body and head)
		///
		///@param scale_X - wartoœæ X
		///
		///@param scale_Y - wartoœæ Y
		///
		void SetScale(float scale_X, float scale_Y);

		///
		///Metoda ustawia skalê (body and head)
		///
		///@param &scale - wektor skali - sta³a referencja na obiekt klasy sf::Vector2f
		///
		void SetScale(const sf::Vector2f& scale);

		///
		///Metoda ustawia skalê
		///
		///@param uniform - jednolita wartoœæ skaluj¹ca w osi x i y
		///
		void SetScale(float uniform);

		///
		///Metoda zwraca wartoœæ obrotu obiektu w stopniach (body and head)
		///
		float GetRotation();

		///
		///Metoda ustawia wartoœæ obrotu obiektu w stopniach (body and head)
		///
		///@param rotation_uniform - wartoœæ obrotu obiektu (body and head)
		///
		void SetRotation(float rotation_uniform);

		///
		///Metoda zwraca wartoœæ obrotu obiektu w stopniach (body)
		///
		float GetRotationBody();

		///
		///Metoda ustawia wartoœæ obrotu obiektu w stopniach (body)
		///
		///@param rotation_body - wartoœæ obrotu obiektu (body)
		///
		void SetRotationBody(float rotation_body);

		///
		///Metoda zwraca wartoœæ obrotu obiektu w stopniach (head)
		///
		float GetRotationHead();

		///
		///Metoda ustawia wartoœæ obrotu obiektu w stopniach (head)
		///
		///@param rotation_head - wartoœæ obrotu obiektu (head)
		///
		void SetRotationHead(float rotation_head);

		///
		///Metoda obraca obiekt o zadany k¹t (body)
		///
		///@param angle - wartoœæ obrotu
		///
		void RotateBody(float angle);

		///
		///Metoda obraca obiekt o zadany k¹t (head)
		///
		///@param angle - wartoœæ obrotu
		///
		void RotateHead(float angle);

		///
		///Metoda obraca obiekt o zadany k¹t (body and head)
		///
		///@param angle - wartoœæ obrotu
		///
		void Rotate(float angle);

		///
		///Metoda zwraca prêdkoœæ obiektu
		///
		const sf::Vector2f& GetVelocity() const;

		///
		///Metoda ustawia prêdkoœæ obiektu
		///
		///@param velocity - sta³a referencja na obiekt klasy sf::Vector2f
		///
		void SetVelocity(const sf::Vector2f& velocity);

		///
		///Metoda zwraca promieñ detekcji wykorzystywany przy liczeniu kolizji
		///
		float GetCircleRadius();

		///
		///Metoda zwraca wyliczenie - typ liczenia kolizji
		///
		ECollisionShape GetCollisionShape();

		///
		///Wirtualna metoda ustawiaj¹ca wartoœæ promienia detekcji wykorzystywan¹ przy liczeniu kolizji
		///
		///@param radius - promieñ detekcji
		///
		virtual void SetBoundingCircle(float radius);

		///
		///Metoda ustawia wartoœæ obszaru prostok¹tnego detekcji wykorzystywany przy liczeniu kolizji
		///
		///@param &rect_size - sta³a referencja wektor dla obszaru prostok¹tnego detekcji wykorzystywany przy liczeniu kolizji
		///
		void SetBoundingRect(const sf::Vector2f& rect_size);

		///
		///Metoda zwraca wektor dla obszaru prostok¹tnego detekcji wykorzystywany przy liczeniu kolizji
		///
		const sf::Vector2f& GetRectSize() const ;

		///
		///Metoda zwraca wartoœæ pu³apu obiektu
		///
		const float GetAltitude() const;

		///
		///Metoda ustawia wartoœæ pu³apu obiektu
		///
		///@param altitude - wartoœæ pu³apu obiektu
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
		///Metoda ustawia oryginalny kolor obiektu za³adowany z tekstury - body and head
		///
		void RestoreColor();

		///
		///Metoda ustawia oryginalny kolor obiektu za³adowany z tekstury - body
		///
		void RestoreColorBody();

		///
		///Metoda ustawia oryginalny kolor obiektu za³adowany z tekstury - head
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
		///Metoda zwraca wektor przesuniêcia cienia wzglêdem obiektu - body
		///
		sf::Vector2f GetShadowOffsetBody() const;

		///
		///Metoda ustawia wektor przesuniêcia cienia wzglêdem obiektu - body
		///
		///@param &shadow_offset_body - sta³a referencja na wektor przesuniêcia cienia wzglêdem obiektu
		///
		void SetShadowOffsetBody(sf::Vector2f& shadow_offset_body);

		///
		///Metoda zwraca wektor przesuniêcia cienia wzglêdem obiektu - head
		///
		sf::Vector2f GetShadowOffsetHead() const;

		///
		///Metoda ustawia wektor przesuniêcia cienia wzglêdem obiektu - head
		///
		///@param &shadow_offset_head - sta³a referencja na wektor przesuniêcia cienia wzglêdem obiektu
		///
		void SetShadowOffsetHead(sf::Vector2f& shadow_offset_head);

		///
		///Metoda ustawia flagê, czy CPhysical ma reprezentacjê graficz¹ (body and head)
		///
		inline void SetUseDisplayable(bool b) { m_use_displayable_body = m_use_displayable_head = b; }

		///
		///Metoda ustawia flagê, czy CPhysical ma reprezentacjê graficz¹ (body)
		///
		inline void SetUseDisplayableBody(bool b) { m_use_displayable_body = b; }

		///
		///Metoda ustawia flagê, czy CPhysical ma reprezentacjê graficz¹ (head)
		///
		inline void SetUseDisplayableHead(bool b) { m_use_displayable_head = b; }

		///
		///Metoda zwraca flagê, czy CPhysical ma reprezentacjê graficz¹ (body)
		///
		inline const bool GetUseDisplayableBody() const { return m_use_displayable_body; }

		///
		///Metoda zwraca flagê, czy CPhysical ma reprezentacjê graficz¹ (head)
		///
		inline const bool GetUseDisplayableHead() const { return m_use_displayable_head; }

		///
		///Metoda zwraca wskaŸnik na animacjê
		///
		///@param physical_part - wyliczenie EPhysicalPart - czêœæ physical (default BODY)
		///
		CAnimation *GetAnimation(EPhysicalPart physical_part = BODY);

		///
		///Metoda ustawia ustawia wskaŸnik na animacjê
		///
		///@param *p_anim - wskaŸnik na animacjê - obiekt klasy CAnimation
		///
		///@param physical_part - wyliczenie EPhysicalPart - czêœæ physical (default BODY)
		///
		void SetAnimation(CAnimation* p_anim, EPhysicalPart physical_part = BODY);

		///
		///Metoda ustawia nazwê animacji (only body) /zgodnoœæ interfejsu/
		///
		///@param &anim_name - nazwa animacji (only body) /zgodnoœæ interfejsu/
		///
		///@param physical_part - wyliczenie EPhysicalPart - czêœæ physical (default BODY)
		///
		void SetAnimation(const std::string& anim_name, EPhysicalPart physical_part = BODY);

		///
		///Metoda zwraca nazwê animacji
		///
		/////@param physical_part - wyliczenie EPhysicalPart - czêœæ physical (default BODY)
		///
		const std::string& GetAnimationName(EPhysicalPart physical_part = BODY) const;

		///
		///Metoda zwraca wskaŸnik na animacjê (body) /zgodnoœæ interfejsu/
		///
		CAnimation *GetAnimation();

		///
		///Metoda ustawia ustawia wskaŸnik na animacjê (body) /zgodnoœæ interfejsu/
		///
		///@param *p_anim - wskaŸnik na animacjê - obiekt klasy CAnimation /zgodnoœæ interfejsu/
		///
		void SetAnimation(CAnimation* p_anim);

		///
		///Metoda zwraca nazwê animacji (only body) /zgodnoœæ interfejsu/
		///
		const std::string& GetAnimationName() const;

		///
		///Metoda ustawia nazwê animacji (only body) /zgodnoœæ interfejsu/
		///
		///@param &anim_name - nazwa animacji (only body) /zgodnoœæ interfejsu/
		///
		void SetAnimation(const std::string& anim_name);

		///
		///Metoda zwraca wskaŸnik na animacjê (body)
		///
		CAnimation *GetAnimationBody();

		///
		///Metoda ustawia ustawia wskaŸnik na animacjê (body)
		///
		///@param *p_anim_body - wskaŸnik na animacjê - obiekt klasy CAnimation (body)
		///
		void SetAnimationBody(CAnimation* p_anim_body);

		///
		///Metoda zwraca nazwê animacji (body)
		///
		const std::string& GetAnimationBodyName() const;

		///
		///Metoda ustawia nazwê animacji (body)
		///
		///@param &anim_body_name - nazwa animacji (body)
		///
		void SetAnimationBody(const std::string& anim_body_name);

		///
		///Metoda zwraca wskaŸnik na animacjê (head)
		///
		CAnimation *GetAnimationHead();

		///
		///Metoda ustawia ustawia wskaŸnik na animacjê (head)
		///
		///@param *p_anim_head - wskaŸnik na animacjê - obiekt klasy CAnimation (head)
		///
		void SetAnimationHead(CAnimation* p_anim_head);

		///
		///Metoda zwraca nazwê animacji (head)
		///
		const std::string& GetAnimationHeadName() const;

		///
		///Metoda ustawia nazwê animacji (head)
		///
		///@param &anim_head_name - nazwa animacji (head)
		///
		void SetAnimationHead(const std::string& anim_head_name);

		///
		///Metoda ustawia komplet animacji
		///
		///@param *p_anim_body - wskaŸnik na obiekt klasy CAnimation (body)
		///
		///@param *p_anim_head - wskaŸnik na obiekt klasy CAnimation (head)
		///
		void SetAnimation(CAnimation *p_anim_body, CAnimation *p_anim_head);

		///
		///Metoda ustawia komplet animacji
		///
		///@param &anim_name_body - sta³a referencja na obiekt klasy std::string - nazwa animacji (body)
		///
		///@param &anim_name_head - sta³a referencja na obiekt klasy std::string - nazwa animacji (head)
		///
		void SetAnimation(const std::string& anim_name_body, const std::string& anim_name_head);
	    
		///
		///Metoda zwraca wskaŸnik na obiekt klasy CDisplayable (body) /zgodnoœæ interfejsu/
		///
		CDisplayable* GetDisplayable();
	    
		///
		///Metoda zwraca wskaŸnik na obiekt klasy CDisplayable (shadow) /zgodnoœæ interfejsu/
		///
		CDisplayable* GetShadow();

		///
		///Metoda zwraca wskaŸnik na obiekt klasy CDisplayable (body)
		///
		///@param physical_part - wyliczenie EPhysicalPart - czêœæ physical
		///
		CDisplayable* GetDisplayable(EPhysicalPart physical_part);
	    
		///
		///Metoda zwraca wskaŸnik na obiekt klasy CDisplayable (shadow)
		///
		///@param physical_part - wyliczenie EPhysicalPart - czêœæ physical
		///
		CDisplayable* GetShadow(EPhysicalPart physical_part);

		///
		///Metoda zwraca wskaŸnik na obiekt klasy CDisplayable (body)
		///
		CDisplayable* GetDisplayableBody();
	    
		///
		///Metoda zwraca wskaŸnik na obiekt klasy CDisplayable (body shadow)
		///
		CDisplayable* GetDisplayableBodyShadow();

		///
		///Metoda zwraca wskaŸnik na obiekt klasy CDisplayable (head)
		///
		CDisplayable* GetDisplayableHead();

		///
		///Metoda zwraca wskaŸnik na obiekt klasy CDisplayable (head shadow)
		///
		CDisplayable* GetDisplayableHeadShadow();

		///
		///Metoda zwraca flagê, czy obiekt generuje cieñ (body)
		///
		bool GetUseShadowBody();

		///
		///Metoda ustawia flagê, czy obiekt ma generowaæ cieñ (body)
		///
		///@param use_shadow_body - flaga, czy obiekt ma generowaæ cieñ (body)
		///
		void SetUseShadowBody(bool use_shadow_body);

		///
		///Metoda zwraca flagê, czy obiekt generuje cieñ (head)
		///
		bool GetUseShadowHead();

		///
		///Metoda ustawia flagê, czy obiekt ma generowaæ cieñ (head)
		///
		///@param use_shadow_head - flaga, czy obiekt ma generowaæ cieñ (head)
		///
		void SetUseShadowHead(bool use_shadow_head);

		///
		///Metoda zwraca flagê, czy obiekt generuje cieñ (body and head) /zgodnoœæ interfejsu/
		///
		bool GetUseShadow();

		///
		///Metoda ustawia flagê, czy obiekt ma generowaæ cieñ (body and head) /zgodnoœæ interfejsu/
		///
		///@param use_shadow - flaga, czy obiekt ma generowaæ cieñ (body and head) /zgodnoœæ interfejsu/
		///
		void SetUseShadow(bool use_shadow);

		///
		///Metoda ustawia flagê dla obiektów gotowych do destrukcji
		///
		void MarkForDelete();
	    
		///
		///Wirtualna metoda zaznacza obiekty do destrukcji
		///
		virtual void Kill();

		///
		///Metoda zwraca flagê, czy obiekt jest gotowy do usuniecia
		///
		virtual bool IsDead();

		///
		///Metoda zwraca nazwê tekstury (body)
		///
		const std::string& GetTextureBody() const;
		
		///
		///Metoda ustatawia nazwê tekstury (body)
		///
		///@param texture_body - nazwa tekstury (body)
		///
		void SetTextureBody(const std::string& texture_body);

		///
		///Metoda zwraca nazwê tekstury (head)
		///
		const std::string& GetTextureHead() const;
		
		///
		///Metoda ustatwia nazwê tekstury (head)
		///
		///@param texture_head - nazwa tekstury (head)
		///
		void SetTextureHead(const std::string& texture_head);

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
		///Metoda zwraca statyczny wspó³czynnik wirtualnej wysokoœci obiektu
		///
		const float GetIncrease() const;

		///
		///Metoda ustawia statyczny wspó³czynnik wirtualnej wysokoœci obiektu
		///
		///@param increase - wirtualna wysokoœæ obiektu
		///
		const void SetIncrease(float increase) const;

		///
		///Metoda zwraca wskaŸnik na obiekt klasy CPhysicalTemplate
		///
		inline CPhysicalTemplate *GetTemplate() const { return p_template; }

		///
		///Metoda ustawia wskaŸnik na obiekt klasy CPhysicalTemplate
		///
		///@param *p_template - wskaŸnik na obiekt klasy CPhysicalTemplate
		///
		inline void SetTemplate(CPhysicalTemplate* p_template) { p_template = p_template; }

		///
		///Wirtualna metoda aktualizuj¹ca obiekt
		///
		///@param dt - czas
		///
		virtual void Update(float dt);

	protected:
	    
		std::wstring		m_unique_id;				//unikalny identyfikator (nadawany w CPhysicalManager)
		std::wstring		m_genre;					//nazwa "gatunku" obiektu (np. robot, human, gun, etc.)
		sf::Vector2f		m_position;					//wektor pozycji
		sf::Vector2f		m_old_position;				//wektor pozycji (przed aktualizacj¹)
		float				m_rotation_uniform;			//wartoœæ obrotu (body and head)
		float				m_rotation_body;			//wartoœæ obrotu (body)
		float				m_rotation_head;			//wartoœæ obrotu (head)
		sf::Vector2f		m_velocity;					//wektor prêdkoœci obiektu
		float				m_circle_radius;			//promieñ detekcji kolizji
		std::string			m_texture_body;				//nazwa tekstury reprezentacji graficznej obiektu - body
		std::string			m_texture_head;				//nazwa tekstury reprezentacji graficznej obiektu - head
		CAnimation*			p_animation_body;			//wskaŸnik na animacjê - body (cienie - taka sama animacja)
		CAnimation*			p_animation_head;			//wskaŸnik na animacjê - head (cienie - taka sama animacja)
		ECollisionShape		m_collision_shape;			//wyliczenie - typ detekcji kolizji
		sf::Vector2f		m_rect_size;				//wektor przechowuj¹cy rozmiar obszaru prostok¹tnego
		float				m_altitude;					//wartoœæ pu³apu obiektu wzglêdem pod³o¿a
		sf::Color			m_color_body;				//kolor obiektu - body
		sf::Color			m_color_head;				//kolor obiektu - head
		sf::Color			m_color_stored_body;		//zapamiêtany kolor obiektu
		sf::Color			m_color_stored_head;		//zapamiêtany kolor obiektu
		sf::Color			m_color_shadow;				//kolor cienia
		sf::Vector2f		m_shadow_offset_body;		//wektor przesuniêcia cienia - body
		sf::Vector2f		m_shadow_offset_head;		//wektor przesuniêcia cienia - head
		bool				m_ready_for_destruction;	//flaga ustawia obiekty gotowe do destrukcji
		bool				m_use_displayable_body;		//flaga okreœla, czy CPhysical posiada reprezentacjê graficzn¹ - body
		bool				m_use_shadow_body;			//flaga okreœla, czy CPhysical posiada reprezentacjê graficzn¹ - body - cieñ
		bool				m_use_displayable_head;		//flaga okreœla, czy CPhysical posiada reprezentacjê graficzn¹ - head
		bool				m_use_shadow_head;			//flaga okreœla, czy CPhysical posiada reprezentacjê graficzn¹ - head - cieñ
		CPhysicalTemplate*	p_template;					//wskaŸnik na obiekt klasy CPhysicalTemplate
		static float		m_shadow_init;				//wspó³czynnik przesuniêcia cienia w zale¿noœci od wielkoœci obiektu

	private:

		int					m_z_index;					//indeks warstwy rysowania
		int					m_physical_manager_index;	//wyliczony indeks w CPhysicalManager
		CDisplayable*		p_displayable_body;			//wskaŸnik na obiekt CDisplayable - body (czêœæ zasadnicza)
		CDisplayable*		p_displayable_body_shadow;	//wskaŸnik na obiekt CDisplayable - body shadow	(cieñ czêœci zasadniczej)
		CDisplayable*		p_displayable_head;			//wskaŸnik na obiekt CDisplayable - head (czêœæ dodatkowa)
		CDisplayable*		p_displayable_head_shadow;	//wskaŸnik na obiekt CDisplayable - head shadow (cieñ czêœci dodatkowej)
		float				m_init_height;				//wyliczona wirtualna wysokoœæ obiektu
		sf::Vector2f		m_stored_scale_body;		//zapamiêtana skala - pole pomocniczne - body
		sf::Vector2f		m_stored_scale_head;		//zapamiêtana skala - pole pomocniczne - head
		bool				m_smooth;					//flaga, czy obiekt wyg³adza piksele tekstury	
		static float		m_increase;					//wspó³czynnik wirtualnej wysokoœci obiektu

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

		void CheckDisplayableBody();		//prywatna metoda sprawdza, czy trzeba utworzyæ
											//obiekt klasy CDisplayable (body), np. gdy chcemy
											//dodaæ obrazek, animacjê, etc...

		void CheckDisplayableHead();		//prywatna metoda sprawdza, czy trzeba utworzyæ
											//obiekt klasy CDisplayable (head), np. gdy chcemy
											//dodaæ obrazek, animacjê, etc...

		void UpdateShadowOffset(float dt);	//prywatna metoda dobieraj¹ca przesuniêcie cienia
											//w zale¿noœci od wielkoœci obiektu - body and head

	};
}//namespace logic
#endif //H_PHYSICAL_SCI
