#include "CFloraTemplate.h"



#include "CFloraTemplate.h"
#include "../XML/CXml.h"
#include "../Logic/CPhysicalManager.h"

namespace factory
{
	//Konstruktor
	CFloraTemplate::CFloraTemplate()
	:
		CActorTemplate()//konstruktor klasy bazowej
	{
	} 

	//Destruktor wirtualny
	CFloraTemplate::~CFloraTemplate()
	{
	}

	//Wirtualna metoda zwalniaj¹ca zasób
	void CFloraTemplate::Drop()
	{
		delete this;
	}

	//Metoda ³aduj¹ca dane
	bool CFloraTemplate::Load(const std::string &name)
	{
		CXml xml(name, "root" );
		return Load(xml);
	}

	//Wirtualna metoda ³aduj¹ca dane z xml ³aduje cechy CMonster
	bool CFloraTemplate::Load(CXml &xml)
	{
//sprawdzamy, czy xml zawiera informacjê, ¿e jest to jakaœ //roœlinnoœæ
		if (xml.GetString(xml.GetRootNode(), "type") != "flora")
			return false;

		//sprawdzamy, czy mo¿na za³adowaæ dane z klasy bazowej
		if (!CActorTemplate::Load(xml))
			return false;

		//gdy w klasie CFlora byd¹ dodawane pola
		//to tutaj, w klasie jej fabryki,
		//nale¿ay utworzyæ takie same pola oraz je uwzglêdniæ

		return true;
	}

	//Metoda tworzy obiek klasy CFlora
	CFlora* CFloraTemplate::Create(std::wstring id)
	{
		CFlora* flora = gPhysicalManager.CreateFlora(id);
		Fill(flora);

		//gdy w klasie CFlora byd¹ dodawane pola
		//to tutaj, w klasie jej fabryki,
		//nale¿ay utworzyæ takie same pola oraz je uwzglêdniæ

		return flora;
	}

	//Wirtualna metoda wype³niaj¹ca danymi obiekt klasy CFlora
	void CFloraTemplate::Fill(CFlora *flora)
	{
		CActorTemplate::Fill(flora);
		//ewentualnie reszta
	}
}//namespace factory
