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
	///Klasa reprezentuje prawzorzec wszystkich wzorców
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
		///Wirtualna metoda zwalniaj¹ca zasób
		///
		void Drop() = 0;

		///
		///Metoda ³aduj¹ca dane
		///
		///@param &name - sta³a referencja na std::string
		///
		bool Load(const std::string &name);

		///
		///Wirtualna metoda ³aduj¹ca dane z xml wywo³ywana przez implementacje klas potomnych
		///
		///@param &xml - referencja na obiekt klasy CXml
		///
		virtual bool Load(CXml &xml);

		///
		///Wirtualna metoda tworzenie obiektów pochodnych klasy CPhysical
		///
		///implementowana przez w pe³ni konkretne podklasy
		///
		///@param id - nazwa identyfikatora - obiekt klasy std::wstring
		///
		virtual CPhysical* Create(std::wstring id = L"") = 0 ;

		///
		///Wirtualna metoda wype³niaj¹ca wskazany obiekt danymi tej klasy - zapowiedŸ (CActor)
		///
		///@param *actor - wskaŸnik na obiekt klasy CActor
		///
		virtual void Fill(CActor *actor) {};

		///
		///Metoda zwraca nazwê pliku zasobu
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
		
		float			m_templ_circle_radius;			//promieñ detekcji kolizji
		sf::Vector2f	m_templ_rect_size;				//wektor przechowuj¹cy rozmiar obszaru prostok¹tnego
		float			m_templ_altitude;				//wartoœæ pu³apu obiektu wzglêdem pod³o¿a
		bool			m_templ_use_displayable_body;	//flaga okreœla, czy CPhysical posiada reprezentacjê graficzn¹ - body
		bool			m_templ_use_shadow_body;		//flaga okreœla, czy CPhysical posiada reprezentacjê graficzn¹ - body - cieñ
		bool			m_templ_use_displayable_head;	//flaga okreœla, czy CPhysical posiada reprezentacjê graficzn¹ - head
		bool			m_templ_use_shadow_head;		//flaga okreœla, czy CPhysical posiada reprezentacjê graficzn¹ - head - cieñ
		float			m_templ_scale_body;				//skala - body
		float			m_templ_scale_head;				//skala - body
		std::string		m_templ_animation_name_body;	//nazwa animacji czêœci body
		std::string		m_templ_animation_name_head;	//nazwa animacji czêœci head
														//animacje musz¹ byæ zarejestrowane
														//w CAnimationManager
	private:

	};
}//namespace factory
#endif //H_PHYSICAL_TEMPLATE_SCI
