/*
 _________________________________________________
| CMapObjectDescriptor.h - definicja klasy.       |
| Jack Flower April 2013.                         |
| basic version for SCI April 2013.               |
|_________________________________________________|

*/

#ifndef H_MAP_OBJECT_DESCRIPTOR_JACK
#define H_MAP_OBJECT_DESCRIPTOR_JACK

#include <string>
#include "CMapObjectType.h"

namespace factory
{
	///
	///Forward declaration
	///
	class CPhysicalTemplate;
}

using namespace logic;


namespace mapengine
{
	///
	///Klasa reprezentuje opakowanie danych dla obiektów (physicals), 
///umieszczonych na mapie (wczytywane z xml)
	///
    class CMapObjectDescriptor
	{

    public:

		///
		///Konstruktor
		///
		CMapObjectDescriptor();

		///
		///Konstruktor kopiuj¹cy
		///
///@param &CMapObjectDescriptorCopy - obiekt klasy ///CMapObjectDescriptor
		///
		CMapObjectDescriptor(const CMapObjectDescriptor& 
							CMapObjectDescriptorCopy);

		///
		///Destruktor
		///
		~CMapObjectDescriptor();


		///
		///Metoda tworzy obiekt mapy
		///
		void Create();

		//metody pomocnicze - hermetyzacja

		inline const std::string GetCode() const { return m_code; }
		inline void SetCode(const std::string &code) { m_code = code; }

		inline const std::string GetName() const { return m_name; }
		inline void SetName(const std::string &name) { m_name = name; }
		
		inline CPhysicalTemplate* GetTemplate() const
{	
return p_templ;
}
		
inline void SetTemplate(CPhysicalTemplate* template_param)
{
p_templ = template_param;
}
		
		inline const float GetXPosition() const
{
return m_x_position;
}
		
inline void SetXPosition(float x_position)
{
m_x_position = x_position;
}
		
		inline const float GetYPosition() const
{
return m_y_position;
}
		
inline void SetYPosition(float y_position)
{
m_y_position = y_position;
}

		inline const float GetRotationBody() const
{
return m_rotation_body;
}
		
inline void SetRotationBody(float rotation_body)
{
m_rotation_body = rotation_body;
}

		inline const float GetRotationHead() const
{
return m_rotation_head;
}
		
 

inline void SetRotationHead(float rotation_head)
{
m_rotation_head = rotation_head;
}

		inline const bool GetSmooth() const { return m_smooth; }
		inline void SetSmooth(bool smooth) { m_smooth = smooth; }

		inline const int GetUniqueId() const { return m_uniqueId; }

	private:

		std::string			m_code;	//nazwa obiektu 
//fabrycznego (template)
//w pliku xml
      std::string			m_name;	//nazwa, któr¹ nadajemy 
							//obiektowi
      CPhysicalTemplate*	p_templ;		//wskaŸnik na wzorzec 
//produkcyjny
      float				m_x_position;	//sk³adowa pozycji x 
//na mapie
float	m_y_position;	//sk³adowa pozycji y 
//na mapie
		float				m_rotation_body;	//wartoœæ obrotu 
//pocz¹tkowego body
		float				m_rotation_head;	//wartoœæ obrotu 
									//pocz¹tkowego head
		int				m_uniqueId;		//unikalny indeks
		bool				m_smooth;		//flaga filtru grafiki 
									//- smooth
		static int			nextId;		//generator wartoœci 
								//unikalnej przy 
//tworzeniu obiektu
    };

}//namespace mapengine
#endif //H_MAP_OBJECT_DESCRIPTOR_JACK
