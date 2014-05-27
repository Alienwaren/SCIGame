/*
 _________________________________________________
| CMapObjectDescriptor.cpp - implementacja klasy. |
| Jack Flower April 2013.                         |
| basic version for SCI April 2013.               |
|_________________________________________________|

*/

#include "CMapObjectDescriptor.h"
#include "../Factory/CPhysicalTemplate.h"
#include "../Utilities/StringUtils/StringUtils.h"

namespace mapengine
{
	//Konstruktor
	CMapObjectDescriptor::CMapObjectDescriptor()
	:
		m_code			(""),
		m_name			(""),
		p_templ			(NULL),
		m_x_position		(0.0f),
		m_y_position		(0.0f),
		m_rotation_body		(0),
		m_rotation_head		(0),
		m_uniqueId			(0),
		m_smooth			(false)
	{
		m_uniqueId = nextId++;	//unikalna wartoœæ identyfikatora 
						//zwiêkszana w konstruktorze
	}
	
	//Konstruktor kopiuj¹cy
	CMapObjectDescriptor::CMapObjectDescriptor(const 
				CMapObjectDescriptor& CMapObjectDescriptorCopy)
	:
		m_code		(CMapObjectDescriptorCopy.m_code),
		m_name		(CMapObjectDescriptorCopy.m_name),
		p_templ		(CMapObjectDescriptorCopy.p_templ),
		m_x_position	(CMapObjectDescriptorCopy.m_x_position),
		m_y_position	(CMapObjectDescriptorCopy.m_y_position),
		m_rotation_body	(CMapObjectDescriptorCopy.m_rotation_body),
		m_rotation_head	(CMapObjectDescriptorCopy.m_rotation_head),
		m_uniqueId		(CMapObjectDescriptorCopy.m_uniqueId),
		m_smooth		(CMapObjectDescriptorCopy.m_smooth)
	{
	}

 
	//Destruktor
	CMapObjectDescriptor::~CMapObjectDescriptor()
	{
		m_code			= "";
		m_name			= "";
		p_templ			= NULL;
		m_x_position		= 0.0f;
		m_y_position		= 0.0f;
		m_rotation_body		= 0;
		m_rotation_head		= 0;
		m_uniqueId			= 0;
		m_smooth			= false;
	}

	//Metoda tworzy obiekt mapy
	void CMapObjectDescriptor::Create()
	{
		CPhysical *phys = 
p_templ->Create(stringutils::ConvertToWString(m_name));
		if (phys != 0)
		{
			phys->SetPosition
(
sf::Vector2f(m_x_position, m_y_position)
);
			phys->SetRotationBody(m_rotation_body);
			phys->SetRotationHead(m_rotation_head);
			phys->setSmoothing(m_smooth);
		}
	}

	//Nadanie wartoœci sta³ym sk³adowum statycznym
	int CMapObjectDescriptor::nextId = 1;
}//namespace mapengine
