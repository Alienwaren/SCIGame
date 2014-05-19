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

	//Wirtualna metoda zwalniaj�ca zas�b
	void CFloraTemplate::Drop()
	{
		delete this;
	}

	//Metoda �aduj�ca dane
	bool CFloraTemplate::Load(const std::string &name)
	{
		CXml xml(name, "root" );
		return Load(xml);
	}

	//Wirtualna metoda �aduj�ca dane z xml �aduje cechy CMonster
	bool CFloraTemplate::Load(CXml &xml)
	{
//sprawdzamy, czy xml zawiera informacj�, �e jest to jaka� //ro�linno��
		if (xml.GetString(xml.GetRootNode(), "type") != "flora")
			return false;

		//sprawdzamy, czy mo�na za�adowa� dane z klasy bazowej
		if (!CActorTemplate::Load(xml))
			return false;

		//gdy w klasie CFlora byd� dodawane pola
		//to tutaj, w klasie jej fabryki,
		//nale�ay utworzy� takie same pola oraz je uwzgl�dni�

		return true;
	}

	//Metoda tworzy obiek klasy CFlora
	CFlora* CFloraTemplate::Create(std::wstring id)
	{
		CFlora* flora = gPhysicalManager.CreateFlora(id);
		Fill(flora);

		//gdy w klasie CFlora byd� dodawane pola
		//to tutaj, w klasie jej fabryki,
		//nale�ay utworzy� takie same pola oraz je uwzgl�dni�

		return flora;
	}

	//Wirtualna metoda wype�niaj�ca danymi obiekt klasy CFlora
	void CFloraTemplate::Fill(CFlora *flora)
	{
		CActorTemplate::Fill(flora);
		//ewentualnie reszta
	}
}//namespace factory
