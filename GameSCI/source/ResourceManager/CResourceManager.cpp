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
	//Konstruktor domy�lny
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

	//Metody  � a d u j � c e  zasoby - implementacja

	//Metoda �aduje zas�b CTexture
	ResourceHandle CResourceManager::LoadTexture(const std::string& name)
	{
		fprintf(stderr, "CResourceManager::LoadTexture() %s\n", name.c_str());
		return LoadResource<CTexture>(name);
	}
	
	//Metoda �aduje zas�b CMusic
	ResourceHandle CResourceManager::LoadMusic(const std::string& name)
	{
		fprintf(stderr, "CResourceManager::LoadMusic() %s\n", name.c_str());
		return LoadResource<CMusic>(name);
	}

	//Metoda �aduje zas�b CSound
	ResourceHandle CResourceManager::LoadSound(const std::string& name)
	{
		fprintf(stderr, "CResourceManager::LoadSound() %s\n", name.c_str());
		return LoadResource<CSound>(name);
	}

	//Metoda �aduje zas�b CFont
	ResourceHandle CResourceManager::LoadFont(const std::string& name)
	{
		fprintf(stderr, "CResourceManager::LoadFont() %s\n", name.c_str());
		return LoadResource<CFont>(name);
	}

	//Metoda �aduje zas�b CPhysicalTemplate
	ResourceHandle CResourceManager::LoadPhysicalTemplate(const std::string& name)
	{
		fprintf(stderr, "CResourceManager::LoadPhysicalTemplate() %s\n", name.c_str());
		return LoadResource<CPhysicalTemplate>(name);
	}


	//Metody  z w r a c a j � c e  zasoby - implementacja

	//Metoda zwraca wska�nik na zas�b - obiekt klasy CTexture
	CTexture* CResourceManager::GetTexture(const std::string& name)
	{
		return (CTexture*)GetResource<CTexture>(name);
	}

	//Metoda zwraca wska�nik na zas�b - obiekt klasy CMusic
	CMusic* CResourceManager::GetMusic(const std::string& name)
	{
		return (CMusic*)GetResource<CMusic>(name);
	}

	//Metoda zwraca wska�nik na zas�b - obiekt klasy CSound
	CSound* CResourceManager::GetSound(const std::string& name)
	{
		return (CSound*)GetResource<CSound>(name);
	}

	//Metoda zwraca wska�nik na zas�b - obiekt klasy CFont
	CFont* CResourceManager::GetFont(const std::string& name)
	{
		return (CFont*)GetResource<CFont>(name);
	}

	//Metoda zwraca wska�nik na zas�b - obiekt klasy CPhysicalTemplate
	CPhysicalTemplate* CResourceManager::GetPhysicalTemplate(const std::string& name)
	{
		return (CPhysicalTemplate*)GetResource<CPhysicalTemplate>(name);
	}

	//Metoda usuwa zas�b na podstawie nazwy std::string
	void CResourceManager::DropResource(const std::string& name)
	{
		ResourceHandle handle = stringutils::GetStringHash(name);	//zamieniamy nazw� zasobu na uchwyt
		if(m_resources.count(handle) > 0)							//je�li w kontenerze s� obiekty
		{
			if(m_resources[handle] != NULL)							//je�li pod wskazanym uchwytem s� dane
				m_resources[handle]->Drop();						//niszczymy je (to co jest pod iteratorem)
			m_resources.erase(handle);								//i usuwamy z kontenera ten wspis
		}
	}

	//Metoda usuwa wszystkie zasoby
	void CResourceManager::Clear()
	{
		while(m_resources.size())						//dop�ki w kontenerze s� obiekty przeszukujemy kontener
		{
			if(m_resources.begin()->second)				//je�li pod pierwszym elementen s� dane
				m_resources.begin()->second->Drop();	//niszczymy je (to co jest pod iteratorem)
			m_resources.erase(m_resources.begin());		//i usuwamy z kontenera ten wspis
														//ponownie ustawiaj�c si� na pierwszy element kontenera
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

	//Szablon prywatnej metody zwracaj�cej wska�nik na zas�b na podstawie nazwy std::string
	template <typename T> T* CResourceManager::GetResource(const std::string& name)
	{
		ResourceHandle handle = stringutils::GetStringHash(name);	//zamieniamy nazw� na uchwyt
		if(m_resources.count(handle) > 0)							//je�li w kontenerze s� obiekty
			return (T*)m_resources[handle];							//zwracamy zas�b z kontenera pod tym kluczem
		else if(LoadResource<T>(name))								//w przeciwnym wypadku pr�bujemy za�adowa� zas�b
			return (T*)m_resources[handle];							//i po za�adowaniu zwr�ci�
		else														//w przeciwnym wypadku
			return (T*)NULL;										//zwracamy wska�nik na NULL
	}

	//Szablon prywatnej metody �aduj�cej zas�b
	template <typename T> ResourceHandle CResourceManager::LoadResource(const std::string& name)
	{
		ResourceHandle handle = InvalidResourceHandle;	//na wszelki wypadek zerujemy uchwyt
		handle = stringutils::GetStringHash(name);		//szyfrujemy funkcj� haszuj�c� std::string na liczb�

		IResource* resource = new T();					//Tworzymy nowy obiekt szablonu
														//poniewa� wska�niki *IResource
														//przechowujemy w kontenerze zasob�w.
														//Pami�taj, �e wska�nikiem na obiekt klasy
														//bazowej IResource, mo�emy tak�e pokazywa�
														//na obiekty klas potomnych, czyli
														//np. CTexture, CSound, CMusic,CFont
														//i ka�dy inny zas�b. kt�ry Resource Manager
														//mo�e produkowa�
														//Wa�ne:
														//Klasa taka musi dziedziczy� po klasie IResource,
														//a ta ma tylko wirtualny interface.
														//Zatem w klasach potomnych trzeba zaimplemntowa�
														//jako osobne metody:
														// virtual bool Load(const std::string &file_name) = 0;
														// virtual void Drop() = 0;

		if(resource->Load(name))						//pr�bujemy za�adowa� dane
		{
			m_resources[handle] = resource;				//je�li to si� powiedzie, wstawiamy do kontenera 
														//wska�nik na zas�b (value), pod klucz (key)
														//handle (uchwyt), wygenerowana liczba
														//za pomoc� funkcji hashuj�cej
			return handle;								//zwracamy zas�b, z kt�rego mo�na korzysta�
			
		}
		else											//je�li za�adowanie si� nie powiod�o
		{
			resource->Drop();							//niszczymy zas�b /patrz cia�o metody Drop()/
			return InvalidResourceHandle;				//zwracamy zero...
		}
	}

	//Szablon prywatnej metody �aduj�ce zasoby (wzorce danych dla obiekt�w gry)
	template <> ResourceHandle CResourceManager::LoadResource<CPhysicalTemplate>(const std::string& name)
	{
		//jestem...
		ResourceHandle handle = InvalidResourceHandle;	//na wszelki wypadek zerujemy uchwyt
		handle = stringutils::GetStringHash(name);		//szyfrujemy funkcj� haszuj�c� std::string na liczb�

		if(m_resources.count(handle) != 0)				//je�li w kontenerze ju� jest taki zas�b (wzorzec)
			return handle;								//nie ma potrzeby go tworzy� - zwracamy go

		CXml xml(name, "root" );						//tworzymy obiekt xml i otwieramy plik z damymi
		
		//z pliku xml odczytujemy typ wzorca, jaki mamy utworzy�,
		//na podstawie kt�rego wzorzec (zas�b), kt�ry zarejestrujemy
		//w kontenerze i na jego podstawie b�dzie mo�na tworzy� obiekty,
		//mi�dzy innyni takiego jak:
		//		- CPhysical,
		//		- CActor,
		//		- CEnemy,
		//		- CPlayer,
		//		- CBullet,
		//		- etc...
		//Jest to przede wszystkim szybsze, ni� pisanie w tych klasach metod
		//�adujacych dane.
		
		//Dlatego tworzymy klasy:
		//		- CPhysicalTemplate,
		//		- CActorTemplate,
		//		- CEnemyTemplate,
		//		- CPlayerTemplate,
		//		- CBulletTemplate,
		//		- etc...
		
		//Poza tym mo�emy za�adowa� do pami�ci, czyli do naszego CResourceManager
		//wzorce na obiekty ca�ego levelu.
		//Takie rozwi�zanie, wymusza jakby spos�b interpretacji
		//�adowanie danych - raz, na pocz�tku rozgrywki (tylko raz czekamy, a� danego si� za�aduj�)
		//Ma to zasadnicze znaczenie, szczeg�lnie, gdyby projektowa�
		//w technologiach web, mobilnych, telefony, etc...
		
		//pobieramy typ wzorca
		const std::string &type = xml.GetString(xml.GetRootNode(),"type");
		
		IResource *resource;	//tworzymy wska�nik na zas�b
		
	
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

		if(resource->Load(name))						//pr�bujemy za�adowa� dane
		{
			m_resources[handle] = resource;				//je�li to si� powiedzie, wstawiamy do kontenera 
														//wska�nik na zas�b w zale�no�ci
														//od typu odczytanego z pliku xml
			return handle;								//zwracamy zas�b, z kt�rego mo�na korzysta�
		}
		else											//je�li za�adowanie si� nie powiod�o
		{
			fprintf(stderr,"ERROR: Resource %s not found\n", name.c_str());
			resource->Drop();							//niszczymy zas�b /patrz cia�o metody Drop()/
			return InvalidResourceHandle;				//zwracamy zero...
		}
	}
}//namespace resource
