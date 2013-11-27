/*
 ________________________________
| CXml.cpp - implemetacja klasy. |
| SCI -  September 2012.         |
|________________________________|

*/

#include "CXml.h"
#include "../Utilities/StringUtils/StringUtils.h"

using namespace stringutils;
using namespace rapidxml;

namespace xml
{
	//Konstruktor domyœlny
	CXml::CXml(std::string filename, std::string root)
	:
		m_xml_document	(),
		m_xml_root		(NULL),
		m_filename		(filename),
		m_file			(NULL)
	{

		try//próba utworzenia i otwarcia pliku
		{
			m_file = new file<>(filename.c_str());							//tworzymy nowy plik i otwieramy jego zawartoœæ
			m_xml_document.parse<parse_declaration_node>(m_file->data());	//przepisujemy zawartoœæ pliku do
																			//dokumentu xml (parsujemy)
			m_xml_root = m_xml_document.first_node(root.c_str());			//ustwiamy siê na g³ównym
																			//wêŸle pliku xml "root"
		}
		catch(std::runtime_error &ex)
		{
			fprintf(stderr, "Error while reading file %s: %s\n", filename.c_str(), ex.what());
		}
	}

	//Destruktor
	CXml::~CXml()
	{
		if (m_file != NULL)
			delete m_file;
	}

	//Metoda zwraca wskaŸnik na wêze³ root dokumentu
	xml_node<>* CXml::GetRootNode()
	{
		return m_xml_root;
	}

	//Metoda zwraca nazwê pliku
	const std::string &CXml::GetFilename() const
	{
		return m_filename;
	}

	//Metoda zwraca wskaŸnik na wêze³ dzieci
	xml_node<>* CXml::GetChild(xml_node<> *parent, const std::string &node_name)
	{
		xml_node<>* real_parent = parent ? parent : m_xml_root;
		if (real_parent)
			return real_parent->first_node(node_name.c_str());
		return NULL;
	}

	//Metoda zwraca wskaŸnik na wêze³ rodzeñstwa
	xml_node<>* CXml::GetSibling(xml_node<> *sibling, const std::string &node_name)
	{
		if (sibling)
			return sibling->next_sibling(node_name.c_str());
		return NULL;
	}

	//Metoda zwraca atrybut wskazanego typu
	bool CXml::GetBool(xml_node<>* parent, const std::string &attrib_name, bool default_value)
	{
		bool out = default_value;
		xml_node<>* real_parent = parent ? parent : m_xml_root;
		std::string attr_value;
	    
		if (real_parent)
		{
			if (attrib_name == "")
			{
				if (real_parent->first_node())
				{
					attr_value = real_parent->first_node()->value();
					FromString(attr_value, out);
				}
			}
			else
				if (xml_attribute<>* attr = real_parent->first_attribute(attrib_name.c_str()))
				{
					attr_value = attr->value();
					out = (attr_value == "true");
					FromString(attr_value, out);
				}
		}
		return out;
	}

	//Metoda zwraca atrybut wskazanego typu
	bool CXml::GetBool(const std::string &node_name, const std::string &attrib_name, bool default_value)
	{
		if (m_xml_root)
			return GetBool(m_xml_root->first_node(node_name.c_str()), attrib_name, default_value);
		return default_value;
	}

	//Metoda zwraca atrybut wskazanego typu
	int CXml::GetInt(xml_node<> *parent, const std::string &attrib_name, int default_value)
	{
		int out = default_value;
		xml_node<>* real_parent = parent ? parent : m_xml_root;
		std::string attr_value;
	    
		if (real_parent)
		{
			if (attrib_name == "")
			{
				if (real_parent->first_node())
				{
					attr_value = real_parent->first_node()->value();
					FromString(attr_value, out);
				}
			}
			else
				if (xml_attribute<>* attr = real_parent->first_attribute(attrib_name.c_str()))
				{
					attr_value = attr->value();
					FromString(attr_value, out);
				}
		}
		return out;
	}

	//Metoda zwraca atrybut wskazanego typu
	int CXml::GetInt(const std::string &node_name, const std::string &attrib_name, int default_value)
	{
		if (m_xml_root)
			return GetInt(m_xml_root->first_node(node_name.c_str()), attrib_name, default_value);
		return default_value;
	}


	//Metoda zwraca atrybut wskazanego typu
	float CXml::GetFloat(xml_node<> *parent, const std::string &attrib_name, float default_value)
	{
		float out = default_value;
		xml_node<>* real_parent = parent ? parent : m_xml_root;
		std::string attr_value;
	    
		if (real_parent)
		{
			if (attrib_name == "")
			{
				if (real_parent->first_node())
				{
					attr_value = real_parent->first_node()->value();
					FromString(attr_value, out);
				}
			}
			else
				if (xml_attribute<>* attr = real_parent->first_attribute(attrib_name.c_str()))
				{
					attr_value = attr->value();
					FromString( attr_value, out );
				}
		}
		return out;
	}

	//Metoda zwraca atrybut wskazanego typu
	float CXml::GetFloat(const std::string &node_name, const std::string &attrib_name, float default_value)
	{
		if (m_xml_root)
			return GetFloat(m_xml_root->first_node(node_name.c_str()), attrib_name, default_value);
		return default_value;
	}

	//Metoda zwraca atrybut wskazanego typu
	std::string CXml::GetString(xml_node<> *parent, const std::string &attrib_name)
	{
		xml_node<>* real_parent = parent ? parent : m_xml_root;

		if (real_parent)
		{
			if (attrib_name == "")
			{
				if (real_parent->first_node())
					return real_parent->first_node()->value();
			}
			else if (xml_attribute<>* attr = real_parent->first_attribute(attrib_name.c_str()))
			{
				std::string out = attr->value();
				return out;
			}
		}
		return "";
	}

	//Metoda zwraca atrybut wskazanego typu
	std::string CXml::GetString(const std::string &node_name, const std::string &attrib_name)
	{
		if (m_xml_root)
			return GetString(m_xml_root->first_node(node_name.c_str()), attrib_name);
		return "";
	}

	//Metoda zwraca atrybut wskazanego typu
	std::wstring CXml::GetWString(xml_node<> *parent, const std::string &attrib_name)
	{
		xml_node<>* real_parent = parent ? parent : m_xml_root;

		if (real_parent)
		{
			if (attrib_name == "")
			{
				if (real_parent->first_node())
					return ConvertToWString(real_parent->first_node()->value());
			}
			else if (xml_attribute<>* attr = real_parent->first_attribute(attrib_name.c_str()))
			{
				std::string out = attr->value();
				return ConvertToWString(out);
			}
		}
		return L"";
	}

	//Metoda zwraca atrybut wskazanego typu
	std::wstring CXml::GetWString(const std::string &node_name, const std::string &attrib_name)
	{
		if (m_xml_root)
			return GetWString(m_xml_root->first_node(node_name.c_str()), attrib_name);
		return L"";
	}
}//namespace xml
