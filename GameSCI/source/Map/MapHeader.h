/*
 ___________________________________________________
| MapHeader.h - definicja struktury opisuj¹ce mapê. |
| basic version for SCI April 2013.                 |
| Jack Flower April 2013.                           |
|___________________________________________________|

*/

#ifndef H_MAP_HEADER_JACK
#define H_MAP_HEADER_JACK

#include <SFML/System/Vector2.hpp>
namespace mapengine
{
	///
	///Struktura opisuje konfiguracjê mapy
	///
	struct MapHeader
	{
		int		m_map_version;		//wersja mapy
		int		m_map_width_in_tile;	//szerkoœæ mapy w kaflach
		int		m_map_height_in_tile;	//wysokoœæ mapy w kaflach
	};
}
#endif //H_MAP_HEADER_JACK
