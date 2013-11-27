/*
 ______________________________________________
| CPhysicalTemplate.h - definicja klasy.       |
| SCI - November 2012.                         |
|______________________________________________|

*/

#ifndef H_PHYSICAL_TEMPLATE_SCI
#define H_PHYSICAL_TEMPLATE_SCI

#include "../ResourceManager/IResource.h"
#include "../Logic/Physical/CPhysical.h"
#include "../XML/CXml.h"
#include <string>
#include <ostream>
#include <map>
#include <SFML/Graphics/Color.hpp>

///
///Forward declaration
///
namespace xml
{
	class CXml;
}

namespace logic
{
	class CActor;
}

using namespace resource;
using namespace xml;
using namespace logic;

namespace factory
{
	///
	///Klasa reprezentuje prawzorzec wszystkich wzorc�w
	///
	class CPhysicalTemplate : public IResource
	{

	public:
		
		///
		///Konstruktor
		///
		CPhysicalTemplate(void);

		///
		///Destruktor
		///
		virtual ~CPhysicalTemplate(void);

		///
		///Wirtualna metoda zwalniaj�ca zas�b
		///
		void Drop() = 0;

		///
		///Metoda �aduj�ca dane
		///
		///@param &name - sta�a referencja na std::string
		///
		bool Load(const std::string &name);

		///
		///Wirtualna metoda �aduj�ca dane z xml wywo�ywana przez implementacje klas potomnych
		///
		///@param &xml - referencja na obiekt klasy CXml
		///
		virtual bool Load(CXml &xml);

		///
		///Wirtualna metoda tworzenie obiekt�w pochodnych klasy CPhysical
		///
		///implementowana przez w pe�ni konkretne podklasy
		///
		///@param id - nazwa identyfikatora - obiekt klasy std::wstring
		///
		virtual CPhysical* Create(std::wstring id = L"") = 0 ;

		///
		///Wirtualna metoda wype�niaj�ca wskazany obiekt danymi tej klasy - zapowied� (CActor)
		///
		///@param *actor - wska�nik na obiekt klasy CActor
		///
		virtual void Fill(CActor *actor) {};

		///
		///Metoda zwraca nazw� pliku zasobu
		///
		inline const std::string& GetFilename() const { return m_templ_filename; }

		//metody pomocnicze - get

		inline std::wstring	GetGenre()				{ return m_templ_genre;					}
		inline float		GetCircleRadius()		{ return m_templ_circle_radius;			}
		inline float		GetAltitude()			{ return m_templ_altitude;				}
		inline bool			GetUseDisplayableBody() { return m_templ_use_displayable_body;	}
		inline bool			GetUseShadowBody()		{ return m_templ_use_shadow_body;		}
		inline bool			GetUseDisplayableHead() { return m_templ_use_displayable_head;	}
		inline bool			GetUseShadowHead()		{ return m_templ_use_shadow_head;		}
		inline float		GetScaleBody()			{ return m_templ_scale_body;			}
		inline float		GetScaleHead()			{ return m_templ_scale_head;			}
		inline std::string	GetAnimationNameBody()	{ return m_templ_animation_name_body;	}
		inline std::string	GetAnimationNameHead()	{ return m_templ_animation_name_head;	}

	protected:

		std::string		m_templ_filename;				//nazwa pliku xml
		std::string		m_templ_type;					//typ obiektu
		std::wstring	m_templ_genre;					//nazwa "gatunku" obiektu (np. robot, human, gun, etc.)
		
		float			m_templ_circle_radius;			//promie� detekcji kolizji
		sf::Vector2f	m_templ_rect_size;				//wektor przechowuj�cy rozmiar obszaru prostok�tnego
		float			m_templ_altitude;				//warto�� pu�apu obiektu wzgl�dem pod�o�a
		bool			m_templ_use_displayable_body;	//flaga okre�la, czy CPhysical posiada reprezentacj� graficzn� - body
		bool			m_templ_use_shadow_body;		//flaga okre�la, czy CPhysical posiada reprezentacj� graficzn� - body - cie�
		bool			m_templ_use_displayable_head;	//flaga okre�la, czy CPhysical posiada reprezentacj� graficzn� - head
		bool			m_templ_use_shadow_head;		//flaga okre�la, czy CPhysical posiada reprezentacj� graficzn� - head - cie�
		float			m_templ_scale_body;				//skala - body
		float			m_templ_scale_head;				//skala - body
		std::string		m_templ_animation_name_body;	//nazwa animacji cz�ci body
		std::string		m_templ_animation_name_head;	//nazwa animacji cz�ci head
														//animacje musz� by� zarejestrowane
														//w CAnimationManager
	private:

	};
}//namespace factory
#endif //H_PHYSICAL_TEMPLATE_SCI
