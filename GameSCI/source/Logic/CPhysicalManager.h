/*
 ____________________________________________
| CPhysicalManager.h - definicja klasy       |
| SCI - November 2012.                       |
|____________________________________________|

*/

#ifndef H_PHYSICAL_MANAGER_SCI
#define H_PHYSICAL_MANAGER_SCI

#include "../Utilities/Singleton/CSingleton.h"
#include "../Game/Listener/IFrameListener.h"
#include <string>
#include <map>

#define gPhysicalManager logic::CPhysicalManager::GetSingleton()

///
///Forward declaration
///
namespace logic
{
	class CPhysical;
	class CActor;
	class CEnemy;
	class CPlayer;
	class CBullet;
	class CFlora;
}
//fabryka mo�e produkowa� obiekty wy�ej wymienionych klasy

using namespace listener;

namespace logic
{
	///
	///Klasa reprezentuje fabryk� produkuj�c� obiekty gry i zarz�dzanie obiektami
	///
	class CPhysicalManager : public CSingleton<CPhysicalManager>, public IFrameListener
	{
	public:

		///
		///Konstruktor
		///
		CPhysicalManager();

		///
		///Destruktor wirtualny
		///
		virtual ~CPhysicalManager();

		///
		///Wirtualna metoda - czy�ci obiekty z kontenera
		///
		///@param secondsPassed - up�ywaj�cy czas
		///
		virtual void FrameStarted(float secondsPassed);
		
		///
		///Metoda tworzy obiekt klasy CPhysical i zwaraca wska�nik na ten obiekt
		///
		///@param &uniqueId - unikalny identyfikator - sta�a referencja na obiekt klasy std::wstring
		///
		logic::CPhysical* CreatePhysical(const std::wstring& unique_id = L"");

		///
		///Metoda tworzy obiekt klasy CActor i zwaraca wska�nik na ten obiekt
		///
		///@param &uniqueId - unikalny identyfikator - sta�a referencja na obiekt klasy std::wstring
		///
		logic::CActor *CreateActor(const std::wstring &uniqueId = L"");

		///
		///Metoda tworzy obiekt klasy CEnemy i zwaraca wska�nik na ten obiekt
		///
		///@param &uniqueId - unikalny identyfikator - sta�a referencja na obiekt klasy std::wstring
		///
		logic::CEnemy *CreateEnemy(const std::wstring &uniqueId = L"");
		///
		///Tworzymy obiekty Flory i zwracamy wska�niki na ten obiekt
		///
		///@param &uniqueId - unikalny identyfikator
		logic::CFlora *CreateFlora(const std::wstring &uniqueId = L"");
		///
		///Metoda tworzy obiekt klasy CPlayer i zwaraca wska�nik na ten obiekt
		///
		///@param &uniqueId - unikalny identyfikator - sta�a referencja na obiekt klasy std::wstring
		///
		logic::CPlayer *CreatePlayer( const std::wstring &uniqueId = L"");

		///
		///Metoda tworzy obiekt klasy CBullet i zwaraca wska�nik na ten obiekt
		///
		///@param &uniqueId - unikalny identyfikator - sta�a referencja na obiekt klasy std::wstring
		///
		logic::CBullet *CreateBullet( const std::wstring &uniqueId = L"");

		///
		///Metoda usuwa obiekt klasy CPhysical z kontenera
		///
		///@param *physical - wska�nik na obiekt klasy CPhysical
		///
		void DestroyPhysical(logic::CPhysical* physical);
	    
		///
		///Metoda usuwa obiekt klasy CPhysical z kontenera
		///
		///@param &id_physical - sta�a referencja na obiekt klasy std::wstring - unikalny identyfikator obiektu
		///
		void DestroyPhysical(const std::wstring& id_physical);

		///
		///Metoda usuwa wszystkie obiekty z kontenera
		///
		///@param force_destroy_instantly - flaga, czy usun�� z kontenera wszystkie obiekty
		///
		void Clear(bool force_destroy_instantly = false);

		///
		///Metoda zwraca sta�a referencj� do kontenera z nazwami wszystkich zarejestorwanych obiekt�w CPhysical
		///
		const std::map<std::wstring, logic::CPhysical*>& GetNamedPhysicals();

		///
		///Metoda zwraca sta�a referencj� do kontenera z wszystkimi wska�nikami zarejestorwanych obiekt�w CPhysical
		///
		const std::vector<logic::CPhysical*>& GetPhysicals();

		///
		///Metoda zwraca wska�nik na obiekt klasy CPhysical z kontenera na podstawie identyfikatora
		///
		///@param &physical_id - sta�a referencja na obiekt klasy std::wstring
		///
		logic::CPhysical* GetPhysicalById(const std::wstring& physical_id);

	private:
		
		//
		//Szablon metody tworzenia obiekt�w
		//
		template<class T> T* Create(const std::wstring &uniqueId);
	    
		std::map<std::wstring, logic::CPhysical*>		m_named_physicals;	//kontener <map> na nazwy obiekt�w CPhysical
		std::vector<logic::CPhysical*>					m_physicals;		//kontener <vector> na wska�niki na obiekty klasy CPhysical
	    
		//
		//Prywatna metoda sprawdzaj�ca jaki identyfikator nada� obiektowi przy utworzeniu
		//
		//@param &new_unique_id - referencja na obiekt klasy std::wstring
		//
		void CheckUniqueId(std::wstring& new_unique_id);
	};
}//namespace logic
#endif//H_PHYSICAL_MANAGER_SCI
