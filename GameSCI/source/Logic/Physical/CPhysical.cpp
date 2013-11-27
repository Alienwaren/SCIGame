/*
 ______________________________________
| CPhysical.cpp - implementacja klasy. |
| SCI - August 2012.                   |
|______________________________________|

*/

#include "CPhysical.h"
#include "../../Weather/CWeather.h"
#include "../../Rendering/Displayable/CDisplayable.h"
#include "../../Rendering/Drawable/CDrawableManager.h"
#include "../../Rendering/Drawable/Layers.h"
#include "../../Rendering/Animations/CAnimation.h"
#include "../../Rendering/Animations/CAnimationState.h"
#include "../../Factory/CPhysicalTemplate.h"
#include <math.h>

using namespace weather;

namespace logic
{
	//Chroniony konstruktor domy�lny - u�ywany wy��cznie przez CPhysicalManager
	CPhysical::CPhysical(const std::wstring& uniqueId)
	:
		//private:
		m_z_index					(Z_PHYSICAL_BODY),
		m_physical_manager_index	(-1),
		p_displayable_body			(NULL),
		p_displayable_body_shadow	(NULL),
		p_displayable_head			(NULL),
		p_displayable_head_shadow	(NULL),
		m_init_height				(0.0f),
		m_stored_scale_body			(1.0f, 1.0f),
		m_stored_scale_head			(1.0f, 1.0f),
		m_smooth					(false),

		//protected:
		m_unique_id					(uniqueId),
		m_genre						(),
		m_position					(0.0f, 0.0f),
		m_old_position				(0.0f, 0.0f),
		m_rotation_uniform			(0.0f),
		m_rotation_body				(0.0f),
		m_rotation_head				(0.0f),
		m_velocity					(0.0f, 0.0f),
		m_circle_radius				(1.0f),
		m_texture_body				(),
		m_texture_head				(),
		p_animation_body			(NULL),
		p_animation_head			(NULL),
		m_collision_shape			(SHAPE_CIRCLE),
		m_rect_size					(1.0f, 1.0f),
		m_altitude					(1.0f),
		m_color_body				(sf::Color()),
		m_color_head				(sf::Color()),
		m_color_stored_body			(sf::Color()),
		m_color_stored_head			(sf::Color()),
		m_color_shadow				(gWeather.GetWeatherShadowColor()),
		m_shadow_offset_body		(0.0f, 0.0f),
		m_shadow_offset_head		(0.0f, 0.0f),
		m_ready_for_destruction		(false),
		m_use_displayable_body		(true),
		m_use_shadow_body			(false),
		m_use_displayable_head		(true),
		m_use_shadow_head			(false),
		p_template					(NULL)
	{
	}

	//Chroniony konstruktor kopiuj�cy
	CPhysical::CPhysical(const CPhysical &CPhysicalCopy)
	:
		//private:
		m_z_index					(CPhysicalCopy.m_z_index),
		m_physical_manager_index	(CPhysicalCopy.m_physical_manager_index),
		p_displayable_body			(CPhysicalCopy.p_displayable_body),
		p_displayable_body_shadow	(CPhysicalCopy.p_displayable_body_shadow),
		p_displayable_head			(CPhysicalCopy.p_displayable_head),
		p_displayable_head_shadow	(CPhysicalCopy.p_displayable_head_shadow),
		m_init_height				(CPhysicalCopy.m_init_height),
		m_stored_scale_body			(CPhysicalCopy.m_stored_scale_body),
		m_stored_scale_head			(CPhysicalCopy.m_stored_scale_head),
		m_smooth					(CPhysicalCopy.m_smooth),

		//protected:
		m_unique_id					(CPhysicalCopy.m_unique_id),
		m_genre						(CPhysicalCopy.m_genre),
		m_position					(CPhysicalCopy.m_position),
		m_old_position				(CPhysicalCopy.m_old_position),
		m_rotation_uniform			(CPhysicalCopy.m_rotation_uniform),
		m_rotation_body				(CPhysicalCopy.m_rotation_body),
		m_rotation_head				(CPhysicalCopy.m_rotation_head),
		m_velocity					(CPhysicalCopy.m_velocity),
		m_circle_radius				(CPhysicalCopy.m_circle_radius),
		m_texture_body				(CPhysicalCopy.m_texture_body),
		m_texture_head				(CPhysicalCopy.m_texture_head),
		p_animation_body			(CPhysicalCopy.p_animation_body),
		p_animation_head			(CPhysicalCopy.p_animation_head),
		m_collision_shape			(CPhysicalCopy.m_collision_shape),
		m_rect_size					(CPhysicalCopy.m_rect_size),
		m_altitude					(CPhysicalCopy.m_altitude),
		m_color_body				(CPhysicalCopy.m_color_body),
		m_color_head				(CPhysicalCopy.m_color_head),
		m_color_stored_body			(CPhysicalCopy.m_color_stored_body),
		m_color_stored_head			(CPhysicalCopy.m_color_stored_head),
		m_color_shadow				(CPhysicalCopy.m_color_shadow),
		m_shadow_offset_body		(CPhysicalCopy.m_shadow_offset_body),
		m_shadow_offset_head		(CPhysicalCopy.m_shadow_offset_head),
		m_ready_for_destruction		(CPhysicalCopy.m_ready_for_destruction),
		m_use_displayable_body		(CPhysicalCopy.m_use_displayable_body),
		m_use_shadow_body			(CPhysicalCopy.m_use_shadow_body),
		m_use_displayable_head		(CPhysicalCopy.m_use_displayable_head),
		m_use_shadow_head			(CPhysicalCopy.m_use_shadow_head),
		p_template					(CPhysicalCopy.p_template)
	{
	}

	//Chroniony destruktor wirtualny - u�ywany wy��cznie przez CPhysicalManager
	CPhysical::~CPhysical()
	{
		if (p_displayable_body)
			gDrawableManager.DestroyDrawable(p_displayable_body);

		if (p_displayable_body_shadow)
			gDrawableManager.DestroyDrawable(p_displayable_body_shadow);

		if (p_displayable_head)
			gDrawableManager.DestroyDrawable(p_displayable_head);

		if (p_displayable_head_shadow)
			gDrawableManager.DestroyDrawable(p_displayable_head_shadow);

		//private:
		m_z_index					= 0;
		m_physical_manager_index	= 0;
		p_displayable_body			= NULL;
		p_displayable_body_shadow	= NULL;
		p_displayable_head			= NULL;
		p_displayable_head_shadow	= NULL;
		m_init_height				= 0.0f;
		//m_stored_scale_body		not edit
		//m_stored_scale_head		not edit
		m_smooth					= false;

		//protected:
		m_unique_id					= L"";
		m_genre						= L"";
		//m_position				not edit
		//m_old_position			not edit
		m_rotation_uniform			= 0.0f;
		m_rotation_body				= 0.0f;
		m_rotation_head				= 0.0f;
		//m_velocity				not edit
		m_circle_radius				= 0.0f;
		m_texture_body				= "";
		m_texture_head				= "";
		p_animation_body			= NULL;
		p_animation_head			= NULL;
		//m_collision_shape			not edit
		//m_rect_size				not edit
		m_altitude					= 0.0f;
		//m_color_body				not edit
		//m_color_head				not edit
		//m_color_stored_body		not edit
		//m_color_stored_head		not edit
		//m_color_shadow			not edit
		//m_shadow_offset_body		not edit
		//m_shadow_offset_head		not edit
		//m_ready_for_destruction	not edit
		m_use_displayable_body		= false;
		m_use_shadow_body			= false;
		m_use_displayable_head		= false;
		m_use_shadow_head			= false;
		p_template					= NULL;
		m_increase					= 0.0f;//static	
		m_shadow_init				= 0.0f;//static	
	}

	//Metoda zwraca unikaln� nazw� obiektu klasy CPhysical
	const std::wstring& CPhysical::GetUniqueId() const
	{
		return m_unique_id;
	}

	//Metoda zwraca nazw� gatunku
	const std::wstring& CPhysical::GetGenre()
	{
		return m_genre; 
	}

	//Metoda ustawia nazw� gatunku
	void CPhysical::SetGenre(const std::wstring& genre)
	{
		m_genre = genre; 
	}

	//Metoda zwraca pozycj� obiektu
	const sf::Vector2f& CPhysical::GetPosition() const
	{
		return m_position;
	}

	//Metoda ustawia pozycj� obiektu
	void CPhysical::SetPosition(float x, float y, bool change_old_position)
	{
									//zak�adamy, �e body and head ma wsp�ny uchwyt
		m_position.x = x;			//aktualizacja pola w klasie (wektor pozycji - x)
		m_position.y = y;			//aktualizacja pola w klasie (wektor pozycji - y)

		if (p_displayable_body)
			p_displayable_body->setPosition(m_position.x, m_position.y);

		if (p_displayable_head)
			p_displayable_head->setPosition(m_position.x, m_position.y);
		
		if (p_displayable_body_shadow)
			p_displayable_body_shadow->setPosition(m_position.x + m_shadow_offset_body.x, m_position.y + m_shadow_offset_body.y);

		if (p_displayable_head_shadow)
			p_displayable_head_shadow->setPosition(m_position.x + m_shadow_offset_head.x, m_position.y + m_shadow_offset_head.y);

		if (change_old_position)
			m_old_position = m_position;
	}

	//Metoda ustawia pozycj� obiektu
	void CPhysical::SetPosition(const sf::Vector2f& new_value, bool change_old_position)
	{
									//zak�adamy, �e body and head ma wsp�ny uchwyt
		m_position = new_value;		//aktualizacja pola w klasie (wektor pozycji)
		
		if (p_displayable_body)
			p_displayable_body->setPosition(m_position);

		if (p_displayable_head)
			p_displayable_head->setPosition(m_position);
		
		if (p_displayable_body_shadow)
			p_displayable_body_shadow->setPosition(m_position + m_shadow_offset_body);

		if (p_displayable_head_shadow)
			p_displayable_head_shadow->setPosition(m_position + m_shadow_offset_head);

		if (change_old_position)
			m_old_position = m_position;
	}

	//Metoda zwraca pozycj� przed aktualizacj� logiki m_old_position
	const sf::Vector2f& CPhysical::GetOldPosition() const
	{
		return m_old_position;
	}

	//Metoda zwraca skal� (body)
	const Vector2f& CPhysical::GetScaleBody() const
	{
		return p_displayable_body->getScale();
	}

	//Metoda ustawia skal� (body)
	void CPhysical::SetScaleBody(float scale_X, float scale_Y)
	{
		//zapami�tuj� skal�
		m_stored_scale_body.x = scale_X;
		m_stored_scale_body.y = scale_Y;

		//obiekt zasadniczy i cie� zawsze maj� t� sam� skal�
		if(p_displayable_body)
			p_displayable_body->setScale(scale_X, scale_Y);

		if(p_displayable_body_shadow)
			p_displayable_body_shadow->setScale(scale_X, scale_Y);
	}

	//Metoda ustawia skal� (body)
	void CPhysical::SetScaleBody(const sf::Vector2f& scale_vector)
	{
		//zapami�tuj� skal�
		m_stored_scale_body = scale_vector;

		//obiekt zasadniczy i cie� zawsze maj� t� sam� skal�
		if(p_displayable_body)
			p_displayable_body->setScale(scale_vector);

		if(p_displayable_body_shadow)
			p_displayable_body_shadow->setScale(scale_vector);
	}

	//Metoda zwraca skal� (body)
	const sf::Vector2f& CPhysical::GetScaleHead() const
	{
		return p_displayable_head->getScale();
	}

	//Metoda ustawia skal� (head)
	void CPhysical::SetScaleHead(float scale_X, float scale_Y)
	{
		//zapami�tuj� skal�
		m_stored_scale_head.x = scale_X;
		m_stored_scale_head.y = scale_Y;

		//obiekt zasadniczy i cie� zawsze maj� t� sam� skal�
		if(p_displayable_head)
			p_displayable_head->setScale(scale_X, scale_Y);

		if(p_displayable_head_shadow)
			p_displayable_head_shadow->setScale(scale_X, scale_Y);
	}

	//Metoda ustawia skal� (head)
	void CPhysical::SetScaleHead(const sf::Vector2f& scale_vector)
	{
		//zapami�tuj� skal�
		m_stored_scale_head = scale_vector;

		//obiekt zasadniczy i cie� zawsze maj� t� sam� skal�
		if(p_displayable_head)
			p_displayable_head->setScale(scale_vector);

		if(p_displayable_head_shadow)
			p_displayable_head_shadow->setScale(scale_vector);
	}

	//Metoda ustawia skal� (body and head)
	void CPhysical::SetScale(float scale_X, float scale_Y)
	{
		//zapami�tuj� skal�
		m_stored_scale_body.x = scale_X;
		m_stored_scale_body.y = scale_Y;

		//zapami�tuj� skal�
		m_stored_scale_head.x = scale_X;
		m_stored_scale_head.y = scale_Y;

		//obiekt zasadniczy i cie� zawsze maj� t� sam� skal�
		if(p_displayable_body)
			p_displayable_body->setScale(scale_X, scale_Y);

		if(p_displayable_body_shadow)
			p_displayable_body_shadow->setScale(scale_X, scale_Y);

		//obiekt zasadniczy i cie� zawsze maj� t� sam� skal�
		if(p_displayable_head)
			p_displayable_head->setScale(scale_X, scale_Y);

		if(p_displayable_head_shadow)
			p_displayable_head_shadow->setScale(scale_X, scale_Y);
	}

	//Metoda ustawia skal� (body and head)
	void CPhysical::SetScale(const sf::Vector2f& scale)
	{
		//zapami�tuj� skal�
		m_stored_scale_body = scale;
		m_stored_scale_head = scale;

		//obiekt zasadniczy i cie� zawsze maj� t� sam� skal�
		if(p_displayable_body)
			p_displayable_body->setScale(scale);

		if (p_displayable_body_shadow)
			p_displayable_body_shadow->setScale(scale);

		//obiekt zasadniczy i cie� zawsze maj� t� sam� skal�
		if(p_displayable_head)
			p_displayable_head->setScale(scale);

		if (p_displayable_head_shadow)
			p_displayable_head_shadow->setScale(scale);
	}

	//Metoda ustawia skal�
	void CPhysical::SetScale(float uniform)
	{
		//zapami�tuj� skal�
		m_stored_scale_body.x = uniform;
		m_stored_scale_head.y = uniform;

		//obiekt zasadniczy i cie� zawsze maj� t� sam� skal�
		if(p_displayable_body)
			p_displayable_body->setScale(uniform);

		if (p_displayable_body_shadow)
			p_displayable_body_shadow->setScale(uniform);

		//obiekt zasadniczy i cie� zawsze maj� t� sam� skal�
		if(p_displayable_head)
			p_displayable_head->setScale(uniform);

		if (p_displayable_head_shadow)
			p_displayable_head_shadow->setScale(uniform);
	}

	//Metoda zwraca warto�� obrotu obiektu w stopniach
	float CPhysical::GetRotation()
	{
		return m_rotation_uniform;
		//m_rotation_uniform;		//warto�� obrotu (body and head)
		//m_rotation_body;			//warto�� obrotu (body)
		//m_rotation_head;			//warto�� obrotu (head)
	}

	//Metoda ustawia warto�� obrotu obiektu w stopniach (body and head)
	void CPhysical::SetRotation(float rotation)
	{
		//zapami�tuj� rotacj�
		m_rotation_uniform = rotation;
		
		//body
		if (p_displayable_body)
			p_displayable_body->setRotation(m_rotation_uniform);

		if (p_displayable_body_shadow)
			p_displayable_body_shadow->setRotation(m_rotation_uniform);

		//head
		if (p_displayable_head)
			p_displayable_head->setRotation(m_rotation_uniform);

		if (p_displayable_head_shadow)
			p_displayable_head_shadow->setRotation(m_rotation_uniform);
	}

	//Metoda zwraca warto�� obrotu obiektu w stopniach (body)
	float CPhysical::GetRotationBody()
	{
		return m_rotation_body;
	}

	//Metoda ustawia warto�� obrotu obiektu w stopniach (body)
	void CPhysical::SetRotationBody(float rotation_body)
	{
		//zapami�tuj� rotacj�
		m_rotation_body = rotation_body;

		if (p_displayable_body)
			p_displayable_body->setRotation(m_rotation_body);

		if (p_displayable_body_shadow)
			p_displayable_body_shadow->setRotation(m_rotation_body);
	}

	//Metoda zwraca warto�� obrotu obiektu w stopniach (head)
	float CPhysical::GetRotationHead()
	{
		return m_rotation_head;
	}

	//Metoda ustawia warto�� obrotu obiektu w stopniach (head)
	void CPhysical::SetRotationHead(float rotation_head)
	{
		//zapami�tuj� rotacj�
		m_rotation_head = rotation_head ;

		if (p_displayable_head)
			p_displayable_head ->setRotation(m_rotation_head);

		if (p_displayable_head_shadow)
			p_displayable_head_shadow->setRotation(m_rotation_head );
	}

	//Metoda obraca obiekt o zadany k�t (body)
	void CPhysical::RotateBody(float angle)
	{
		if (p_displayable_body)
			p_displayable_body->rotate(angle);

		if (p_displayable_body_shadow)
			p_displayable_body_shadow->rotate(angle);
	}

	//Metoda obraca obiekt o zadany k�t (head)
	void CPhysical::RotateHead(float angle)
	{
		if (p_displayable_head)
			p_displayable_head->rotate(angle);

		if (p_displayable_head_shadow)
			p_displayable_head_shadow->rotate(angle);
	}

	//Metoda obraca obiekt o zadany k�t (body and head)
	void CPhysical::Rotate(float angle)
	{
		RotateBody(angle);
		RotateHead(angle);
	}

	//Metoda zwraca pr�dko�� obiektu
	const sf::Vector2f& CPhysical::GetVelocity() const
	{
		return m_velocity;
	}

	//Metoda ustawia pr�dko�� obiektu
	void CPhysical::SetVelocity(const sf::Vector2f& velocity)
	{
		m_velocity = velocity;
	}

	//Metoda zwraca promie� detekcji wykorzystywany przy liczeniu kolizji
	float CPhysical::GetCircleRadius()
	{
		return m_circle_radius;
	}

	//Metoda zwraca wyliczenie - typ liczenia kolizji
	ECollisionShape CPhysical::GetCollisionShape()
	{
		return m_collision_shape;
	}

	//Wirtualna metoda ustawiaj�ca warto�� promienia detekcji wykorzystywan� przy liczeniu kolizji
	void CPhysical::SetBoundingCircle(float radius)
	{
		m_collision_shape = SHAPE_CIRCLE;
		m_circle_radius = radius;
		//obliczamy boki prostok�ta (uproszczenie do kwadratu) wpisanego w okrag
		m_rect_size.x = m_rect_size.y = radius * 2.0f;
	}

	//Metoda ustawia warto�� obszaru prostok�tnego detekcji wykorzystywany przy liczeniu kolizji
	void CPhysical::SetBoundingRect(const sf::Vector2f& rect_size)
	{
		m_collision_shape = SHAPE_RECT;
		m_rect_size = rect_size;
		//obliczamy przeciwprostok�tn�, czyli �rednic� okr�gu opisanego na prostok�cie
		m_circle_radius =  sqrtf(rect_size.x * rect_size.x + rect_size.y * rect_size.y);
	}

	//Metoda zwraca wektor dla obszaru prostok�tnego detekcji wykorzystywany przy liczeniu kolizji
	const sf::Vector2f& CPhysical::GetRectSize() const
	{
		return m_rect_size;
	}

	//Metoda zwraca warto�� pu�apu obiektu
	const float CPhysical::GetAltitude() const
	{
		return m_altitude;
	}

	//Metoda ustawia warto�� pu�apu obiektu
	void CPhysical::SetAltitude(float altitude)
	{
		if(altitude < 0) return;
		m_altitude = altitude;
	}


	//Metoda zwraca kolor obiektu - body
	const sf::Color& CPhysical::GetColor() const
	{
		return m_color_body;	//umawiamy si�, �e default to cz�� body
	}

	//Metoda ustawia kolor obiektu - (body and head)
	void CPhysical::SetColor(const sf::Color& color)
	{
		if (p_displayable_body)
			p_displayable_body->setColor(color);
		
		if (p_displayable_head)
			p_displayable_head->setColor(color);
	}

	//Metoda zwraca kolor obiektu - body
	const sf::Color& CPhysical::GetColorBody() const
	{
		return m_color_body;	//umawiamy si�, �e default to cz�� body
	}

	//Metoda ustawia kolor obiektu - body
	void CPhysical::SetColorBody(const sf::Color& color_body)
	{
		m_color_body = color_body;
		if (p_displayable_body)
			p_displayable_body->setColor(m_color_body);
	}

	//Metoda zwraca kolor obiektu - head
	const sf::Color& CPhysical::GetColorHead() const
	{
		return m_color_head;
	}

	//Metoda ustawia kolor obiektu - head
	void CPhysical::SetColorHead(const sf::Color& color_head)
	{
		m_color_head = color_head;
		if (p_displayable_head)
			p_displayable_head->setColor(color_head);
	}

	//Metoda ustawia oryginalny kolor obiektu za�adowany z tekstury - body and head
	void CPhysical::RestoreColor()
	{
		SetColorBody(m_color_stored_body);
		SetColorHead(m_color_stored_head);
	}

	//Metoda ustawia oryginalny kolor obiektu za�adowany z tekstury - body
	void CPhysical::RestoreColorBody()
	{
		SetColorBody(m_color_stored_body);
	}

	//Metoda ustawia oryginalny kolor obiektu za�adowany z tekstury - head
	void CPhysical::RestoreColorHead()
	{
		SetColorHead(m_color_stored_head);
	}


	//Metoda zwraca kolor cienia obiektu
	const sf::Color& CPhysical::GetColorShadow() const
	{
		return m_color_shadow;
	}

	//Metoda ustawia kolor cienia obiektu
	void CPhysical::SetColorShadow(const sf::Color& color_shadow)
	{
		m_color_shadow = color_shadow;
	}

	//Metoda zwraca wektor przesuni�cia cienia wzgl�dem obiektu - body
	sf::Vector2f CPhysical::GetShadowOffsetBody() const
	{
		return m_shadow_offset_body;
		//return m_shadow_offset_body * m_altitude;	//niech to tutaj zostanie...mo�e si� przyda...
	}

	//Metoda ustawia wektor przesuni�cia cienia wzgl�dem obiektu - body
	void CPhysical::SetShadowOffsetBody(sf::Vector2f& shadow_offset_body)
	{
		m_shadow_offset_body = shadow_offset_body;
	}

	//Metoda zwraca wektor przesuni�cia cienia wzgl�dem obiektu - head
	sf::Vector2f CPhysical::GetShadowOffsetHead() const
	{
		return m_shadow_offset_head;
		//return m_shadow_offset_head * m_altitude;	//niech to tutaj zostanie...mo�e si� przyda...
	}

	//Metoda ustawia wektor przesuni�cia cienia wzgl�dem obiektu - head
	void CPhysical::SetShadowOffsetHead(sf::Vector2f& shadow_offset_head)
	{
		m_shadow_offset_head = shadow_offset_head;
	}

	//Metoda zwraca wska�nik na animacj�
	CAnimation *CPhysical::GetAnimation(EPhysicalPart physical_part)
	{
		if (physical_part == BODY)
			return p_animation_body;
		else if (physical_part == HEAD)
			return p_animation_head;
		//default
		return p_animation_body;
	}

	//Metoda ustawia ustawia wska�nik na animacj�
	void CPhysical::SetAnimation(CAnimation* p_anim, EPhysicalPart physical_part)
	{
		if (physical_part == BODY)
			SetAnimationBody(p_anim);
		else if (physical_part == HEAD)
			SetAnimationHead(p_anim);
		else return;
	}

	//Metoda ustawia nazw� animacji (only body) /zgodno�� interfejsu/
	void CPhysical::SetAnimation(const std::string& anim_name, EPhysicalPart physical_part)
	{
		if (physical_part == BODY)
			SetAnimationBody(anim_name);
		else if (physical_part == HEAD)
			SetAnimationHead(anim_name);
		else return;
	}

	//Metoda zwraca nazw� animacji
	const std::string& CPhysical::GetAnimationName(EPhysicalPart physical_part) const
	{
		if (physical_part == BODY)
			return p_displayable_body->GetAnimationState()->GetAnimation()->GetAnimationName();
		else if (physical_part == HEAD)
			return p_displayable_head->GetAnimationState()->GetAnimation()->GetAnimationName();
		//default
		return p_displayable_body->GetAnimationState()->GetAnimation()->GetAnimationName();
	}

	//Metoda zwraca wska�nik na animacj� (body) /zgodno�� interfejsu/
	CAnimation *CPhysical::GetAnimation()
	{
		return GetAnimationBody();
	}

	//Metoda ustawia ustawia wska�nik na animacj� (body) /zgodno�� interfejsu/
	void CPhysical::SetAnimation(CAnimation* p_anim)
	{
		SetAnimationBody(p_anim);
	}

	//Metoda ustawia nazw� animacji (body) /zgodno�� interfejsu/
	void CPhysical::SetAnimation(const std::string& anim_name)
	{
		SetAnimationBody(anim_name);
	}

	//Metoda zwraca nazw� animacji (body) /zgodno�� interfejsu/
	const std::string& CPhysical::GetAnimationName() const
	{
		return GetAnimationBodyName();
	}

	//Metoda zwraca wska�nik na animacj� - obiekt klasy CAnimation (body)
	CAnimation *CPhysical::GetAnimationBody()
	{
		return p_animation_body;
	}

	//Metoda ustawia ustawia wska�nik na animacj� (body)
	void CPhysical::SetAnimationBody(CAnimation* p_anim_body)
	{
		CheckDisplayableBody();
		p_animation_body = p_anim_body;

		if (p_displayable_body)
			p_displayable_body->SetAnimation(p_animation_body);

		if (p_displayable_body_shadow)
			p_displayable_body_shadow->SetAnimation(p_animation_body);
	}

	//Metoda zwraca nazw� animacji (body)
	const std::string& CPhysical::GetAnimationBodyName() const
	{
		return p_displayable_body->GetAnimationState()->GetAnimation()->GetAnimationName();
	}

	//Metoda ustawia nazw� animacji (body)
	void CPhysical::SetAnimationBody(const std::string& anim_body_name)
	{
		CheckDisplayableBody();

		if (p_displayable_body)
			p_displayable_body->SetAnimation(anim_body_name);

		if (p_displayable_body_shadow)
			p_displayable_body_shadow->SetAnimation(anim_body_name);

		//po za�adowaniu animacji (parametr std::string), aktualizacja wska�nika
		if(p_displayable_body)
			p_animation_body = p_displayable_body->GetAnimationState()->GetAnimation();
	}

	//Metoda zwraca wska�nik na animacj� - obiekt klasy CAnimation (head)
	CAnimation *CPhysical::GetAnimationHead()
	{
		return p_animation_head;
	}

	//Metoda ustawia ustawia wska�nik na animacj� (head)
	void CPhysical::SetAnimationHead(CAnimation* p_anim_head)
	{
		CheckDisplayableHead();
		p_animation_head = p_anim_head;

		if (p_displayable_head)
			p_displayable_head->SetAnimation(p_animation_head);

		if (p_displayable_head_shadow)
			p_displayable_head_shadow->SetAnimation(p_animation_head);
	}

	//Metoda zwraca nazw� animacji (head)
	const std::string& CPhysical::GetAnimationHeadName() const
	{
		return p_displayable_head->GetAnimationState()->GetAnimation()->GetAnimationName();
	}

	//Metoda ustawia nazw� animacji (head)
	void CPhysical::SetAnimationHead(const std::string& anim_head_name)
	{
		CheckDisplayableHead();

		if (p_displayable_head)
			p_displayable_head->SetAnimation(anim_head_name);

		if (p_displayable_head_shadow)
			p_displayable_head_shadow->SetAnimation(anim_head_name);

		//po za�adowaniu animacji (parametr std::string), aktualizacja wska�nika
		if(p_displayable_head)
			p_animation_head = p_displayable_head->GetAnimationState()->GetAnimation();
	}

	//Metoda ustawia komplet animacji
	void CPhysical::SetAnimation(CAnimation *p_anim_body, CAnimation *p_anim_head)
	{
		SetAnimationBody(p_anim_body);
		SetAnimationHead(p_anim_head);
	}

	//Metoda ustawia komplet animacji
	void CPhysical::SetAnimation(const std::string& anim_name_body, const std::string& anim_name_head)
	{
		SetAnimationBody(anim_name_body);
		SetAnimationHead(anim_name_head);
	}

	//Metoda zwraca wska�nik na obiekt klasy CDisplayable (body) /zgodno�� interfejsu/
	CDisplayable * CPhysical::GetDisplayable()
	{
		return p_displayable_body;
	}

	//Metoda zwraca wska�nik na obiekt klasy CDisplayable (shadow) /zgodno�� interfejsu/
	CDisplayable * CPhysical::GetShadow()
	{
		return p_displayable_body_shadow;
	}

	//Metoda zwraca wska�nik na obiekt klasy CDisplayable (body)
	CDisplayable * CPhysical::GetDisplayable(EPhysicalPart physical_part)
	{
		if (physical_part == BODY)
			return p_displayable_body;
		else if (physical_part == HEAD)
			return p_displayable_head;
		return p_displayable_body;
	}

	//Metoda zwraca wska�nik na obiekt klasy CDisplayable (shadow)
	CDisplayable * CPhysical::GetShadow(EPhysicalPart physical_part)
	{
		if (physical_part == BODY)
			return p_displayable_body_shadow;
		else if (physical_part == HEAD)
			return p_displayable_head_shadow;
		return p_displayable_body_shadow;
	}

	//Metoda zwraca wska�nik na obiekt klasy CDisplayable (body)
	CDisplayable * CPhysical::GetDisplayableBody()
	{
		return p_displayable_body;
	}

	//Metoda zwraca wska�nik na obiekt klasy CDisplayable (body shadow)
	CDisplayable * CPhysical::GetDisplayableBodyShadow()
	{
		return p_displayable_body_shadow;
	}

	//Metoda zwraca wska�nik na obiekt klasy CDisplayable (head)
	CDisplayable * CPhysical::GetDisplayableHead()
	{
		return p_displayable_head;
	}

	//Metoda zwraca wska�nik na obiekt klasy CDisplayable (head shadow)
	CDisplayable * CPhysical::GetDisplayableHeadShadow()
	{
		return p_displayable_head_shadow;
	}

	//Metoda zwraca flag�, czy obiekt generuje cie� (body)
	bool CPhysical::GetUseShadowBody()
	{
		return m_use_shadow_body;
	}

	//Metoda ustawia flag�, czy obiekt ma generowa� cie� (body)
	void CPhysical::SetUseShadowBody(bool use_shadow_body)
	{
		m_use_shadow_body = use_shadow_body;
	}

	//Metoda zwraca flag�, czy obiekt generuje cie� (head)
	bool CPhysical::GetUseShadowHead()
	{
		return m_use_shadow_head;
	}

	//Metoda ustawia flag�, czy obiekt ma generowa� cie� (head)
	void CPhysical::SetUseShadowHead(bool use_shadow_head)
	{
		m_use_shadow_head = use_shadow_head;
	}

	//Metoda zwraca flag�, czy obiekt generuje cie� (body and head) /zgodno�� interfejsu/
	bool CPhysical::GetUseShadow()
	{
		return m_use_shadow_body;
		//return m_use_shadow_head;
	}

	//Metoda ustawia flag�, czy obiekt ma generowa� cie� (body and head) /zgodno�� interfejsu/
	void CPhysical::SetUseShadow(bool use_shadow)
	{
		m_use_shadow_body = use_shadow;	//body
		m_use_shadow_head = use_shadow;	//head
	}

	//Metoda ustawia flag� dla obiekt�w gotowych do destrukcji
	void CPhysical::MarkForDelete()
	{
		m_ready_for_destruction = true;
	}

	//Wirtualna metoda zaznacza obiekty do destrukcji
	void CPhysical::Kill()
	{
		MarkForDelete();
	}

	//Metoda zwraca flag�, czy obiekt jest gotowy do usuniecia
	bool CPhysical::IsDead()
	{
		return m_ready_for_destruction;
	}

	//Metoda zwraca nazw� tekstury
	const std::string& CPhysical::GetTextureBody() const
	{
		return m_texture_body;
	}

	//Metoda ustatawia nazw� tekstury (body)
	void CPhysical::SetTextureBody(const std::string& texture_body)
	{
		m_texture_body = texture_body;

		CheckDisplayableBody();

		if (p_displayable_body)
			p_displayable_body->setTexture(m_texture_body);

		if (p_displayable_body_shadow)
			p_displayable_body_shadow->setTexture(m_texture_body);
	}

	//Metoda zwraca nazw� tekstury (head)
	const std::string& CPhysical::GetTextureHead() const
	{
		return m_texture_head;
	}

	//Metoda ustatwia nazw� tekstury (head)
	void CPhysical::SetTextureHead(const std::string& texture_head)
	{
		CheckDisplayableHead();

		if (p_displayable_head)
			p_displayable_head->setTexture(texture_head);

		if (p_displayable_head_shadow)
			p_displayable_head_shadow->setTexture(texture_head);
	}

	//Metoda zwraca tryb wyg�adzania tekstury
	const bool CPhysical::getSmoothing() const
	{
		return m_smooth;
	}

	//Metoda ustawia tryb wyg�adzania tekstury
	void CPhysical::setSmoothing(bool smooth)
	{
		m_smooth = smooth; //zapamietuj� flag� wyg�adzania tekstury

		if(p_displayable_body)
			p_displayable_body->setSmoothing(m_smooth);
		if(p_displayable_body_shadow)
			p_displayable_body_shadow->setSmoothing(m_smooth);
		if(p_displayable_head)
			p_displayable_head->setSmoothing(m_smooth);
		if(p_displayable_head_shadow)
			p_displayable_head_shadow->setSmoothing(m_smooth);
	}

	//Metoda zwraca statyczny wsp�czynnik wirtualnej wysoko�ci obiektu
	const float CPhysical::GetIncrease() const
	{
		return m_increase;
	}

	//Metoda ustawia statyczny wsp�czynnik wirtualnej wysoko�ci obiektu
	const void CPhysical::SetIncrease(float increase) const
	{
		m_increase = increase;
	}

	//Wirtualna metoda aktualizuj�ca obiekt
	void CPhysical::Update(float dt)
	{
		sf::Vector2f new_position;
		new_position.x = m_position.x + (dt * m_velocity.x);
		new_position.y = m_position.y + (dt * m_velocity.y);
		m_old_position = m_position;
		SetPosition(new_position);

		//aktualizacja wektora cienia i "obiegu s�o�ca/gwiazdy"...
		UpdateShadowOffset(dt);
	}

	//implementajca metod protected:

	//Metoda ustawia indeks warstwy renderingu obiektu
	void CPhysical::SetZIndex(int layer_index)
	{
		//metoda rejestruje obiekt tylko wtedy, gdy parametr,
		//indeks warstwy jest inny ni� w tej klasie (Z_PHYSICAL_BODY)
		//co mo�e by� zaimplementowane w klasach pochodnych
		//oraz gdy wska�nik jest zainicjowany
		if ((m_z_index != layer_index) &&(p_displayable_body!= NULL))
			gDrawableManager.RegisterDrawable(p_displayable_body, layer_index);
		
		m_z_index = layer_index;
	}

	//implementajca metod private:

	//prywatna metoda sprawdza, czy trzeba utworzy� obiekt klasy CDisplayable
	void CPhysical::CheckDisplayableBody()
	{
		//body - oryginal
		if ((m_use_displayable_body) && (!p_displayable_body))
		{
			p_displayable_body = gDrawableManager.CreateDisplayable(Z_PHYSICAL_BODY);
			if (!p_displayable_body)
			{
				fprintf(stderr, "error: CPhysical::CheckDisplayable, p_displayable_body null, returning\n");
				return;
			}
			p_displayable_body->setPosition(m_position);
			p_displayable_body->setRotation(m_rotation_body);
			p_displayable_body->setColor(p_displayable_body->getColor());
			p_displayable_body->setScale(m_stored_scale_body);
			m_color_stored_body = p_displayable_body->getColor();//zapami�tujemy oryginalny kolor
		}

		//body - shadow
		if ((m_use_shadow_body) && (!p_displayable_body_shadow))
		{
			p_displayable_body_shadow = gDrawableManager.CreateDisplayable(Z_PHYSICAL_SHADOWS_BODY);
			if ( !p_displayable_body_shadow )
			{
				fprintf(stderr, "error: CPhysical::CheckDisplayable, p_displayable_body_shadow null, returning\n");
				return;
			}
			p_displayable_body_shadow->setPosition(m_position.x + m_shadow_offset_body.x, m_position.y + m_shadow_offset_body.y);
			p_displayable_body_shadow->setRotation(m_rotation_body);
			p_displayable_body_shadow->setColor(gWeather.GetWeatherShadowColor());
			p_displayable_body_shadow->setScale(m_stored_scale_body);
		}
	}

	//prywatna metoda sprawdza, czy trzeba utworzy� obiekt klasy CDisplayable
	void CPhysical::CheckDisplayableHead()
	{
		//head - oryginal
		if ((m_use_displayable_head) && (!p_displayable_head))
		{
			p_displayable_head = gDrawableManager.CreateDisplayable(Z_PHYSICAL_HEAD);
			if (!p_displayable_head)
			{
				fprintf(stderr, "error: CPhysical::CheckDisplayable, p_displayable_head null, returning\n");
				return;
			}
			p_displayable_head->setPosition(m_position);
			p_displayable_head->setRotation(m_rotation_head);
			p_displayable_head->setColor(p_displayable_head->getColor());
			p_displayable_head->setScale(m_stored_scale_head);
			m_color_stored_head = p_displayable_head->getColor();//zapami�tujemy oryginalny kolor
		}

		//head - shadow
		if ((m_use_shadow_head) && (!p_displayable_head_shadow))
		{
			p_displayable_head_shadow = gDrawableManager.CreateDisplayable(Z_PHYSICAL_SHADOWS_HEAD);
			if ( !p_displayable_head_shadow )
			{
				fprintf(stderr, "error: CPhysical::CheckDisplayable, p_displayable_head_shadow null, returning\n");
				return;
			}
			p_displayable_head_shadow->setPosition(m_position.x + m_shadow_offset_head.x, m_position.y + m_shadow_offset_head.y);
			p_displayable_head_shadow->setRotation(m_rotation_head);
			p_displayable_head_shadow->setColor(gWeather.GetWeatherShadowColor());
			p_displayable_head_shadow->setScale(m_stored_scale_head);
		}
	}

	//prywatna metoda dobieraj�ca przesuni�cie cienia w zale�no�ci od wielko�ci obiektu - body and head
	void CPhysical::UpdateShadowOffset(float dt)
	{
		//offset body
		if(p_displayable_body)
		{
			if(p_displayable_body->GetSprite()->getLocalBounds().width >= p_displayable_body->GetSprite()->getLocalBounds().height)
			{
				m_shadow_offset_body.x = p_displayable_body->GetSprite()->getLocalBounds().height * m_shadow_init * p_displayable_body->getScale().x * m_altitude;
				m_shadow_offset_body.y = p_displayable_body->GetSprite()->getLocalBounds().height * m_shadow_init * p_displayable_body->getScale().y * m_altitude;
			}
			else
			{
				m_shadow_offset_body.x = p_displayable_body->GetSprite()->getLocalBounds().width * m_shadow_init * p_displayable_body->getScale().x * m_altitude;
				m_shadow_offset_body.y = p_displayable_body->GetSprite()->getLocalBounds().width * m_shadow_init * p_displayable_body->getScale().y * m_altitude;
			}

			//shadow position body
			if(m_use_shadow_body)
				if(p_displayable_body_shadow)
					p_displayable_body_shadow->setPosition
					(
						p_displayable_body->getPosition().x + (m_shadow_offset_body.x * cos(gWeather.GetDegree())),
						p_displayable_body->getPosition().y + (m_shadow_offset_body.y * sin(gWeather.GetDegree()))
					);
		}

		//offset head
		if(p_displayable_head)
		{
			if(p_displayable_head->GetSprite()->getLocalBounds().width >= p_displayable_head->GetSprite()->getLocalBounds().height)
			{
				m_shadow_offset_head.x = p_displayable_head->GetSprite()->getLocalBounds().height * m_shadow_init * p_displayable_head->getScale().x * m_altitude;
				m_shadow_offset_head.y = p_displayable_head->GetSprite()->getLocalBounds().height * m_shadow_init * p_displayable_head->getScale().y * m_altitude;
			}
			else
			{
				m_shadow_offset_head.x = p_displayable_head->GetSprite()->getLocalBounds().width * m_shadow_init * p_displayable_head->getScale().x * m_altitude;
				m_shadow_offset_head.y = p_displayable_head->GetSprite()->getLocalBounds().width * m_shadow_init * p_displayable_head->getScale().y * m_altitude;
			}
			
			//shadow position head
			if(m_use_shadow_head)
				if(p_displayable_head_shadow)
					p_displayable_head_shadow->setPosition
					(
						p_displayable_head->getPosition().x + (m_shadow_offset_head.x * cos(gWeather.GetDegree())),
						p_displayable_head->getPosition().y + (m_shadow_offset_head.y * sin(gWeather.GetDegree()))
					);
		}
	}
}//namespace logic

//Nadanie warto�ci sta�ym sk�adowum statycznym
float logic::CPhysical::m_increase		= 0.33f;	//wsp�czynnik wysoko�ci (wzrostu) obiektu
float logic::CPhysical::m_shadow_init	= 0.125f;	//wsp�czynnik przesuni�cia cienia obiektu (offset)
