/*
 _____________________________________________
| CResourceManager.cpp - implementacja klasy. |
| SCI - September 2012.                       |
|_____________________________________________|

*/

#include "CResourceManager.h"
#include "../Utilities/StringUtils/StringUtils.h"

#include "CTexture.h"
#include "CMusic.h"
#include "CSound.h"
#include "CFont.h"
#include "../XML/CXml.h"
#include "../Factory/CPhysicalTemplate.h"
#include "../Factory/CActorTemplate.h"
#include "../Factory/CEnemyTemplate.h"
#include "../Factory/CPlayerTemplate.h"
#include "../Factory/CBulletTemplate.h"

template<> resource::CResourceManager* CSingleton<resource::CResourceManager>::m_singleton = 0;

namespace resource
{
	//Konstruktor domyœlny
	CResourceManager::CResourceManager()
	{
		fprintf(stderr, "CResourceManager::CResourceManager()\n");
	}

	//Destruktor wirtualny
	CResourceManager::~CResourceManager()
	{
		fprintf(stderr, "CResourceManager::~CResourceManager()\n");
		Clear();//usuwamy wszystkie zasoby z kontenera
	}

	//Metody  ³ a d u j ¹ c e  zasoby - implementacja

	//Metoda ³aduje zasób CTexture
	ResourceHandle CResourceManager::LoadTexture(const std::string& name)
	{
		fprintf(stderr, "CResourceManager::LoadTexture() %s\n", name.c_str());
		return LoadResource<CTexture>(name);
	}
	
	//Metoda ³aduje zasób CMusic
	ResourceHandle CResourceManager::LoadMusic(const std::string& name)
	{
		fprintf(stderr, "CResourceManager::LoadMusic() %s\n", name.c_str());
		return LoadResource<CMusic>(name);
	}

	//Metoda ³aduje zasób CSound
	ResourceHandle CResourceManager::LoadSound(const std::string& name)
	{
		fprintf(stderr, "CResourceManager::LoadSound() %s\n", name.c_str());
		return LoadResource<CSound>(name);
	}

	//Metoda ³aduje zasób CFont
	ResourceHandle CResourceManager::LoadFont(const std::string& name)
	{
		fprintf(stderr, "CResourceManager::LoadFont() %s\n", name.c_str());
		return LoadResource<CFont>(name);
	}

	//Metoda ³aduje zasób CPhysicalTemplate
	ResourceHandle CResourceManager::LoadPhysicalTemplate(const std::string& name)
	{
		fprintf(stderr, "CResourceManager::LoadPhysicalTemplate() %s\n", name.c_str());
		return LoadResource<CPhysicalTemplate>(name);
	}


	//Metody  z w r a c a j ¹ c e  zasoby - implementacja

	//Metoda zwraca wskaŸnik na zasób - obiekt klasy CTexture
	CTexture* CResourceManager::GetTexture(const std::string& name)
	{
		return (CTexture*)GetResource<CTexture>(name);
	}

	//Metoda zwraca wskaŸnik na zasób - obiekt klasy CMusic
	CMusic* CResourceManager::GetMusic(const std::string& name)
	{
		return (CMusic*)GetResource<CMusic>(name);
	}

	//Metoda zwraca wskaŸnik na zasób - obiekt klasy CSound
	CSound* CResourceManager::GetSound(const std::string& name)
	{
		return (CSound*)GetResource<CSound>(name);
	}

	//Metoda zwraca wskaŸnik na zasób - obiekt klasy CFont
	CFont* CResourceManager::GetFont(const std::string& name)
	{
		return (CFont*)GetResource<CFont>(name);
	}

	//Metoda zwraca wskaŸnik na zasób - obiekt klasy CPhysicalTemplate
	CPhysicalTemplate* CResourceManager::GetPhysicalTemplate(const std::string& name)
	{
		return (CPhysicalTemplate*)GetResource<CPhysicalTemplate>(name);
	}

	//Metoda usuwa zasób na podstawie nazwy std::string
	void CResourceManager::DropResource(const std::string& name)
	{
		ResourceHandle handle = stringutils::GetStringHash(name);	//zamieniamy nazwê zasobu na uchwyt
		if(m_resources.count(handle) > 0)							//jeœli w kontenerze s¹ obiekty
		{
			if(m_resources[handle] != NULL)							//jeœli pod wskazanym uchwytem s¹ dane
				m_resources[handle]->Drop();						//niszczymy je (to co jest pod iteratorem)
			m_resources.erase(handle);								//i usuwamy z kontenera ten wspis
		}
	}

	//Metoda usuwa wszystkie zasoby
	void CResourceManager::Clear()
	{
		while(m_resources.size())						//dopóki w kontenerze s¹ obiekty przeszukujemy kontener
		{
			if(m_resources.begin()->second)				//jeœli pod pierwszym elementen s¹ dane
				m_resources.begin()->second->Drop();	//niszczymy je (to co jest pod iteratorem)
			m_resources.erase(m_resources.begin());		//i usuwamy z kontenera ten wspis
														//ponownie ustawiaj¹c siê na pierwszy element kontenera
		}
		fprintf(stderr, "CResourceManager::Clear()\n");
	}

	///
	///Wirtualny interfejs - implementacja
	///
	void CResourceManager::Cleanup()
	{
		Clear();
	}

	//Szablon prywatnej metody zwracaj¹cej wskaŸnik na zasób na podstawie nazwy std::string
	template <typename T> T* CResourceManager::GetResource(const std::string& name)
	{
		ResourceHandle handle = stringutils::GetStringHash(name);	//zamieniamy nazwê na uchwyt
		if(m_resources.count(handle) > 0)							//jeœli w kontenerze s¹ obiekty
			return (T*)m_resources[handle];							//zwracamy zasób z kontenera pod tym kluczem
		else if(LoadResource<T>(name))								//w przeciwnym wypadku próbujemy za³adowaæ zasób
			return (T*)m_resources[handle];							//i po za³adowaniu zwróciæ
		else														//w przeciwnym wypadku
			return (T*)NULL;										//zwracamy wskaŸnik na NULL
	}

	//Szablon prywatnej metody ³aduj¹cej zasób
	template <typename T> ResourceHandle CResourceManager::LoadResource(const std::string& name)
	{
		ResourceHandle handle = InvalidResourceHandle;	//na wszelki wypadek zerujemy uchwyt
		handle = stringutils::GetStringHash(name);		//szyfrujemy funkcj¹ haszuj¹c¹ std::string na liczbê

		IResource* resource = new T();					//Tworzymy nowy obiekt szablonu
														//poniewa¿ wskaŸniki *IResource
														//przechowujemy w kontenerze zasobów.
														//Pamiêtaj, ¿e wskaŸnikiem na obiekt klasy
														//bazowej IResource, mo¿emy tak¿e pokazywaæ
														//na obiekty klas potomnych, czyli
														//np. CTexture, CSound, CMusic,CFont
														//i ka¿dy inny zasób. który Resource Manager
														//mo¿e produkowaæ
														//Wa¿ne:
														//Klasa taka musi dziedziczyæ po klasie IResource,
														//a ta ma tylko wirtualny interface.
														//Zatem w klasach potomnych trzeba zaimplemntowaæ
														//jako osobne metody:
														// virtual bool Load(const std::string &file_name) = 0;
														// virtual void Drop() = 0;

		if(resource->Load(name))						//próbujemy za³adowaæ dane
		{
			m_resources[handle] = resource;				//jeœli to siê powiedzie, wstawiamy do kontenera 
														//wskaŸnik na zasób (value), pod klucz (key)
														//handle (uchwyt), wygenerowana liczba
														//za pomoc¹ funkcji hashuj¹cej
			return handle;								//zwracamy zasób, z którego mo¿na korzystaæ
			
		}
		else											//jeœli za³adowanie siê nie powiod³o
		{
			resource->Drop();							//niszczymy zasób /patrz cia³o metody Drop()/
			return InvalidResourceHandle;				//zwracamy zero...
		}
	}

	//Szablon prywatnej metody ³aduj¹ce zasoby (wzorce danych dla obiektów gry)
	template <> ResourceHandle CResourceManager::LoadResource<CPhysicalTemplate>(const std::string& name)
	{
		//jestem...
		ResourceHandle handle = InvalidResourceHandle;	//na wszelki wypadek zerujemy uchwyt
		handle = stringutils::GetStringHash(name);		//szyfrujemy funkcj¹ haszuj¹c¹ std::string na liczbê

		if(m_resources.count(handle) != 0)				//jeœli w kontenerze ju¿ jest taki zasób (wzorzec)
			return handle;								//nie ma potrzeby go tworzyæ - zwracamy go

		CXml xml(name, "root" );						//tworzymy obiekt xml i otwieramy plik z damymi
		
		//z pliku xml odczytujemy typ wzorca, jaki mamy utworzyæ,
		//na podstawie którego wzorzec (zasób), który zarejestrujemy
		//w kontenerze i na jego podstawie bêdzie mo¿na tworzyæ obiekty,
		//miêdzy innyni takiego jak:
		//		- CPhysical,
		//		- CActor,
		//		- CEnemy,
		//		- CPlayer,
		//		- CBullet,
		//		- etc...
		//Jest to przede wszystkim szybsze, ni¿ pisanie w tych klasach metod
		//³adujacych dane.
		
		//Dlatego tworzymy klasy:
		//		- CPhysicalTemplate,
		//		- CActorTemplate,
		//		- CEnemyTemplate,
		//		- CPlayerTemplate,
		//		- CBulletTemplate,
		//		- etc...
		
		//Poza tym mo¿emy za³adowaæ do pamiêci, czyli do naszego CResourceManager
		//wzorce na obiekty ca³ego levelu.
		//Takie rozwi¹zanie, wymusza jakby sposób interpretacji
		//³adowanie danych - raz, na pocz¹tku rozgrywki (tylko raz czekamy, a¿ danego siê za³aduj¹)
		//Ma to zasadnicze znaczenie, szczególnie, gdyby projektowaæ
		//w technologiach web, mobilnych, telefony, etc...
		
		//pobieramy typ wzorca
		const std::string &type = xml.GetString(xml.GetRootNode(),"type");
		
		IResource *resource;	//tworzymy wskaŸnik na zasób
		
	
		if (type == "enemy")
			resource = new CEnemyTemplate();
		else if(type == "player")
			resource = new CPlayerTemplate();
		else if(type == "bullet")
			resource = new CBulletTemplate();
		//else if(type == "xxx")
		//	resource = new CXXXTemplate();
		else
			return InvalidResourceHandle;

		if(resource->Load(name))						//próbujemy za³adowaæ dane
		{
			m_resources[handle] = resource;				//jeœli to siê powiedzie, wstawiamy do kontenera 
														//wskaŸnik na zasób w zale¿noœci
														//od typu odczytanego z pliku xml
			return handle;								//zwracamy zasób, z którego mo¿na korzystaæ
		}
		else											//jeœli za³adowanie siê nie powiod³o
		{
			fprintf(stderr,"ERROR: Resource %s not found\n", name.c_str());
			resource->Drop();							//niszczymy zasób /patrz cia³o metody Drop()/
			return InvalidResourceHandle;				//zwracamy zero...
		}
	}
}//namespace resource
