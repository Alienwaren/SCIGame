/*
 ____________________________________________
| CPhysicalManager.cpp - implementacja klasy |
| SCI - November 2012.                       |
|____________________________________________|

*/

#include "CPhysicalManager.h"
#include "Physical/CPhysical.h"
#include "Actor/CActor.h"
#include "Enemy/CEnemy.h"
#include "Player/CPlayer.h"
#include "Bullet/CBullet.h"
#include "../Utilities/StringUtils/StringUtils.h"
#include "../Game/CGame.h"
#include "../Logic/Flora/CFlora.h"
#include <sstream>


template<> logic::CPhysicalManager* CSingleton<logic::CPhysicalManager>::m_singleton = 0;

using namespace game;

namespace logic
{
	//Konstruktor
	CPhysicalManager::CPhysicalManager()
	{
		fprintf(stderr, "CPhysicalManager::CPhysicalManager()\n");
		gGame.AddFrameListener(this);
	}

	//Destruktor wirtualny
	CPhysicalManager::~CPhysicalManager()
	{
		fprintf(stderr, "CPhysicalManager::~CPhysicalManager()\n");
		Clear(true);
	}

	//Wirtualna metoda - czyœci obiekty z kontenera
	void CPhysicalManager::FrameStarted(float secondsPassed)
	{
		//Czyszczenie obiektów
		std::vector<CPhysical*>				dirty;		//kontener na obiekty do zniszczenia
		std::vector<CPhysical*>::iterator	it;			//iterator tego kontenera

		for (it = m_physicals.begin() ; it != m_physicals.end() ; it++)
		{
			if ((*it)->m_ready_for_destruction)			//jeœli obiekt jest gotowy do zniszczaenia
				dirty.push_back(*it);					//wstawiamy go do kontenera "œmierci"
		}

		for (unsigned int i = 0; i < dirty.size(); i++)	//iterujemy po tym kontenerze
			DestroyPhysical(dirty[i]);					//i usuwamy obiekty
	}

	//Szablon metody tworzenia obiektów
	template<class T>
	T* CPhysicalManager::Create(const std::wstring &uniqueId)
	{
		std::wstring new_unique_id = uniqueId;
		if (uniqueId != L"")
		{
			CheckUniqueId(new_unique_id);

			if (m_named_physicals.find(new_unique_id) != m_named_physicals.end())
			{
				fprintf(stderr, "PhysicalsManager::Create<T> - %ls key already in m_named_physicals map", new_unique_id.c_str());
				return NULL;
			}

			m_named_physicals[new_unique_id] = NULL; // zarezerwowanie nazwy przed utworzeniem obiektu
		}

		T* obj = new T(new_unique_id);
		obj->m_physical_manager_index = (int)m_physicals.size();
		m_physicals.push_back(obj);
		if (uniqueId != L"")
			m_named_physicals[new_unique_id] = obj;
		return obj;
	}

	//Metoda tworzy obiekt klasy CPhysical i zwaraca wskaŸnik na ten obiekt
	logic::CPhysical *CPhysicalManager::CreatePhysical(const std::wstring& unique_id)
	{
		fprintf(stderr, "CPhysical created\n");
		return Create<logic::CPhysical>(unique_id);
	}

	//Metoda tworzy obiekt klasy CActor i zwaraca wskaŸnik na ten obiekt
	logic::CActor *CPhysicalManager::CreateActor(const std::wstring &uniqueId)
	{
		return Create<logic::CActor>(uniqueId);
		fprintf(stderr, "CActor created\n");
	}

	//Metoda tworzy obiekt klasy CEnemy i zwaraca wskaŸnik na ten obiekt
	logic::CEnemy *CPhysicalManager::CreateEnemy(const std::wstring &uniqueId)
	{
		return Create<logic::CEnemy>(uniqueId);
		fprintf(stderr, "CEnemy created\n");
	}

	//Metoda tworzy obiekt klasy CPlayer i zwaraca wskaŸnik na ten obiekt
	logic::CPlayer *CPhysicalManager::CreatePlayer( const std::wstring &uniqueId)
	{
		return Create<logic::CPlayer>(uniqueId);
		fprintf(stderr, "CPlayer created\n");
	}

	//Metoda tworzy obiekt klasy CBullet i zwaraca wskaŸnik na ten obiekt
	logic::CBullet *CPhysicalManager::CreateBullet( const std::wstring &uniqueId)
	{
		return Create<logic::CBullet>(uniqueId);
		fprintf(stderr, "CBullet created\n");
	}

	//Metoda usuwa obiekt klasy CPhysical z kontenera
	void CPhysicalManager::DestroyPhysical(logic::CPhysical* physical)
	{
		if (physical->m_physical_manager_index >= 0)
		{
			m_physicals[physical->m_physical_manager_index] = m_physicals[m_physicals.size()-1];
			m_physicals[physical->m_physical_manager_index]->m_physical_manager_index = physical->m_physical_manager_index;
			m_physicals.pop_back();
			physical->m_physical_manager_index = -1;
			DestroyPhysical(physical->GetUniqueId());
			delete physical;
		}
	}

	//Metoda usuwa obiekt klasy CPhysical z kontenera
	void CPhysicalManager::DestroyPhysical(const std::wstring& id_physical)
	{
		if (m_named_physicals.find(id_physical) != m_named_physicals.end())
		{
			CPhysical* physical = m_named_physicals[id_physical];
			m_named_physicals.erase(m_named_physicals.find( id_physical));
			DestroyPhysical(physical);
		}
	}

	//Metoda usuwa wszystkie obiekty z kontenera
	void CPhysicalManager::Clear(bool force_destroy_instantly)
	{
		std::vector<CPhysical*>::iterator it;

		for (it = m_physicals.begin(); it != m_physicals.end(); it++)
		{
			(*it)->MarkForDelete();
		}

		if (force_destroy_instantly)
		{
			FrameStarted(0.0f);
		}
	}

	//Metoda zwraca sta³¹ referencjê do kontenera z nazwami wszystkich zarejestorwanych obiektów CPhysical
	const std::map<std::wstring, logic::CPhysical*>& CPhysicalManager::GetNamedPhysicals()
	{
		return m_named_physicals;
	}

	//Metoda zwraca sta³¹ referencjê do kontenera z wszystkimi wskaŸnikami zarejestorwanych obiektów CPhysical
	const std::vector<logic::CPhysical *> &CPhysicalManager::GetPhysicals()
	{
		return m_physicals;
	}

	//Metoda zwraca wskaŸnik na obiekt klasy CPhysical z kontenera na podstawie identyfikatora
	logic::CPhysical* CPhysicalManager::GetPhysicalById(const std::wstring& physical_id)
	{
		if (m_named_physicals.find(physical_id) != m_named_physicals.end())
			return m_named_physicals[physical_id];
		else
		{
			fprintf(stderr, "PhysicalsManager::GetPhysicalById - %ls key not found in m_named_physicals map", physical_id.c_str());
			return NULL;
		}
	}

	//Prywatna metoda sprawdzaj¹ca jaki identyfikator nadaæ obiektowi przy utworzeniu
	void CPhysicalManager::CheckUniqueId(std::wstring& new_unique_id)
	{
		static long physicalCount = 0;
		//jeœli identyfikator jest ci¹giem pustych znaków
		//lub w kontenerze s¹ ju¿ jakieœ nazwy
		if ((new_unique_id == L"" ) || (m_named_physicals.count(new_unique_id) > 0))
			do
			{
				//to tworzymy nazwê zsyntetyzowan¹
				//do s³owa "physical" do dajemy wartoœæ licznika zamienion¹ na string
				new_unique_id = L"physical" + stringutils::ToWString(physicalCount++);
			}
			while (m_named_physicals.find(new_unique_id) != m_named_physicals.end());
	}
}//namespace logic
