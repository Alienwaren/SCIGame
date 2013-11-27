/*
 ___________________________________________
| CActorTemplate.cpp - implementacja klasy. |
| SCI - February 2013.                      |
|___________________________________________|

*/

#include "CActorTemplate.h"
#include "../Logic/Actor/CActor.h"
#include "../XML/CXml.h"
#include "../Rendering/Animations/CAnimSet.h"

using namespace rendering::animation;

namespace factory
{
	//Konstruktor
	CActorTemplate::CActorTemplate()
	:
		CPhysicalTemplate				(),//konstruktor klasy bazowej
		m_templ_energy					(0.0f),
		p_templ_animations				(NULL),
		m_templ_available_animations	(),
		m_templ_mass					(0.0f),
		m_templ_temperature				(0.0f),
		m_templ_speed					(0.0f),
		m_templ_movabled				(false)
	{
	}

	//Destruktor wirtualny
	CActorTemplate::~CActorTemplate()
	{
		m_templ_energy					= 0.0f;
		p_templ_animations				= NULL;
		//m_templ_available_animations	not edit
		m_templ_mass					= 0.0f;
		m_templ_temperature				= 0.0f;
		m_templ_speed					= 0.0f;
		m_templ_movabled				= false;
	}

	//Wirtualna metoda zwalniaj¹ca zasób - implementacje w klasach pochodnych
	void CActorTemplate::Drop()
	{
		delete this;
	}

	//Metoda ³aduj¹ca dane
	bool CActorTemplate::Load(const std::string &name)
	{
		CXml xml(name, "root" );
		return Load(xml);
	}

	//Wirtualna metoda ³aduj¹ca dane z xml ³aduje wspólne cechy CActor
	bool CActorTemplate::Load(CXml &xml)
	{
		//³adowanie danych klasy bazowej CPhysical
		if (!CPhysicalTemplate::Load(xml)) return false;

		//³adowanie wartoœci energii pocz¹tkowej obiektu
		if (xml_node<>*	node = xml.GetChild(xml.GetRootNode(), "unit_energy"))
		{
			m_templ_energy = xml.GetFloat(node, "energy");
		}

		//³adowanie zestawów animacji
		if (xml_node<>*	node = xml.GetChild(xml.GetRootNode(), "animset"))
		{
			for (xml_node<>* node = xml.GetChild(xml.GetRootNode(), "animset"); node; node = xml.GetSibling(node,"animset"))
			{
				CAnimSet * animations = new CAnimSet();
				animations->SetAnimSetName(xml.GetString(node, "name_animset"));
				animations->Parse(xml,node);
				m_templ_available_animations.push_back(animations);
			}
		}
		else
		{
			CAnimSet * animations = new CAnimSet();
			animations->Parse(xml);
			m_templ_available_animations.push_back(animations);
		}

		//jeœli zestaw animacji liczy wiêcej, ni¿ jedn¹ animacjê
		if (m_templ_available_animations.size() > 0)
			//ustawiam siê w zestawie na pierwsz¹ pod zerowym indeksem
			p_templ_animations = m_templ_available_animations[0];
		else
			p_templ_animations = NULL;

		//dane techniczne obiektu
		if (xml_node<> *node = xml.GetChild(xml.GetRootNode(), "technical_data"))
		{
			m_templ_mass = xml.GetFloat(node, "mass");
			m_templ_temperature = xml.GetFloat(node, "temperature");
			m_templ_speed = xml.GetFloat(node, "speed");
			m_templ_movabled = xml.GetBool(node, "movabled");
		}

		//wszystkie podklasy sprawdzaj¹, czy xml jest poprawny
		return true;
	}

	//Wirtualna metoda wype³niaj¹ca danymi obiekt klasy CActor
	void CActorTemplate::Fill(CActor *actor)
	{
		if(actor)
		{
			//ustawienie kompletnego wzorca
			actor->SetTemplate(this);

			//nazwa gatunku
			actor->SetGenre(m_templ_genre);

			//radius
			actor->SetBoundingCircle(m_templ_circle_radius);

			//rectangle size
			actor->SetBoundingRect(m_templ_rect_size);

			//konfiguracja obiektu - body, head, wygl¹d, cieñ, etc...
			actor->SetUseDisplayableBody(m_templ_use_displayable_body);
			actor->SetUseShadowBody(m_templ_use_shadow_body);
			actor->SetUseDisplayableHead(m_templ_use_displayable_head);
			actor->SetUseShadowHead(m_templ_use_shadow_head);

			//przekazanie zestawu animacji do obiektu, który jest wype³niany danymi wzorca
			if (p_templ_animations)
			{
				actor->SetAnimSet(p_templ_animations);    
				if (p_templ_animations->GetDefaultAnimBody()!= NULL)
					actor->SetAnimationBody(p_templ_animations->GetDefaultAnimBody());

				if (p_templ_animations->GetDefaultAnimHead()!= NULL)
					actor->SetAnimationHead(p_templ_animations->GetDefaultAnimHead());
			}

			//body scale
			actor->SetScaleBody(m_templ_scale_body, m_templ_scale_body);

			//head scale
			actor->SetScaleHead(m_templ_scale_head, m_templ_scale_head);

			//wartoœæ energi pocz¹tkowej obiektu
			actor->setEnergy(m_templ_energy);

			//dane techniczne obiektu
			actor->setMass(m_templ_mass);
			actor->setTemperature(m_templ_temperature);
			actor->setSpeed(m_templ_speed);
			actor->setIsMovabled(m_templ_movabled);
			actor->SetAltitude(m_templ_altitude);
		}
	}
} //namespace factory