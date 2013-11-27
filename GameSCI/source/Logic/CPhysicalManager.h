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
}
//fabryka mo¿e produkowaæ obiekty wy¿ej wymienionych klasy

using namespace listener;

namespace logic
{
	///
	///Klasa reprezentuje fabrykê produkuj¹c¹ obiekty gry i zarz¹dzanie obiektami
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
		///Wirtualna metoda - czyœci obiekty z kontenera
		///
		///@param secondsPassed - up³ywaj¹cy czas
		///
		virtual void FrameStarted(float secondsPassed);
		
		///
		///Metoda tworzy obiekt klasy CPhysical i zwaraca wskaŸnik na ten obiekt
		///
		///@param &uniqueId - unikalny identyfikator - sta³a referencja na obiekt klasy std::wstring
		///
		logic::CPhysical* CreatePhysical(const std::wstring& unique_id = L"");

		///
		///Metoda tworzy obiekt klasy CActor i zwaraca wskaŸnik na ten obiekt
		///
		///@param &uniqueId - unikalny identyfikator - sta³a referencja na obiekt klasy std::wstring
		///
		logic::CActor *CreateActor(const std::wstring &uniqueId = L"");

		///
		///Metoda tworzy obiekt klasy CEnemy i zwaraca wskaŸnik na ten obiekt
		///
		///@param &uniqueId - unikalny identyfikator - sta³a referencja na obiekt klasy std::wstring
		///
		logic::CEnemy *CreateEnemy(const std::wstring &uniqueId = L"");

		///
		///Metoda tworzy obiekt klasy CPlayer i zwaraca wskaŸnik na ten obiekt
		///
		///@param &uniqueId - unikalny identyfikator - sta³a referencja na obiekt klasy std::wstring
		///
		logic::CPlayer *CreatePlayer( const std::wstring &uniqueId = L"");

		///
		///Metoda tworzy obiekt klasy CBullet i zwaraca wskaŸnik na ten obiekt
		///
		///@param &uniqueId - unikalny identyfikator - sta³a referencja na obiekt klasy std::wstring
		///
		logic::CBullet *CreateBullet( const std::wstring &uniqueId = L"");

		///
		///Metoda usuwa obiekt klasy CPhysical z kontenera
		///
		///@param *physical - wskaŸnik na obiekt klasy CPhysical
		///
		void DestroyPhysical(logic::CPhysical* physical);
	    
		///
		///Metoda usuwa obiekt klasy CPhysical z kontenera
		///
		///@param &id_physical - sta³a referencja na obiekt klasy std::wstring - unikalny identyfikator obiektu
		///
		void DestroyPhysical(const std::wstring& id_physical);

		///
		///Metoda usuwa wszystkie obiekty z kontenera
		///
		///@param force_destroy_instantly - flaga, czy usun¹æ z kontenera wszystkie obiekty
		///
		void Clear(bool force_destroy_instantly = false);

		///
		///Metoda zwraca sta³a referencjê do kontenera z nazwami wszystkich zarejestorwanych obiektów CPhysical
		///
		const std::map<std::wstring, logic::CPhysical*>& GetNamedPhysicals();

		///
		///Metoda zwraca sta³a referencjê do kontenera z wszystkimi wskaŸnikami zarejestorwanych obiektów CPhysical
		///
		const std::vector<logic::CPhysical*>& GetPhysicals();

		///
		///Metoda zwraca wskaŸnik na obiekt klasy CPhysical z kontenera na podstawie identyfikatora
		///
		///@param &physical_id - sta³a referencja na obiekt klasy std::wstring
		///
		logic::CPhysical* GetPhysicalById(const std::wstring& physical_id);

	private:
		
		//
		//Szablon metody tworzenia obiektów
		//
		template<class T> T* Create(const std::wstring &uniqueId);
	    
		std::map<std::wstring, logic::CPhysical*>		m_named_physicals;	//kontener <map> na nazwy obiektów CPhysical
		std::vector<logic::CPhysical*>					m_physicals;		//kontener <vector> na wskaŸniki na obiekty klasy CPhysical
	    
		//
		//Prywatna metoda sprawdzaj¹ca jaki identyfikator nadaæ obiektowi przy utworzeniu
		//
		//@param &new_unique_id - referencja na obiekt klasy std::wstring
		//
		void CheckUniqueId(std::wstring& new_unique_id);
	};
}//namespace logic
#endif//H_PHYSICAL_MANAGER_SCI
