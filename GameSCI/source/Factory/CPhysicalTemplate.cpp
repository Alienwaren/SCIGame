/*
 ______________________________________________
| CPhysicalTemplate.cpp - implementacja klasy. |
| SCI - November 2012.                         |
|______________________________________________|

*/

#include "CPhysicalTemplate.h"
#include "../ResourceManager/CResourceManager.h"
#include "../Logic/CPhysicalManager.h"
#include "../XML/CXml.h"
#include "../Utilities/StringUtils/StringUtils.h"
#include "../Rendering/Displayable/CDisplayable.h"

using namespace rapidxml;

namespace factory
{
	//Konstruktor
	CPhysicalTemplate::CPhysicalTemplate(void)
	:
		IResource						(),//konstruktor klasy bazowej
		m_templ_filename				(),
		m_templ_type					(),
		m_templ_genre					(),
		m_templ_circle_radius			(0.0f),
		m_templ_rect_size				(0.0f, 0.0f),
		m_templ_altitude				(1.0f),
		m_templ_use_displayable_body	(true),
		m_templ_use_shadow_body			(false),
		m_templ_use_displayable_head	(true),
		m_templ_use_shadow_head			(false),
		m_templ_scale_body				(1.0f),
		m_templ_scale_head				(1.0f),
		m_templ_animation_name_body		(""),
		m_templ_animation_name_head		("")
	{
	}

	//Destruktor
	CPhysicalTemplate::~CPhysicalTemplate(void)
	{
		//IResource						not edit
		m_templ_filename				= "";
		m_templ_type					= "";
		m_templ_genre					= L"";
		m_templ_circle_radius			= 0.0f;
		//m_templ_rect_size				not edit
		m_templ_altitude				= 0.0f;
		m_templ_use_displayable_body	= false;
		m_templ_use_shadow_body			= false;
		m_templ_use_displayable_head	= false;
		m_templ_use_shadow_head			= false;
		m_templ_scale_body				= 0.0f;
		m_templ_scale_head				= 0.0f;
		m_templ_animation_name_body		= "";
		m_templ_animation_name_head		= "";
	}

	//Metoda ³aduj¹ca dane
	bool CPhysicalTemplate::Load(const std::string &name)
	{
		CXml xml(name, "root");
		return Load(xml);
	}

	//Wirtualna metoda ³aduj¹ca dane z xml wywo³ywana przez implementacje klas potomnych
	bool CPhysicalTemplate::Load(CXml &xml)
	{
		//nazwa pliku xml
		m_templ_filename = xml.GetFilename();

		//typ obiektu
		if (xml_node<> *node = xml.GetRootNode())
			m_templ_type = xml.GetString(node, "type");

		//nazwa "gatunku" obiektu (np. robot, human, gun, etc.)
		if (xml_node<> *node = xml.GetChild(xml.GetRootNode(), "genre"))
			m_templ_genre = xml.GetWString(node, "genre");

		//zakres promienia detekcji kolizji
		if (xml_node<> *node = xml.GetChild(xml.GetRootNode(), "radius"))
		{
			m_templ_circle_radius = xml.GetFloat(node, "circle_radius");
		}

		//wektor przechowuj¹cy rozmiar obszaru prostok¹tnego
		if (xml_node<> *node = xml.GetChild(xml.GetRootNode(), "rect_size"))
		{
			m_templ_rect_size.x = xml.GetFloat(node, "rect_size_x");
			m_templ_rect_size.y = xml.GetFloat(node, "rect_size_y");
		}

		//skala obiektu (body and head)
		if (xml_node<> *node = xml.GetChild(xml.GetRootNode(), "scale"))
		{
			m_templ_scale_body = xml.GetFloat(node, "scale_body");
			m_templ_scale_head = xml.GetFloat(node, "scale_head");
		}

		//wartoœæ pu³apu obiektu wzglêdem pod³o¿a
		if (xml_node<> *node = xml.GetChild(xml.GetRootNode(), "altitude"))
		{
			m_templ_altitude = xml.GetFloat(node, "altitude");
		}

		//pola konfiguracyjne - potrzebne przy podejmowaniu decyzji - wygl¹d obiektu
		if (xml_node<> *node = xml.GetChild(xml.GetRootNode(), "physical_config"))
		{
			m_templ_use_displayable_body = xml.GetBool(node, "use_displayable_body");
			m_templ_use_shadow_body = xml.GetBool(node, "use_shadow_body");
			m_templ_use_displayable_head = xml.GetBool(node, "use_displayable_head");
			m_templ_use_shadow_head = xml.GetBool(node, "use_shadow_head");
		}

		//nazwy dla animacji (body i head) - (docelowo ³adowane s¹ ca³e zestawy - tu tylko do testów)
		if (xml_node<> *node = xml.GetChild(xml.GetRootNode(), "unit_animation"))
		{
			m_templ_animation_name_body = xml.GetString(node, "animation_body");
			m_templ_animation_name_head = xml.GetString(node, "animation_head");
		}

		//wszystkie podklasy sprawdzaj¹, czy xml jest poprawny
		return true;
	}
}//namespace factory
