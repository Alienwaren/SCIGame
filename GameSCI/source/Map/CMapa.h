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
	
	const int CURRENT_MAP_VERSION = 1;	//nale¿y pamietaæ, aby w plikach 
//xml
//z map¹ trzymaæ aktualn¹ wersjê //mapy
//poniewa¿ jet to doœæ ryzykowny //kawa³ek kodu
							//zatem - w xml pisaæ wersjê 1, 
//tak jak
							//tutaj zosta³a zadeklarowana

	///
	///Klasa reprezentuje mapê gry - mapa œwiata gry
	///
	class CMapa : public IResource
	{

	public:

		///
		///Konstruktor
		///
		CMapa(void);

		///
		///Konstruktor kopiuj¹cy
		///
		///@param &CMapCopy - obiekt klasy CMap
		///
		CMapa(const CMapa& CMapCopy);

		///
		///Destruktor wirtualny
		///
		virtual ~CMapa(void);

		///
		///Wirtualna metoda zwalniaj¹ca zasób - implementacje w klasach 
///pochodnych
		///
		void Drop();

		///
		///Metoda rozmieszcza na mapie obiekty wczytane z pliku
		///
		///@param load_complete_map - flaga okreœla, czy dane maj¹ byæ 
///uwzglêdniane na mapie
		///
		void RespawnMapObjects(bool load_complete_map);

		///
		///Metoda ³aduj¹ca dane
		///
		///@param &filename - sta³a referencja na std::string
		///
		bool Load(const std::string &filename);

		///
		///Metoda ³aduj¹ca dane z pliku xml
		///
		///@param &filename - sta³a referencja na std::string
		///
		bool LoadFromXML(const std::string &filename);

		///
		///Metoda usuwa z wektora wskaŸniki na obiekty klasy 
///CMapObjectDescriptor i dane pod tymi wskaŸnikami
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
		///Metoda zwraca nazwê pliku z map¹
		///
		const std::string & CMapa::GetFilename();

		///
		///Metoda zwraca wektor z rozmiarem mapy w kaflach
		///
		sf::Vector2<int> GetSize();

		///
		///Metoda zwraca wersjê mapy
		///
		int GetVersion();


	private:

		MapHeader*	m_map_header;	//wskaŸnik na strukturê opisuj¹c¹ 
//konfiguracjê mapy
		std::string	m_map_filename;	//nazwa pliku mapy
		sf::Vector2<int>	m_size;	//rozmiar mapy
		sf::IntRect	m_view_rectangle;	//obszar widoku (mapa w oku 
							//kamery)
		std::vector<CMapObjectType *>	m_map_object_types;		
							//wektor wskaŸników na obiekty 
//fabryczne - wzorce dla obiektów 
//mapy
		std::vector<CMapObjectDescriptor *>	m_map_object_descriptors;
							//wektor wskaŸników na obiekt
//umieszczone na mapie
 	};
} //namespace mapengine
#endif //H_MAP_JACK
