/*
 ___________________________________________
| CEnemyTemplate.cpp - implementacja klasy. |
| Jack Flower May 2013.                     |
|___________________________________________|

*/

#include "CEnemyTemplate.h"
#include "../XML/CXml.h"
#include "../Logic/Actor/CActor.h"
#include "../Logic/CPhysicalManager.h"

namespace factory
{
	//Konstruktor
	CEnemyTemplate::CEnemyTemplate()
	:
		CActorTemplate()
	{
	} 

	//Destruktor wirtualny
	CEnemyTemplate::~CEnemyTemplate()
	{
		m_enemy_AI.clear();
	}

	//Wirtualna metoda zwalniaj�ca zas�b - implementacje w klasach pochodnych
	void CEnemyTemplate::Drop()
	{
		delete this;
	}

	//Metoda �aduj�ca dane
	bool CEnemyTemplate::Load(const std::string &name)
	{
		CXml xml(name, "root" );
		return Load(xml);
	}

	//Wirtualna metoda �aduj�ca dane z xml �aduje cechy CEnemy
	bool CEnemyTemplate::Load(CXml &xml)
	{
		//sprawdzamy, czy xml zawiera informacj�, �e jest enemy
		if (xml.GetString(xml.GetRootNode(), "type") != "enemy")
			return false;

		//sprawdzamy, czy mo�na za�adowa� dane z klasy bazowej
		if (!CActorTemplate::Load(xml))
			return false;

		//reszta, gdyby klasa CEnemy (jej wzorzec CEnemyTemplate)
		//mia�y jakie� pola do wczytania i przekazania...

		return true;
	}

	//Metoda tworzy obiek klasy CEnemy
	logic::CEnemy* CEnemyTemplate::Create(std::wstring id)
	{
		logic::CEnemy* enemy = gPhysicalManager.CreateEnemy(id);
		Fill(enemy);
		//gdyby by�y jakie� pola do przekazania, nale�y to uczyni�...
		return enemy;
	}
}//namespace factory