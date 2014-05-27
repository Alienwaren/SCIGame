/*
 ___________________________________________
| CMapObjectType.h - definicja klasy.       |
| Jack Flower April 2013.                   |
| basic version for SCI April 2013.         |
|___________________________________________|

*/

#ifndef H_MAP_OBJECT_TYPE_JACK
#define H_MAP_OBJECT_TYPE_JACK

#include <string>
#include "../Factory/CPhysicalTemplate.h"
namespace mapengine
{
	///
	///Klasa reprezentuje typ wzorca obiektu umieszczonego na mapie
	///
	class CMapObjectType
	{

	public:

		///
		///Konstruktor
		///
		CMapObjectType();

		///
		///Konstruktor kopiujπcy
		///
		///@param &CMapObjectTypeCopy - obiekt klasy CMapObjectType
		///
		CMapObjectType(const CMapObjectType& CMapObjectTypeCopy);

		///
		///Destruktor
		///
		~CMapObjectType();

		//metody pomocnicze - hermetyzacja

		inline const std::string &GetCode() const
{
return m_code;
}
		inline void SetCode(const std::string& code)
{
m_code = code;
}

		inline CPhysicalTemplate* GetTemplate() const
{
return p_template;
}
		

inline void SetTemplate(CPhysicalTemplate* template_param)
{
p_template = template_param;
}


	private:

std::string	m_code;	//unikalna nazwa
//obiektu wzorca nadawana
//w pliku xml
		CPhysicalTemplate*	p_template;	//wskaünik na wzorzec danych
	};
} //namespace mapengine
#endif //H_MAP_OBJECT_TYPE_JACK
