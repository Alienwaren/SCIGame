/*
 _____________________________________
| CMapa.cpp - implementacja klasy.     |
| Jack Flower October 2012.           |
| basic version October 2012.         |
|_____________________________________|

*/

#include "CMapa.h"
#include "CMapObjectDescriptor.h"
#include "../ResourceManager/CResourceManager.h"
#include "../Rendering/Displayable/CDisplayable.h"
#include "../Rendering/Drawable/CDrawableManager.h"
#include "../Rendering/Drawable/Layers.h"

using namespace rapidxml;
using namespace resource;
using namespace mapengine;
using namespace rendering::displayable;

namespace mapengine
{
	//Konstruktor
	CMapa::CMapa(void)
	:
		m_map_filename			(""),
		m_map_header			(NULL),
		m_view_rectangle			(0,0,0,0),
		m_size				(0,0),
		m_map_object_types		(NULL),
		m_map_object_descriptors	(NULL)
	{
		fprintf(stderr, "CMapa::CMapa()\n");
	}

	//Konstruktor kopiuj¹cy
	CMapa::CMapa(const CMapa& CMapaCopy)
	:
		m_map_filename			(CMapaCopy.m_map_filename),
		m_map_header			(CMapaCopy.m_map_header),
		m_view_rectangle			(CMapaCopy.m_view_rectangle),
		m_size				(CMapaCopy.m_size),
		m_map_object_types		(CMapaCopy.m_map_object_types),
		m_map_object_descriptors    (CMapaCopy.m_map_object_descriptors)
	{
		fprintf(stderr, "CMapa::CMapa(const CMapa& CMapaCopy)\n");
	}

 
	//Destruktor
	CMapa::~CMapa(void)
	{
		m_map_filename			= "";
		m_map_header			= NULL;
		//m_view_rectangle		not edit
		//m_size				not edit
		//m_map_object_types		not edit
		//m_map_object_descriptors	not edit
		fprintf(stderr, "CMapa::~CMapa(void)\n");
	}

	//Wirtualna metoda zwalniaj¹ca zasób - implementacje w klasach 
	//pochodnych
	void CMapa::Drop()
	{
		fprintf(stderr, "CMapa::Drop()\n");
		
		delete m_map_header;
		ClearMapObjects();
		delete this;
	}

	//Metoda rozstawiam wczytane z pliku mapy obiekty na scenie
	void CMapa::RespawnMapObjects(bool load_complete_map)
	{
	//póki co, przy wywo³aniu metody flagê nale¿y ustawiæ na true
        for (unsigned int i = 0; i < m_map_object_descriptors.size(); i++)
        {
            if (load_complete_map)
                m_map_object_descriptors[i]->Create();
        }
	}


	//Metoda ³aduj¹ca dane
	bool CMapa::Load(const std::string &filename)
	{
		fprintf(stderr, "map %s loaded...\n", filename.c_str());
		return LoadFromXML(filename);
	}


	//Metoda ³aduj¹ca dane z pliku xml
	bool CMapa::LoadFromXML(const std::string &filename)
	{
		m_map_filename = filename;	//nazwa pliku mapy
		CXml xml(filename, "map");	//wszystkie pliki xml z mapami – 
							//maj¹ nag³ówek root <map>
		xml_node<>* node;			//wskaŸnik na wêze³ dokumentu xml
		std::string str_data;		//nazwa dla danych ³adowanych z 
							//xml

        //tworzymy nag³ówek mapy
        m_map_header = new MapHeader();

	//sprawdzamy, czy obowi¹zuj¹ca wersja mapy jest poprawna
        m_map_header->m_map_version = xml.GetInt("version");
        if(m_map_header->m_map_version != CURRENT_MAP_VERSION)
		{
			fprintf(stderr, "Invalid map version (%d, expected %d) for map %s", m_map_header->m_map_version, CURRENT_MAP_VERSION, filename.c_str());
			return false;
        }

		//wype³niamy danymi strukturê opisuj¹c¹ mapê
		m_map_header->m_map_width_in_tile = xml.GetInt( "width" );
		m_map_header->m_map_height_in_tile = xml.GetInt( "height" );
		m_size.x = m_map_header->m_map_width_in_tile;
		m_size.y = m_map_header->m_map_height_in_tile;

        //typy fabryczne dla physicali na danej mapie
		CMapObjectType* p_map_object_type;

		for (node = xml.GetChild(xml.GetRootNode(), "objtype"); node; node = xml.GetSibling(node, "objtype"))
		{
			str_data = xml.GetString(node, "file");
			if(gResourceManager.LoadPhysicalTemplate(str_data) == false)
			{
				fprintf(stderr, "Cannot load object template file: %ls", str_data.c_str());
				return false;
			}
			p_map_object_type = new CMapObjectType();
			p_map_object_type->SetCode(xml.GetString(node, "code"));
			p_map_object_type->SetTemplate(gResourceManager.GetPhysicalTemplate(str_data));
			m_map_object_types.push_back(p_map_object_type);
        }

		//physical's (potwory, drzewka, domki, to co potrafimy utworzyæ)
		CMapObjectDescriptor *p_map_object;
		for (node = xml.GetChild(xml.GetRootNode(), "obj"); node; node = xml.GetSibling(node, "obj"))
		{
			str_data = xml.GetString(node, "code");
			int i = GetMapObjectTypeIndex(str_data);
			if (i < 0)
				return false;
			p_map_object = new CMapObjectDescriptor();

			p_map_object->SetCode(str_data);//nazwa wzorca (fabryczna
			p_map_object->SetName(xml.GetString(node, "name"));//nazwa obiektu
			p_map_object->SetXPosition(xml.GetFloat(node, "x"));
			p_map_object->SetYPosition(xml.GetFloat(node, "y"));
			p_map_object->SetRotationBody(xml.GetFloat(node, "rotation_body"));
			p_map_object->SetRotationHead(xml.GetFloat(node, "rotation_head"));
			p_map_object->SetSmooth(xml.GetBool(node, "smooth"));
			
			p_map_object->SetTemplate(m_map_object_types[i]->GetTemplate());
			m_map_object_descriptors.push_back(p_map_object);
		}
        return true;//jeœli pomyœlnie zosta³y za³adowane dane - zwracamy true
	}


	//Metoda usuwa z wektora wskaŸniki na obiekty klasy CMapaObjectDescriptor i dane pod tymi wskaŸnikami
	void CMapa::ClearMapObjects()
	{
		//obiekty
		for (unsigned i = 0; i < m_map_object_descriptors.size(); i++)
			delete m_map_object_descriptors[i];
		m_map_object_descriptors.clear();
	}
	
	//Metoda zwraca indeks wzorca na podstawie nazwy
	int CMapa::GetMapObjectTypeIndex(const std::string &map_object_type_name)
	{
		for (unsigned int i = 0; i < m_map_object_types.size(); i++)
			if (m_map_object_types[i]->GetCode() == map_object_type_name)
				return i;
		// zwraca -1, wiec to chyba nie jest niezbedne?
		//tego nie analizowaæ, ja Jack Flower - mêczy³em siê
		//i nawet nie pamiêtam, czy ten temat "zamiot³em"?
		fprintf(stderr, "failed to find object template code %s\n",map_object_type_name.c_str());
		return -1;
	}

	//Metoda zwraca nazwê pliku z map¹
	const std::string& CMapa::GetFilename()
	{
		return m_map_filename;
	}

	//Metoda zwraca wektor z rozmiarem mapy w kaflach
	sf::Vector2<int> CMapa::GetSize()
	{
		return m_size;
	}

	//Metoda zwraca wersjê mapy
	int CMapa::GetVersion()
	{
		return m_map_header->m_map_version;
	}

} //namespace mapengine
