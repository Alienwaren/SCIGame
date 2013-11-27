/*
 ________________________________
| CXml.h - definicja klasy.      |
| SCI -  September 2012.         |
|________________________________|

*/

#ifndef H_XML_SCI
#define H_XML_SCI

#include "RapidXML/rapidxml.hpp"
#include "RapidXML/rapidxml_utils.hpp"
#include <string>

using namespace std;
using namespace rapidxml;

namespace xml
{
	///
	///Klasa reprezentuje opadkowanie parsera RapidXML
	///
	class CXml
	{
	public:
		
		///
		///Konstruktor domy�lny
		///
		///@param filename - nazwa pliku
		///
		///@param root - nazwa w�z�a g��wnego root
		///
		CXml(std::string filename, std::string root);
		
		///
		///Destruktor
		///
		~CXml();

		///
		///Metoda zwraca wska�nik na w�ze� root dokumentu
		///
		xml_node<>* GetRootNode();

		///
		///Metoda zwraca nazw� pliku
		///
		const std::string &GetFilename() const;

		///
		///Metoda zwraca wska�nik na w�ze� dziecka
		///
		///@param parent  - wska�nik na w�ze�
		///
		///@param node_name - nazwa pobieranego w�z�a
		///
		xml_node<>* GetChild(xml_node<>* parent, const std::string &node_name);

		///
		///Metoda zwraca wska�nik na w�ze� rodze�stwa
		///
		///@param *sibling - wska�nik na w�ze�
		///
		///@param node_name - nazwa w�z�a
		///
		xml_node<>* GetSibling(xml_node<>* sibling, const std::string &node_name);    

		///
		///Metoda zwraca atrybut wskazanego typu
		///
		///@param *parent - wska�nik na w�ze� dokumentu xml
		///
		///@param &attrib_name - sta�a referencja na nazw� atrybutu dokumentu xml
		///
		///@param default_value - warto�� default (false)
		///
		bool GetBool(xml_node<>* parent, const std::string &attrib_name = "", bool default_value = false);

		///
		///Metoda zwraca atrybut wskazanego typu
		///
		///@param &node_name - sta�a referencja na nazw� w�z�a
		///
		///@param &attrib_name - sta�a referencja na nazw� atrybutu dokumentu xml
		///
		///@param default_value - warto�� default (false)
		///
		bool GetBool(const std::string &node_name, const std::string &attrib_name = "", bool default_value = false);

		///
		///Metoda zwraca atrybut wskazanego typu
		///
		///@param *parent - wska�nik na w�ze� dokumentu xml
		///
		///@param &attrib_name - sta�a referencja na nazw� atrybutu dokumentu xml
		///
		///@param default_value - warto�� default (false)
		///
		int GetInt(xml_node<>* parent, const std::string &attrib_name = "", int default_value = 0);

		///
		///Metoda zwraca atrybut wskazanego typu
		///
		///@param &node_name - sta�a referencja na nazw� w�z�a
		///
		///@param &attrib_name - sta�a referencja na nazw� atrybutu dokumentu xml
		///
		///@param default_value - warto�� default (false)
		///
		int	GetInt(const std::string &node_name, const std::string &attrib_name = "", int default_value = 0);

		///
		///Metoda zwraca atrybut wskazanego typu
		///
		///@param *parent - wska�nik na w�ze� dokumentu xml
		///
		///@param &attrib_name - sta�a referencja na nazw� atrybutu dokumentu xml
		///
		///@param default_value - warto�� default (false)
		///
		float GetFloat(xml_node<>* parent, const std::string &attrib_name = "", float default_value = 0.0f);

		///
		///Metoda zwraca atrybut wskazanego typu
		///
		///@param &node_name - sta�a referencja na nazw� w�z�a
		///
		///@param &attrib_name - sta�a referencja na nazw� atrybutu dokumentu xml
		///
		///@param default_value - warto�� default (false)
		///
		float GetFloat(const std::string &node_name, const std::string &attrib_name = "", float default_value = 0.0f);

		///
		///Metoda zwraca atrybut wskazanego typu
		///
		///@param *parent - wska�nik na w�ze� dokumentu xml
		///
		///@param &attrib_name - sta�a referencja na nazw� atrybutu dokumentu xml
		///
		///@param default_value - warto�� default (false)
		///
		std::string	GetString(xml_node<>* parent, const std::string &attrib_name = "");

		///
		///Metoda zwraca atrybut wskazanego typu
		///
		///@param &node_name - sta�a referencja na nazw� w�z�a
		///
		///@param &attrib_name - sta�a referencja na nazw� atrybutu dokumentu xml
		///
		///@param default_value - warto�� default (false)
		///
		std::string	GetString(const std::string &node_name, const std::string &attrib_name = "");

		///
		///Metoda zwraca atrybut wskazanego typu
		///
		///@param *parent - wska�nik na w�ze� dokumentu xml
		///
		///@param &attrib_name - sta�a referencja na nazw� atrybutu dokumentu xml
		///
		std::wstring GetWString(xml_node<>* parent, const std::string &attrib_name = "");

		///
		///Metoda zwraca atrybut wskazanego typu
		///
		///@param &node_name - sta�a referencja na nazw� w�z�a
		///
		///@param &attrib_name - sta�a referencja na nazw� atrybutu dokumentu xml
		///
		std::wstring GetWString(const std::string &node_name, const std::string &attrib_name = "");


	private:

		xml_document<>	m_xml_document;		//dokument XML
		xml_node<>*		m_xml_root;			//wska�nik na w�ze� root dokumentu
		std::string     m_filename;			//nazwa pliku
		file<char>*		m_file;				//obiekt szablonu klasy rapidxml::file - plik
	};
}//namespace xml
#endif //H_XML_SCI

