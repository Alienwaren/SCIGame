/*
 ___________________________________________
| CMapObjectType.cpp - implementacja klasy. |
| Jack Flower April 2013.                   |
| basic version for SCI April 2013.         |
|___________________________________________|

*/

#include "CMapObjectType.h"

namespace mapengine
{
	//Konstruktor
	CMapObjectType::CMapObjectType()
	:
		m_code	(""),
		p_template	(NULL)
	{
	}

	//Konstruktor kopiuj¹cy
CMapObjectType::CMapObjectType(const CMapObjectType& 
							CMapObjectTypeCopy)
	:
		m_code	(CMapObjectTypeCopy.m_code),
		p_template	(CMapObjectTypeCopy.p_template)
	{
	}

	//Destruktor
	CMapObjectType::~CMapObjectType()
	{	
		m_code	= "";
		p_template	= NULL;
	}
}//namespace mapengine
 

