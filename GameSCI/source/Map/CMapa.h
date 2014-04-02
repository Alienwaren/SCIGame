/*
 _____________________________________
| CMap.h - definicja klasy.           |
| Jack Flower October 2012.           |
| basic version for SCI October 2012. |
|_____________________________________|

*/

#ifndef H_MAP_JACK
#define H_MAP_JACK

#include <vector>
#include "../ResourceManager/IResource.h"
#include "CMapObjectType.h"
#include "CMapObjectDescriptor.h"
#include "MapHeader.h"
#include <SFML/Graphics/Rect.hpp>

///
///Forward declaration
///
namespace mapengine
{
	class CMapObjectDescriptor;
}

namespace mapengine
{
	
	const int CURRENT_MAP_VERSION = 1;	//nale�y pamieta�, aby w plikach 
//xml
//z map� trzyma� aktualn� wersj� //mapy
//poniewa� jet to do�� ryzykowny //kawa�ek kodu
							//zatem - w xml pisa� wersj� 1, 
//tak jak
							//tutaj zosta�a zadeklarowana

	///
	///Klasa reprezentuje map� gry - mapa �wiata gry
	///
	class CMapa : public IResource
	{

	public:

		///
		///Konstruktor
		///
		CMapa(void);

		///
		///Konstruktor kopiuj�cy
		///
		///@param &CMapCopy - obiekt klasy CMap
		///
		CMapa(const CMapa& CMapCopy);

		///
		///Destruktor wirtualny
		///
		virtual ~CMapa(void);

		///
		///Wirtualna metoda zwalniaj�ca zas�b - implementacje w klasach 
///pochodnych
		///
		void Drop();

		///
		///Metoda rozmieszcza na mapie obiekty wczytane z pliku
		///
		///@param load_complete_map - flaga okre�la, czy dane maj� by� 
///uwzgl�dniane na mapie
		///
		void RespawnMapObjects(bool load_complete_map);

		///
		///Metoda �aduj�ca dane
		///
		///@param &filename - sta�a referencja na std::string
		///
		bool Load(const std::string &filename);

		///
		///Metoda �aduj�ca dane z pliku xml
		///
		///@param &filename - sta�a referencja na std::string
		///
		bool LoadFromXML(const std::string &filename);

		///
		///Metoda usuwa z wektora wska�niki na obiekty klasy 
///CMapObjectDescriptor i dane pod tymi wska�nikami
		///
		void ClearMapObjects();

		///
		///Metoda zwraca indeks wzorca na podstawie nazwy
		///
		///@param map_object_type_name - nazwa identyfikatora wzorca 
///fabrycznego
		///
		int GetMapObjectTypeIndex(const std::string &map_object_type_name);

		///
		///Metoda zwraca nazw� pliku z map�
		///
		const std::string & CMapa::GetFilename();

		///
		///Metoda zwraca wektor z rozmiarem mapy w kaflach
		///
		sf::Vector2<int> GetSize();

		///
		///Metoda zwraca wersj� mapy
		///
		int GetVersion();


	private:

		MapHeader*	m_map_header;	//wska�nik na struktur� opisuj�c� 
//konfiguracj� mapy
		std::string	m_map_filename;	//nazwa pliku mapy
		sf::Vector2<int>	m_size;	//rozmiar mapy
		sf::IntRect	m_view_rectangle;	//obszar widoku (mapa w oku 
							//kamery)
		std::vector<CMapObjectType *>	m_map_object_types;		
							//wektor wska�nik�w na obiekty 
//fabryczne - wzorce dla obiekt�w 
//mapy
		std::vector<CMapObjectDescriptor *>	m_map_object_descriptors;
							//wektor wska�nik�w na obiekt
//umieszczone na mapie
 	};
} //namespace mapengine
#endif //H_MAP_JACK
