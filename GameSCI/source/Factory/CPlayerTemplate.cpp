/*
 ____________________________________________
| CPlayerTemplate.cpp - implementacja klasy. |
| Jack Flower May 2013.                      |
|____________________________________________|

*/

#include "CPlayerTemplate.h"
#include "../XML/CXml.h"
#include "../Logic/CPhysicalManager.h"

namespace factory
{
	//Konstruktor
	CPlayerTemplate::CPlayerTemplate()
	:
		CActorTemplate()
	{
	} 

	//Destruktor wirtualny
	CPlayerTemplate::~CPlayerTemplate()
	{
		m_player_AI.clear();
	}

	//Wirtualna metoda zwalniaj�ca zas�b - implementacje w klasach pochodnych
	void CPlayerTemplate::Drop()
	{
		delete this;
	}

	//Metoda �aduj�ca dane
	bool CPlayerTemplate::Load(const std::string &name)
	{
		CXml xml(name, "root" );
		return Load(xml);
	}

	//Wirtualna metoda �aduj�ca dane z xml �aduje cechy CPlayer
	bool CPlayerTemplate::Load(CXml &xml)
	{
		//sprawdzamy, czy xml zawiera informacj�, �e jest player
		if (xml.GetString(xml.GetRootNode(), "type") != "player")
			return false;

		//sprawdzamy, czy mo�na za�adowa� dane z klasy bazowej
		if (!CActorTemplate::Load(xml))
			return false;

		//reszta, gdyby klasa CPlayer (jej wzorzec CPlayerTemplate)
		//mia�y jakie� pola do wczytania i przekazania...

		return true;
	}

	//Metoda tworzy obiek klasy CPlayer
	logic::CPlayer* CPlayerTemplate::Create(std::wstring id)
	{
		logic::CPlayer* player = gPhysicalManager.CreatePlayer(id);
		Fill(player);
		//gdyby by�y jakie� pola do przekazania, nale�y to uczyni�...
		return player;
	}
}//namespace factory
